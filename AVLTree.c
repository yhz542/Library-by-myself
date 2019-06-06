#include<stdio.h>
#include<stdlib.h>
typedef struct TreeNode *AVLTree ;
typedef AVLTree Position ;
typedef int ElementType ;
struct TreeNode
{
        ElementType Data ;
        AVLTree Left ;//左子树
        AVLTree Right ;//右子树
        int Height ;//树高
};
void PreOrderTraversal( AVLTree );//先序遍历
void InOrderTraversal( AVLTree );//中序遍历
void PostOrderTraversal( AVLTree );//后序遍历
Position Find( ElementType X , AVLTree BST );//查找
//平衡二叉树自适应插入
int Max( int , int ) ;
int GetHeight( AVLTree );
AVLTree SingleLeftRotation( AVLTree );
AVLTree SingleRightRotation( AVLTree) ;
AVLTree DoubleLeftRightRotation( AVLTree );
AVLTree DoubleRightLeftRotation( AVLTree );
AVLTree Insert( AVLTree , ElementType X ) ;
//平衡二叉树自适应插入
AVLTree FindMax( AVLTree ) ;
AVLTree FindMin( AVLTree ) ;
AVLTree Delete( AVLTree , ElementType ) ;
//平衡二叉树自适应删除
int main(void)
{
        int amount = 0 ;
        scanf("%d" ,&amount ) ;
        AVLTree T = NULL ;
        for ( int i = 0 , tem ; i < amount ; ++i )
        {
                scanf("%d" , &tem ) ;
                T = Insert( T , tem ) ;
        }
        printf("输入删除元素:");
        scanf("%d",&amount);
        T=Delete(T,amount);//注意删除操作的用法.
        PreOrderTraversal( T ) ;
        putchar('\n') ;
        InOrderTraversal( T ) ;
        putchar('\n') ;
        PostOrderTraversal( T ) ;
        return 0 ;
}
void PreOrderTraversal( AVLTree BT )
{
        if( BT )
        {
                printf( "%d" , BT->Data ) ;
                PreOrderTraversal( BT->Left ) ;
                PreOrderTraversal( BT->Right ) ;
        }
}
void InOrderTraversal( AVLTree BT )
{
        if( BT )
        {
                InOrderTraversal( BT->Left ) ;
                printf( "%d" , BT->Data ) ;
                InOrderTraversal( BT->Right ) ;
        }
}
void PostOrderTraversal( AVLTree BT )
{
        if( BT )
        {
                PostOrderTraversal( BT->Left ) ;
                PostOrderTraversal( BT->Right ) ;
                printf( "%d" , BT->Data ) ;
        }
}
Position Find( ElementType X , AVLTree BST )
{
        if( !BST )
                return NULL;
        if( X > BST->Data )
                return Find( X , BST->Right ) ;
        else if( X < BST->Data)
                return Find( X , BST->Left ) ;
        else
                return BST;//查找成功
}
int GetHeight( AVLTree A )
{
        int Height ;
        if( !A )
                Height = -1 ;
        else
                Height = A->Height ;
        return Height ;
}
int Max( int a , int b )
{
        return a > b ? a : b ;
}
AVLTree SingleLeftRotation( AVLTree A )
{
        AVLTree B = A->Left ;
        A->Left = B->Right ;
        B->Right = A ;
        A->Height = Max( GetHeight(A->Left) , GetHeight(A->Right))+1;
        B->Height = Max( GetHeight(B->Left) , A->Height)+1;
        return B;
}
AVLTree SingleRightRotation( AVLTree A )
{
        AVLTree B = A->Right ;
        A->Right = B->Left ;
        B->Left = A ;
        A->Height = Max( GetHeight(A->Left) , GetHeight(A->Right))+1;
        B->Height = Max( GetHeight(B->Right) , A->Height )+1;
        return B ;
}
AVLTree DoubleLeftRightRotation( AVLTree A )
{
        A->Left = SingleRightRotation(A->Left);
        return SingleLeftRotation(A);
}
AVLTree DoubleRightLeftRotation( AVLTree A )
{
        A->Right = SingleLeftRotation(A->Right) ;
        return SingleRightRotation( A ) ;
}
AVLTree Insert( AVLTree T , ElementType X )
{
        if(!T)//如果当前为空树，创建并插入子节点
        {
                T=(AVLTree)malloc(sizeof( struct TreeNode ) );
                T->Data = X ;
                T->Height = 0 ;
                T->Left = T->Right = NULL;
        }
        else if( X < T->Data )//插入左边
        {
                T->Left = Insert( T->Left , X );
                if( GetHeight(T->Left) - GetHeight( T->Right ) == 2 )
                        if( X < T->Left->Data )
                                T = SingleLeftRotation( T );
                        else
                                T = DoubleLeftRightRotation( T ) ;
        }
        else if( X > T->Data )//插入右边
        {
                T->Right = Insert( T->Right , X ) ;
                if( GetHeight( T->Left ) - GetHeight( T->Right ) == -2 )
                        if( X > T->Right->Data )
                                T = SingleRightRotation( T ) ;
                        else
                                T = DoubleRightLeftRotation( T ) ;
        }
        T->Height = Max( GetHeight( T->Left ) , GetHeight( T->Right ) ) + 1 ;//左右两边的最大高度加上自身这一层
        return T ;
}
//每次插入点只会将路径上的所有节点高度加一，不在路径上的节点不做任何操作。
AVLTree FindMax( AVLTree T )
{
        if ( T )
                while( T->Right )
                        T = T->Right ;
        return T ;
}
AVLTree FindMin( AVLTree T )
{
        if ( T )
                while( T->Left )
                        T = T->Left ;
        return T ;
}
AVLTree Delete( AVLTree T , ElementType X )
{
        if ( !T )
        {
                printf("无此节点！") ;
                return NULL ;
        }
        else if ( X < T->Data )
        {
                T->Left = Delete( T->Left , X ) ;
                if( GetHeight(T->Left) - GetHeight( T->Right ) == -2 )//右边较高
                {
                        if ( GetHeight( T->Right->Right ) >= GetHeight( T->Right->Left ) )
                                T = SingleRightRotation( T ) ;
                        else
                                T = DoubleRightLeftRotation( T ) ;
                }
        }
        else if ( X > T->Data )
        {
                T->Right = Delete( T->Right , X ) ;
                if( GetHeight( T->Left ) - GetHeight( T->Right ) == 2 )
                {
                        if ( GetHeight( T->Left->Left ) >= GetHeight( T->Left->Right ) )
                                T = SingleLeftRotation( T ) ;
                        else
                                T = DoubleLeftRightRotation( T ) ;
                }
        }
        else
        {

                if ( T->Left && T->Right )//左右子树都存在
                {
                        int LeftHeight = GetHeight( T->Left ) ;
                        int RightHeight = GetHeight( T->Right ) ;
                        if ( LeftHeight > RightHeight )
                        {
                                ElementType Tem = FindMax( T->Left )->Data ;//找到左子树中值最大的结点并获取它的值
                                T->Left = Delete( T->Left , Tem ) ;//删除该结点
                                T->Data = Tem ;//将找到的当前结点存储的值设置为左子树中的最大值
                        }//这一步的思想是偷梁换柱，删除当前结点后用左子树的最大结点进行代替。因为高度可能会下降，所以用较高的树进行删除操作。
                        else
                        {
                                ElementType Tem = FindMin( T->Right )->Data ;//与上步同理。
                                T->Right = Delete( T->Right , Tem ) ;
                                T->Data = Tem ;
                        }
                }
                else if ( T->Left )
                {
                        AVLTree New = T->Left ;
                        free( T ) ;
                        return New ;
                }
                else if ( T->Right )
                {
                        AVLTree New = T->Right ;
                        free( T ) ;
                        return New ;
                }
                else
                {
                        free( T ) ;
                        return NULL ;
                }
        }
        T->Height = Max( GetHeight( T->Left ) , GetHeight( T->Right ) ) + 1 ;
        return T ;
}
