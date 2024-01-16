#include <stdio.h>
#include <math.h>
//5-1
void printout()
{
    char c;
    scanf("%c",&c);
    if (c>='A'&&c<'Z')
        c+=32;
    putchar(c);
}


//5-2
void Caesar()
{
    char c;
    scanf("%c",&c);
    if (c>='a'&&c<='z')
    {
        c='a'+(c-'a'+13)%26;
    }
    if (c>='A'&&c<='Z')
    {
        c='A'+(c-'A'+13)%26;
    }
    putchar(c);
}


//5-3
unsigned int reverse_bits(unsigned int value)
{
    int bits[32]={0};
    unsigned int result=0;
    for (int i=0;i<32;i++)
    {
        if(value%2==1) *(bits+i)=1;
        value>>=1;
    }
    for (double k=0;k<32;k++)
    {
        result += *(bits+(int)k)*pow(2.0,31-k);
    }
    return result;
}



//5-4   suitable for computers whose CHAR_BIT eaquls to 8.
void set_bit(char* bit_array,unsigned bit_number)
{
    *(bit_array+bit_number/8) |= (1 << bit_number % 8);
}

void clear_bit(char* bit_array,unsigned bit_number)
{
    *(bit_array+bit_number/8) &= ~(1 << bit_number % 8);
}

void assign_bit(char* bit_array,unsigned bit_number,int value)
{
    if (value) set_bit(bit_array,bit_number);
    else       clear_bit(bit_array,bit_number);
}

int test_bits(char* bit_array,unsigned bit_number)
{
    unsigned test = 1 << bit_number % 8;
    test &= *(bit_array+bit_number/8);
    if (test) return 1;
    else      return 0;
}


//5-5
unsigned int store_bit_field(int original_value,int value_to_store,unsigned starting_bit,unsigned ending_bit)
{
    unsigned result=0;
    unsigned rmask = ~0u>>ending_bit<<ending_bit;
    unsigned lmask = ~0u<<31-starting_bit>>31-starting_bit;
    unsigned mask = rmask & lmask;
    unsigned outbit_value = original_value & ~mask;
    unsigned inbit_value = (value_to_store << ending_bit) & mask;
    result = outbit_value | inbit_value;
    return result;
}


int main()
{
    unsigned int t=store_bit_field(0xffff,0x123,13,9);
    return 0;
}
