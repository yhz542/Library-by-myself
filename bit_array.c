//把指定位设置为1 从0开始
void set_bit(char bit_array[],unsigned bit_number)
{
        unsigned indexOfArray = bit_number / 8 ;
        unsigned indexOfBit = bit_number % 8;
        bit_array[indexOfArray] |= (1<<indexOfBit);
}
//把指定位清零
void clear_bit(char bit_array[],unsigned bit_number)
{
        unsigned indexOfArray = bit_number / 8 ;
        unsigned indexOfBit = bit_number % 8;
        bit_array[indexOfArray] &= ~(1<<indexOfBit);
}
//如果value=0,把指定位清零，否则设置为1
void assign_bit(char bit_array[],unsigned bit_number,int value)
{
        if(value)
        {
                set_bit(bit_array,bit_number);
        }
        else
        {
                clear_bit(bit_array,bit_number);
        }
}
//如果指定位不是0，就返回真，否则返回假
int test_bit(char bit_array[],unsigned bit_number)
{
        int result = 0;
        unsigned indexOfArray = bit_number / 8 ;
        unsigned indexOfBit = bit_number % 8;
        result = bit_array[indexOfArray] & (1<<indexOfBit);
        return result;
}
