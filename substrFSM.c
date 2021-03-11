//字符串匹配 有限状态机
//生成子串
char *getSubStr(char * const output,const char * const source,int start,int length)
{
        for(int i = 0 ; i < length ;++i)
        {
                if(source[start+i] != '\0')
                {
                        output[i] = source[start+i];
                }
                else
                        break;
        }
        return output;
}
//比较两个字符串后缀等于前缀的最大长度
int cmp(const char *former,const char *later)
{

        int len1 = strlen(former);
        int i;
        for( i = len1 ; i > 0 ; --i)
        {
                bool eq = true;
                int start = len1 -i;

                for(int j = 0 ; j < i ; ++j)
                {
                        if(former[start + j] != later[j])
                        {
                                eq = false;
                                break;
                        }
                }
                if( eq )
                        break;
        }
        return i;
}
char *newString;
//生成待匹配字符串的有限状态机
char **generateStrTable(const char *str)
{
        int cnt = 0;
        unsigned char charRecord[64];
        char *tem = (char *)str;
        memset(charRecord,0,sizeof(charRecord));
        while( *tem )//计算字符串中有多少个字母
        {
                if(!charRecord[*tem -'A'])
                {
                        charRecord[*tem -'A'] = 1;
                        ++cnt;
                }
                ++tem;
        }
        char *mapping = (char *)malloc(sizeof(char)*(cnt+1));//存储所有字母
        for(int i = 0 ,j = 0; j < cnt ;++i)
        {
                if(charRecord[i])
                {
                        mapping[j] = i+'A';
                        ++j;
                }
        }
        mapping[cnt] ='\0';
        int numOfChar = cnt + 1 ;//建立FSM的宽度(列)
        int numOfState = strlen(str) ;//FSM的高度(行)
        char **table = (char **)malloc(sizeof(char *)*numOfState);
        newString = (char *)malloc(sizeof(char)*(numOfState+1));
        memset(newString,0,sizeof(char)*(sizeof(str)+1));
        for(int i = 0 ; i < numOfState ; ++i )
        {
                table[i] = (char *)malloc(sizeof(char)*numOfChar);
                table[i][cnt] = 0;
                newString = getSubStr(newString,str,0,i);
                for(int j = 0 ; j < cnt ;++j)
                {
                        newString[i] = mapping[j];
                        newString[i+1] = '\0';
                        table[i][j]=cmp(newString,str);
                }
        }
        return table;
}
//在字符串中寻找字符下标
int findCharInStr(char c,const char *str)
{
        int index;
        for(index = 0 ; str[index] != '\0';index++)
        {
                if(c==str[index])
                        break;
        }
        return index;
}
//在source字符串中匹配target字符串，返回source匹配target字符串的最后一个字符指针
const char *find_str( const char * target,const char * source )
{
        char **table = generateStrTable(target);
        int index = 0;
        int state = 0;
        while( *source )
        {
                index = findCharInStr(*source,newString);
                state = table[state][index];
                if(state == strlen(target))
                        break;
                source++;
        }

        free(newString);
        //注意回收table
        return source;
}
