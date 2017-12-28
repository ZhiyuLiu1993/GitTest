#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

#define UINT8 unsigned char
#define UINT32 unsigned int 
#define INT32  int 
//1个字节8个像素转为1个字节1个像素
//bitarraytemp为1个字节1个像素，current为1个字节8个像素,bitmapsize为像素数量
void bitmap2char(UINT8 *bitarraytemp, UINT8 *current, UINT32 bitmapsize)
{
	UINT8 a;
	INT32 j, k;
	memset(bitarraytemp, 0, bitmapsize);
	for(j = 0; j < bitmapsize/8; j++)
	{
		a = 0b10000000;
		for(k = 0; k < 8; k++)
		{
			if(a == (a & current[j]))
			{
				bitarraytemp[j*8+k] = 1;
			}
			else
				bitarraytemp[j*8+k] = 0;

			//printf("%d", bitarraytemp[j*8+k]);
			a = a>>1;//需验证UINT8右移是否最高位是否为1
		}
	}
}

//1个字节1个像素转为1个字节8个像素
//bitarraytemp为1个字节1个像素，current为1个字节8个像素,bitmapsize为像素数量
void char2bitmap(UINT8 *bitarraytemp, UINT8 *current, UINT32 bitmapsize)
{
	UINT8 a[8];
	a[7] = 0b00000001;
	a[6] = 0b00000010;
	a[5] = 0b00000100;
	a[4] = 0b00001000;
	a[3] = 0b00010000;
	a[2] = 0b00100000;
	a[1] = 0b01000000;
	a[0] = 0b10000000;
	INT32 i, j, k, temp;
	temp = bitmapsize/8;
	if(bitmapsize%8)
		temp = bitmapsize/8 + 1;
	memset(current, 0, temp);
	for(j = 0; j < bitmapsize; j++)
	{
		k = j / 8;
		i = j % 8;
		if(bitarraytemp[j] == 1)
		{
			current[k] = current[k] | a[i];		
		printf("%d:%d\n", k, current[k]);
		}
	}
}

int main()
{
	char *bitarraytemp = "100000001111111100000001";
	unsigned char *current = malloc(10 * sizeof(char));
	char2bitmap(bitarraytemp, current, 24);
	//char current[3] = {255,128,1};
	//char *bitarraytemp = malloc(25 * sizeof(char));
	//bitmap2char(bitarraytemp, current, 24);
	int i;
	for(i = 0; i < 3; ++i)
		printf("%d:%d\n", i, current[i]);
	return 0;
}

