#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<stdbool.h>
typedef int ElementType ;
typedef int Index ;
typedef Index Position ;
typedef enum { Legitimate , Empty , Deleted } EntryType ;
typedef struct HashEntry Cell ;
struct HashEntry
{
       ElementType Data ;
       EntryType Info ;
};
typedef struct TblNode *HashTable;
struct TblNode
{
        int TableSize ;
        Cell *Cells ;
};
HashTable CreateTable( int TableSize ) ;//创建哈希表 ，哈希表大小由函数自己确定
bool IsPrime( int );
Position Find( HashTable H , ElementType Key );//在哈希表中寻找KEY，找到返回其下标值，没找到返回找到的可用空位置。
bool Insert( HashTable H , ElementType Key) ;//此函数运行时，会先进行判断 KEY是否在表中，在表中时不插入。
int main(void)
{
        return 0;
}
HashTable CreateTable( int TableSize )
{
        TableSize *= 2 ;
        TableSize++ ;
        while( 1 )
        {
                if(IsPrime( TableSize ))
                        break ;
                TableSize += 2 ;
        }
        HashTable H ;
        int i ;
        H = ( HashTable )malloc(sizeof(struct TblNode)) ;
        H->TableSize = TableSize ;
        H->Cells = ( Cell * )malloc( sizeof(Cell) * H->TableSize ) ;
        for( i = 0 ; i < H->TableSize ; i++ )
                H->Cells[i].info = Empty ;
        return H ;
}
bool IsPrime( int Num )
{
        if( Num == 2 || Num == 5 || Num == 3 )//因子从7开始 所以 2，3，5作为因子单独测试，因为2，3，5分别被2，3，5整除
                return true ;                   //所以先观察是不是2，3，5，然后再看他们是否被2，3，5整除，如果直接整除2，3，5 ，那么2，3，5
        if( !( Num % 2 ) || ! ( Num % 5 ) || ! ( Num % 3 ) )//会被直接判定为非素数。
                return false ;
        int Max = ( int )sqrt( Num ) ;
        Max = (Max % 2) ? Max : Max - 1 ;
        for ( int i = 7 ; i <= Max ; i += 2 )
        {
                for( int j = 0 ; j < 4 ; j++ , i+=2 )
                {
                        if( !( Num % i) )
                                return false;
                }
        }
        if( Num<=1 )
                return false;
        return true;
}
Position Find( HashTable H , ElementType Key )
{
        Position CurrentPos , NewPos;
        int CNum = 0;//记录冲突次数
        NewPos = CurrentPos = Key % H->TableSize ;
        while( H->Cells[NewPos].Info!=Empty && H->Cells[NewPos].Data !=Key )
        {
                if(++CNum%2 )//奇数次冲突
                {
                        NewPos = CurrentPos + (CNum+1)*(CNum+1)/4 ;//向右移平方
                        if( NewPos >= H->TableSize )
                                NewPos = NewPos % H->TableSize ;
                }
                else
                {
                        NewPos = CurrentPos - CNum*CNum/4 ;//向左移平方
                        while( NewPos < 0 )//相当于求余运算
                                NewPos += H->TableSize ;
                }
        }
        return NewPos ;
}
bool Insert( HashTable H , ElementType Key )
{
        Position Pos = Find( H , Key ) ;
        if( H->Cells[ Pos ].Info != Legitimate )//未被占用
        {
                H->Cells[ Pos ].Info = Legitimate ;
                H->Cells[ Pos ].Data = Key ;
                return true ;
        }
        else
        {
                printf("键值已存在");
                return false;
        }
}
