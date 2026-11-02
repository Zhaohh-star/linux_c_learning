#include <stdio.h>
#include <stdint.h>
#include <string.h>

static uint16_t decode_u16_le(const uint8_t *in)   //小端编码
{
	return (uint16_t)in[0] | ((uint16_t)in[1]<<8);
}

int main(int argc, char** argv)
{
	if(argc != 2)
	{
		fprintf(stderr,"Usage: ./reader sample.bin\n");
		return 2;
	}
	FILE *fp = fopen(argv[1],"rb");
	if(!fp)
	{
		perror("open fail");
		return 3;
	}
	
	uint8_t buf[8] = {0};  //整个缓冲区，一共8个字节，全部先清零
	

	//把8个原始字节一次性写入文件
	//size_t fread(void *ptr, size_t size, size_t nmemb, FILE *stream);
	size_t rn = fread(buf,1,8,fp);
	if(rn != 8)
	{
		fprintf(stderr,"file length error,need 8 bytes\n");
		fclose(fp);
		return 4;
	}
	
	//校验magic 首字母是不是PCIE
	if(memcmp(buf, "PCIE", 4) != 0)
	{
		fprintf(stderr,"magic number error!\n");
		fclose(fp);
		return 4;
	}

	//解码 从偏移4解码version   从偏移6解码count  小端
	uint16_t ver = decode_u16_le(buf + 4);
	uint16_t cnt = decode_u16_le(buf + 6);
	
	printf("Magic: PCIE\n");
	printf("Version: %u\n",ver);
	printf("Count: %u\n",cnt);

	fclose(fp);
	return 0;
}
