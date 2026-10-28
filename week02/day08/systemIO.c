#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	
	if(argc != 3)
	{
		printf("Usage: %s src dst\n",argv[0]);
		return -1;
	}
	//int open(const char *pathname, int flags, mode_t mode);
	int fd1 = open(argv[1], O_RDWR | O_CREAT ,0777); // R W X
        if(fd1 == -1) //说明打开失败
        { 
                perror("have a error!");
		return -1;
        }

	int fd2 = open(argv[2],O_RDWR | O_CREAT,0777); // R W X
	if(fd2 == -1) //说明打开失败
	{
		perror("have a error!");
		return -1;
	}

	//打开成功！下面就是业务逻辑
        if(fd1 != -1) //说明打开成功
        { 
		int size;
	        //off_t lseek(int fd, off_t offset, int whence);
		size = lseek(fd1,0,SEEK_END);//获得文件的大小
         	printf("file size is:%d\n",size);

		lseek(fd1,0,SEEK_SET); //把文件位置指针移动到相对文件头部0个字节的位置（文件的第一个字符）
		
		char buf[size+1];
		int num;
		int ret;
		//ssize_t read(int fd, void *buf, size_t count);
		num = read(fd1, buf, size); //从fd1所代表的文件读size个字节，到buf当中
		buf[size] = '\0';	
		printf("read %d:\n%s\n",num,buf);

		//ssize_t write(int fd, const void *buf, size_t count);
		ret = write(fd2, buf, size);
		if(ret > 0)
		{
			perror("write successfully!!! \n");
                	return -1;
		}
		else
		{
			perror("write failed!!! \n");
			return -1;
		}

		close(fd2);  //关闭目标文件
		close(fd1);  //关闭源文件

	//	system("cat ");
        }




	return 0;


}
