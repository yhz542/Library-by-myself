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
		if (Num%i == 0 || Num % (i + 2) == 0)//%i 表示6x+5 %(i+2)表示 6x+7也就是6x+1
			return false;
	return true;
}
/**********************************
因为6x-1 以及6x+1肯定不可能被偶数整除
所以6x 6x+2 6x+4 都不用进行判断,又6x+3肯定是3的倍数，但是6x-1 6x+1肯定不是3的倍数，所以6x+3也不用判断，只用判断6x+1 以及6x + 5(6x-1)
**********************************/
//https://blog.csdn.net/afei__/article/details/80638460
我们继续分析，其实质数还有一个特点，就是它总是等于 6x-1 或者 6x+1，其中 x 是大于等于1的自然数。

    如何论证这个结论呢，其实不难。首先 6x 肯定不是质数，因为它能被 6 整除；其次 6x+2 肯定也不是质数，因为它还能被2整除；依次类推，6x+3 肯定能被 3 整除；6x+4 肯定能被 2 整除。那么，就只有 6x+1 和 6x+5 (即等同于6x-1) 可能是质数了。所以循环的步长可以设为 6，然后每次只判断 6 两侧的数即可。

public static boolean isPrime(int num) {
    if (num <= 3) {
        return num > 1;
    }
    // 不在6的倍数两侧的一定不是质数
    if (num % 6 != 1 && num % 6 != 5) {
        return false;
    }
    int sqrt = (int) Math.sqrt(num);
    for (int i = 5; i <= sqrt; i += 6) {
        if (num % i == 0 || num % (i + 2) == 0) {
            return false;
        }
    }
    return true;
}
    对于输入的自然数 n 较小时，也许效果不怎么明显，但是当 n 越来越大后，该方法的执行效率就会越来越明显了。
————————————————
版权声明：本文为CSDN博主「阿飞__」的原创文章，遵循 CC 4.0 BY-SA 版权协议，转载请附上原文出处链接及本声明。
原文链接：https://blog.csdn.net/afei__/article/details/80638460
