#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#define Length 1000000
//i j对应的实际数
#define map(i,j) (2*(8*i+j)+1)
#define numIsTrue(i,j) ( (data[i] >> j) & 1 )
//在位数组bit_array中清除目标数bit_number
void clear_bit(unsigned char bit_array[],unsigned bit_number)
{
        unsigned indexOfArray = bit_number / 16 ;
        unsigned indexOfBit = (bit_number % 16-1)/2;
        bit_array[indexOfArray] &= ~(1<<indexOfBit);
}
//bit_number:要找的数,indexofArray:目标数在位数组中的下标,indexOfbit:目标数在位数组中的偏移值
void find_number(unsigned *indexOfArray,unsigned *indexOfBit,unsigned bit_number)
{
        *indexOfArray = bit_number / 16 ;
        *indexOfBit = (bit_number % 16-1)/2;
}
int main(void)
{
        unsigned char data[Length]={0};
        memset(data,255,Length);
        data[0]&=(~1);
        int max = map(Length-1,8);
        int curNum = 0;
        for(int i = 0 ; i < Length ; ++i)
        {
                for(int j = 0 ; j < 8;++j)
                {
                        if( numIsTrue(i,j) )
                        {
                                curNum = map(i,j);
                                for(int num = 3*curNum ;num < max ;num += 2*curNum)
                                {
                                        clear_bit(data,num);
                                }
                        }
                }
        }
        unsigned startIndexOfArray,startIndexOfBit,endIndexOfArray,endIndexOfBit;
        find_number(&startIndexOfArray,&startIndexOfBit,1000000);//
        find_number(&endIndexOfArray,&endIndexOfBit,1001000);
        unsigned num = 0;
        int cnt = 0;
        for(int i = startIndexOfArray ; i<= endIndexOfArray ;++i)
        {
                for(int j = 0 ; j<8;++j)
                {
                        if(data[i]&(1<<j))
                        {
                                num = 16*i+2*j+1;
                                printf("%d ",num);
                                if(num>=1000000&&num<=1001000)
                                        cnt++;
                        }
                }
        }
        printf("%d",cnt);
}
