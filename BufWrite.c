#define N 1024//缓冲区空间
static char buffer[N];
static char *bufptr;
bufptr = buffer;
//未改良版
void bufwrite(char *p , int n)// 每读取一个字符判断两次
{
  while(--n >= 0 )
  {
    if(bufptr == buffer + N ) 
      flushbuffer();
    *bufptr++ = *p++;
  }
}
//改良后
void memcpy(char *dest , const char *source , int k)//将source中的k个内容转移到dest中
{
  while( --k >= 0 )
  {
    *dest++ = *source++;
  }
}
void bufwrite(char *p,int n)
{
  int k , rem ;
  while( n > 0 )//每读取N个字符判断N+3次,总共判断 (N+3)n/N次
  {
    if( bufptr == buffer + N )
      flushbuffer();
    rem = N - (bufptr - buffer) ;//计算剩余字符数
    k = n > rem ? rem : n ;//k代表写入的字符长度
    memcpy( bufptr , p , k );
    bufptr += k ;
    n -= k;
    p += k ;
  }
}
//显然N越大，提升的效果越好
