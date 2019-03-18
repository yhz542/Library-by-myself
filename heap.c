#ifndef HEAP_H_INCLUDED
#define HEAP_H_INCLUDED
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#define MaxData 65535
#define MinData -65535
typedef struct HeapStruct *Heap ;
typedef struct HeapStruct *MinHeap ;
typedef struct HeapStruct *MaxHeap ;
typedef int ElementType ;
struct HeapStruct
{
        ElementType *Elements ;//存储堆元素的数组
        int Size ;//堆的当前元素个数
        int Capacity ;//堆的最大容量
};
MinHeap CreateMinHeap( int MaxSize )
{
        MinHeap H = ( MinHeap )malloc( sizeof( struct HeapStruct ) ) ;
        H->Elements = ( ElementType *)malloc ( sizeof( ElementType )*( MaxSize + 1 ) ) ;//空出下标为0的空间用于存放哨兵
        H->Size = 0 ;
        H->Capacity = MaxSize ;
        H->Elements[ 0 ] = MinData ;
        return H ;
}
MaxHeap CreateMaxHeap( int MaxSize )
{
        MaxHeap H = ( MaxHeap )malloc( sizeof( struct HeapStruct ) ) ;
        H->Elements = ( ElementType *)malloc ( sizeof( ElementType )*( MaxSize + 1 ) ) ;//空出下标为0的空间用于存放哨兵
        H->Size = 0 ;
        H->Capacity = MaxSize ;
        H->Elements[ 0 ] = MaxData ;
        return H ;
}
bool IsFull( Heap H )
{
        return ( H->Size == H->Capacity ) ;
}
void InsertMaxHeap( MaxHeap H , ElementType item )
{
        int i ;
        if ( IsFull( H ) )
        {
                printf("MaxHeap had been full\n") ;
                return ;
        }
        i = ++H->Size ;
        for ( ; H->Elements[ i / 2 ] < item ; i /= 2 )
                H->Elements[ i ] = H->Elements[ i / 2 ] ;
        printf("1111");
        H->Elements[ i ] = item ;
}
void InsertMinHeap( MinHeap H , ElementType item )
{
        int i ;
        if ( IsFull( H ) )
        {
                printf("MinHeap had been full\n") ;
                return;
        }
        i = ++H->Size ;
        for ( ; H->Elements[ i / 2 ] > item ; i /= 2 )
                H->Elements[ i ] = H->Elements[ i / 2 ] ;
        H->Elements[ i ] = item ;
}
bool IsEmpty( Heap H )
{
        return H->Size == 0 ;
}
ElementType DeleteMax( MaxHeap H )
{
        int Parent , Child ;
        ElementType MaxItem , temp ;
        if ( IsEmpty( H ) )
        {
                printf("MaxHeap had been empty\n") ;
                return -1;
        }
        MaxItem = H->Elements[ 1 ] ;
        temp = H->Elements[ H->Size-- ] ;
        for ( Parent = 1 ; Parent * 2 <= H->Size ; Parent = Child )//判断是否有左节点
        {
                Child = Parent * 2 ;
                if ( ( Child != H->Size ) && //Child不为最后一个元素下标
                ( H->Elements[ Child ] < H->Elements[ Child + 1 ] ) ) //选出更大的的元素下标
                        ++Child ;
                if ( temp >= H->Elements[ Child ] )
                        break ;
                H->Elements[ Parent ] = H->Elements[ Child ] ;
        }
        H->Elements[ Parent ] = temp ;
        return MaxItem ;
}
ElementType DeleteMin( MinHeap H )
{
        int Parent , Child ;
        ElementType MinItem , temp ;
        if ( IsEmpty( H ) )
        {
                printf("MinHeap had been empty\n") ;
                return -1;
        }
        temp = H->Elements[ H->Size-- ] ;
        MinItem = H->Elements[ 1 ] ;
        for ( Parent = 1 ; Parent * 2 <= H->Size ; Parent = Child )
        {
                Child = Parent * 2 ;
                if ( ( Child != H->Size ) && ( H->Elements[ Child ] > H->Elements[ Child + 1 ] ) )
                        ++Child ;
                if ( temp <= H->Elements[ Child ] )
                        break ;
                H->Elements[ Parent ] = H->Elements[ Child ] ;
        }
        H->Elements[ Parent ] = temp ;
        return MinItem ;
}
void PercDownMax( MaxHeap H , int p )
{
        int Parent, Child ;
        ElementType X ;
        X = H->Elements[ p ] ;
        for ( Parent = p ; Parent * 2 <=H->Size ; Parent = Child )
        {
                Child = Parent * 2 ;
                if ( (Child!=H->Size)&&( H->Elements[Child] < H->Elements[Child + 1 ] ) )
                        ++Child;
                if ( H->Elements[ Child ] <= X )
                        break;
                H->Elements[ Parent ] = H->Elements[ Child ] ;
        }
        H->Elements[ Parent ] = X ;
}
void BuildMaxHeap( MaxHeap H )
{
        int i ;
        for ( i = H->Size / 2 ; i > 0 ; --i )
                PercDownMax( H , i ) ;
}
void PercDownMin( MaxHeap H , int p )
{
        int Parent, Child ;
        ElementType X ;
        X = H->Elements[ p ] ;
        for ( Parent = p ; Parent * 2 <= H->Size ; Parent = Child )
        {
                Child = Parent * 2 ;
                if ( (Child!=H->Size)&&( H->Elements[Child] > H->Elements[Child + 1 ] ) )
                        ++Child;
                if ( H->Elements[ Child ] >= X )
                        break;
                H->Elements[ Parent ] = H->Elements[ Child ] ;
        }
        H->Elements[ Parent ] = X ;
}
void BuildMinHeap( MinHeap H )
{
        int i ;
        for ( i = H->Size / 2 ; i > 0 ; --i )
                PercDownMin( H , i ) ;
}
#endif // HEAP_H_INCLUDED
