#include <math.h>
#include <stdbool.h>
bool IsPrime( int Num )
{
        if( Num == 2 || Num == 5 || Num == 3 )
                return true ;
        if( !( Num % 2 ) || ! ( Num % 5 ) || ! ( Num % 3 ) )
                return false ;
        int Max = ( int )sqrt( Num ) ;
        Max = (Max % 2) ? Max : Max - 1 ;
        for ( int i = 7 ; i <= Max ; i += 4 )
        {
                for( int j = 0 ; j < 3 ; j++ , i+=2 )
                {
                        if( !( Num % i) )
                                return false;
                }
        }
        if( Num<=1 )
                return false;
        return true;
}


bool IsPrime(long long Num)//更好的方法。质数一定是被6整除余1或者余5的数(1除外)
{
	if (Num <= 3)
		return Num > 1;
	if (Num % 6 != 1 && Num % 6 != 5)
		return false;
	long long range = (long long)sqrt(Num);
	for (int i = 5; i < range; i += 6)
		if (Num%i == 0 || Num % (i + 2) == 0)
			return false;
	return true;
}
