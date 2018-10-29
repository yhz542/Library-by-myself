#include <iostream>//代码待优化
#include <string>
#include <cstddef>
#include <cstdlib>
using namespace std ;
size_t findDot( string &) ;
int main()
{
	string num1 , num2 ;
	size_t floatlength = 0 ;
	char *floatPart ;
	while ( cin >> num1 >> num2 )
	{
		size_t dotPosition1 , dotPosition2 ;
		dotPosition1 = findDot( num1 ) ;
		dotPosition2 = findDot( num2 ) ;
		auto floatlength1 = num1.size() - dotPosition1 -1;
		auto floatlength2 = num2.size() - dotPosition2 -1;
		if ( floatlength1 > floatlength2 )
		{
			char *tem = ( char * ) malloc( sizeof( char ) * ( floatlength1 - floatlength2+1));
			for ( int i = 0 ; i != floatlength1 - floatlength2 ; ++i )
				tem[ i ] = '0' ;
			tem[ floatlength1 - floatlength2 ] ='\0' ;
			num2 += tem ;
			free( tem ) ;
			floatlength = floatlength1 ;
		}
		else if( floatlength2 > floatlength1 )
		{
			char *tem = ( char * ) malloc( sizeof( char ) * ( floatlength2 - floatlength1+1));
			for ( int i = 0 ; i != floatlength2 - floatlength1 ; ++i )
				tem[ i ] = '0' ;
			tem[ floatlength2 - floatlength1 ] ='\0' ;
			num1 += tem ;
			free( tem ) ;
			floatlength = floatlength2 ;
		}
		else//长度相等
			floatlength = floatlength1 ;
		floatPart = ( char * ) malloc ( sizeof ( char ) *  ( floatlength + 1 ) ) ;
		floatPart[ floatlength ] = '\0' ;
		int i = floatlength - 1 ;
		bool flag = false ;
		int firstNonZero = -1 ;
		for (  auto j = num1.cend()-1,k=num2.cend()-1 ; i >= 0 ; --i,--j,--k )
		{
			unsigned tem = *j + *k -'0' -'0' ;
			if ( flag )
				++tem ;
			if ( tem >= 10 )
			{
				tem -= 10 ;
				flag = true ;
			}
			else
				flag = false ;
			floatPart[ i ] = tem + '0' ;
			if ( firstNonZero == -1 && tem )
				firstNonZero = i ;
		}
		int intLength = ( dotPosition1 > dotPosition2 ? dotPosition1 : dotPosition2 ) + 2 ;//第一位可能有进位
		char *intPart = ( char * ) malloc ( sizeof( char )* intLength ) ;
		intPart[0] = '0';
		intPart[ intLength - 1 ] = '\0' ;
		int beginIndex = intLength - 2 ;//起始下标
		int intIndex1 = dotPosition1 - 1 ;
		int intIndex2 = dotPosition2 - 1 ;
		while ( ( intIndex1 >= 0 ) && ( intIndex2 >= 0 ) )
		{
			int tem = num1[intIndex1] + num2[ intIndex2 ] - '0' - '0' ;
			if ( flag )
				++tem ;
			if ( tem >= 10 )
			{
				tem-= 10 ;
				flag = true ;
			}
			else 
				flag = false ;
			intPart[ beginIndex ] = tem + '0' ;
			--beginIndex ;
			--intIndex1 ;
			--intIndex2 ;
		}
		while ( intIndex1 >=0 )
		{
			int tem = num1[intIndex1] -'0' ;
			if ( flag )
				++tem ;
			if ( tem >= 10 )
			{
				tem-= 10 ;
				flag = true ;
			}
			else 
				flag = false ;
			intPart[ beginIndex ] = tem + '0' ;
			--beginIndex ;
			--intIndex1 ;
		}
		while ( intIndex2 >=0 )
		{
			int tem = num2[intIndex2] -'0' ;
			if ( flag )
				++tem ;
			if ( tem >= 10 )
			{
				tem-= 10 ;
				flag = true ;
			}
			else 
				flag = false ;
			intPart[ beginIndex ] = tem + '0' ;
			--beginIndex ;
			--intIndex2 ;
		}
		if ( flag )
			intPart[ beginIndex ] += 1 ;
		if ( intPart[ 0 ] != '0' ) 
			cout << intPart ;
		else
			cout << intPart+1 ;
		if ( firstNonZero != -1 )
			cout << '.' << floatPart << endl ;
		else
			cout << endl ;
	}
	return 0 ;
}
size_t findDot( string &num )//寻找逗号所在下标。
{
	size_t offSet ;
	size_t length = num.size() ;
	for ( offSet = 0 ; offSet != length ; ++offSet )
	{
		if ( num[ offSet ] == '.' )
			return offSet;
	}
	num += '.' ;
	return offSet ;
}
