#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>

int main(int argc, char *argv[])
{
	//1.参数校验
	if(argc != 3){
		fprintf(stderr, "用法：%s <源文件路径> <目标文件路径>\n", argv[0]);
		return 1;
	}
	const char *src_path = argv[1];
	const char *dst_path = argv[2];

	//2.检查源文件与目标文件是否为同一个文件（防止O——TRUNC清空源文件）
	struct stat src_stat, dst_stat;
	if(stat(src_path, &src_stat) == -1){
		perror("stat source file");
		return 1;
	}
	//目标文件已存在时，通过设备号+inode号判断是否为同一文件
	if(stat(dst_path, &dst_stat) == 0){
		if(src_stat.st_dev == dst_stat.st_dev && src_stat.st_ino == dst_stat.st_ino){
			fprintf(stderr, "error:source and destination cannot be the same file\n");
			return 1;
		}
	}

	int src_fd = -1;
	int dst_fd = -1;
	char buffer[4096];

	//3. 打开源文件（只读）
	src_fd = open(src_path,O_RDONLY);
	if(src_fd == -1){
		perror("open source");
		return 1;
	}

	//4.打开/创建目标文件（只写+创建+清空），权限0644
	dst_fd = open(dst_path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if(dst_fd == -1){
		perror("open destination");
		close(src_fd);//异常路径必须释放已打开的资源
		return 1;
	}

	//5.循环读写核心逻辑
	for(;;){
		ssize_t nread = read(src_fd, buffer, sizeof(buffer));
		//读到文件末尾，正常结束
		if(nread == 0){
			break;
		}
		
		//读取出错
		if(nread < 0){
                        if(errno == EINTR){
				continue;
			}
			perror("read source");
			close(src_fd);
			close(dst_fd);
			return 1;
                }

		//循环写入，保证所有数据全部写入完成（处理短写）
		ssize_t offset = 0;
		while(offset < nread){
			ssize_t nwritten = write(dst_fd, buffer + offset, (size_t)(nread - offset));

		        if(nwritten < 0){
       				if(errno == EINTR){
                                	continue;
                        	}
                        	perror("write destination");
                        	close(src_fd);
                        	close(dst_fd);
                        	return 1;
                }
		
		offset += nwritten;

		}
	}

	//6.正常路径释放所有资源
	close(src_fd);
	close(dst_fd);

	return 0;
}

