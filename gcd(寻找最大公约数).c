int gcd(int M,int N)
{
        int R = M % N ;
        if( !R )
                return N;
        else
                return gcd(N , R ) ;
}
//返回M和N的最大公约数
