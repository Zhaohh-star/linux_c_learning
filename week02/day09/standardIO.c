#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int main(int argc,char const*argv[])
{
	if(argc != 3){
		printf("Uagae:%s,<src> <dst>\n",argv[0]);
		exit(1);//1表示异常退出，0是正常退出
	}

	//FILE *fopen(const char *pathname, const char *mode);
	FILE *fp1 = fopen(argv[1],"r"); //只读
	FILE *fp2 = fopen(argv[2],"w"); // 只写

	int c;
	while(1)
	{
		c=fgetc(fp1);//从指定的流fp1读，一次读一个字符
		if(c == EOF)//表示出错或者文件末尾
		{
			//1.到达文件末尾
			if(feof(fp1))//feof()用于判断是否到达文件末尾
			{
				printf("read completed!\n");
				break;
			}
			//2.遇到错误
			else if(ferror(fp1)&& errno == EINTR)//feof()用于判断是否到达文件末尾
                        {                               //ferror用于判断是否出现错误
							//errno是一个全局错误马用于存储程序运行期间产生的错误信息
                                printf("interrupt!\n");//EINTR表示发生了系统调用或中断
                                continue;
                        }
			else if(ferror(fp1))
			{
				printf("fatal error!\n");
                                break;

			}
		}
		fputc(c,fp2); //向指定的流fp2,一次输出一个字符
	}
	fclose(fp1);   //关闭输入流
	fclose(fp2);   // 关闭输出流
	return 0;
}
