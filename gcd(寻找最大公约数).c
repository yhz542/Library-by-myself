int gcd(int M,int N)
{
        int R = M % N ;
        if( !R )
                return N;
        else
                return gcd(N , R ) ;
}
//返回M和N的最大公约数 C和指针 中文版 函数章节P139 编程练习 第二题
