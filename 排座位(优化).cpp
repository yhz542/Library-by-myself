#include <iostream>//排座位 要安排：3个A国人，3个B国人，3个C国人坐成一排。 要求不能使连续的3个人是同一个国籍。 求所有不同方案的总数？
#include <string>
using namespace std;
unsigned cnt = 0 ;
void calculate( int [], int ) ;
bool check ( int *, int ) ;
int main()
{
	int data[ 9 ] = { 0 , 1 , 2 , 3 , 4 , 5 , 6 , 7 , 8 };
	calculate( data , 1 ) ;
	cout << cnt << endl ;
	return 0 ;
}
void calculate( int data[] , int layer )
{
	int tem ;
	for ( int i = layer - 1 ; i < 9 ; ++i )
	{
		tem = data[ layer - 1 ] ;
		data[ layer - 1 ] = data[ i ] ;
		data[ i ] = tem ;
		if ( layer >= 3 )
		{
			if ( (data[ layer-1 ]/3 == data[ layer - 2 ]/3) && (data[ layer - 3 ]/3 == data[ layer - 2 ]/3) )
			{
				tem = data[ layer - 1 ] ;
				data[ layer - 1 ] = data[ i ] ;
				data[ i ] = tem ;
				continue ;
			}
			else if ( 9 == layer )
			{
				++cnt ;
				return ;
			}	
		}
		calculate( data , layer + 1 ) ;
		tem = data[ layer - 1 ] ;
		data[ layer - 1 ] = data[ i ] ;
		data[ i ] = tem ;
	}
}
