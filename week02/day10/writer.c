#include <stdio.h>
#include <stdint.h>
#include <string.h>

static void encode_u16_le(uint8_t *out ,uint16_t value)   //小端编码
{
	out[0] = value & 0xffu;
	out[1] = (value >> 8) & 0xffu;
}

int main(int argc, char** argv)
{
	if(argc != 2)
	{
		fprintf(stderr,"Uasge: ./writer sample.bin\n");
		return 2;
	}
	FILE *fp = fopen(argv[1], "wb");
	if(!fp)
	{
		perror("fopen failed");
		return 3;
	}
	
	uint8_t buf[8] = {0};  //整个缓冲区，一共8个字节，全部先清零
	
	//void *memcpy(void *dest, const void *src, size_t n);	
	memcpy(buf, "PCIE",4);
	encode_u16_le(buf + 4, 1); // 小端
	encode_u16_le(buf + 6, 2);

	//把8个原始字节一次性写入文件
	//size_t fwrite(const void *ptr, size_t size, size_t nmemb,FILE *stream);
	size_t wn = fwrite(buf,1,8,fp);
	if(wn != 8)
	{
		perror("fwrite error");
		fclose(fp);
		return 3;
	}
	
	if(fclose(fp) != 0)
	{
		perror("fclose error");
                return 3;
	}

	printf("write ok\n");
	return 0;
}
