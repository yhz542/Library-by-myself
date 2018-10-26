#include <stdio.h>
#define Min (-1*(2LL<<30))
void MaxSeq(int [],int);
int main(void)
{
        int testArray[ 10 ] = { -1 , -2 , 3 , 5 , -4 , -9 , -14 , -15 , 20 , 21 } ;
        int temSum = Min ;
        int MaxSum = temSum ;
        int tem ;
        for ( int i = 0 ; i < 10 ; ++i )
        {
                tem = testArray[ i ] ;
                temSum = ( temSum < 0 ? tem : temSum+ tem ) ;
                if ( temSum > MaxSum )
                        MaxSum = temSum ;
        }
        printf("%d",MaxSum) ;
        return 0;
}
