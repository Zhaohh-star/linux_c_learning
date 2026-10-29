#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

int main(int argc,char const*argv[])
{
	if(argc != 3){
		printf("Uagae:%s,<src> <dst>\n",argv[0]);
		exit(1);//1表示异常退出，0是正常退出
	}

	//FILE *fopen(const char *pathname, const char *mode);
	FILE *fp1 = fopen(argv[1],"r"); //只读
	FILE *fp2 = fopen(argv[2],"w"); // 只写

	char *buf = malloc(100*5); // 申请100个字节的动态内存快
	int nread;
	while(1)
	{
		unsigned long pos1 =  ftell(fp1);// ftell获得当前文件位置指针的位置
		//size_t fread(void *ptr, size_t size, size_t nmemb, FILE *stream);
		nread=fread(buf,100,5,fp1);//从指定的流fp1读，一次读5块数据，每块的大小是100个字节，一次最多读500个字节
		//1. 遇到了错误
		if(nread == -1)
		{
			printf("error!:%s\n",strerror(errno)); // 打印全局错误码 strerror函数将错误码映射成错误信息
			exit(1);//异常退出
		}
		//2.到达文件末尾
		if(nread<5)
		{
			unsigned long pos2 =  ftell(fp1);// ftell获得当前文件位置指针的位置
			fwrite(buf,pos2-pos1,1,fp2); //写一块，这块的大小是pos2-pos1个位置
			break;
		}
		//3.正常读写
		//size_t fread(void *ptr, size_t size, size_t nmemb, FILE *stream);size_t fread(void *ptr, size_t size, size_t nmemb, FILE *stream);
		fwrite(buf,100,5,fp2); // 向指定的流fp2写数据
	}
	fclose(fp1);   //关闭输入流
	fclose(fp2);   // 关闭输出流

	free(buf);
	return 0;
}
