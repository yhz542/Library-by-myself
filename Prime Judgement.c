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
