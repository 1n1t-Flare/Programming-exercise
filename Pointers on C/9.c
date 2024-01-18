#include<stdio.h>
#include<ctype.h>
#include<string.h>
//9-1
void char_static(const char *str)
{
    static int ctrl,space,digit,lchar,uchar,punct,unprint;
    const char *cp=str;
    for (;*cp !='\0';cp++)
    {
        if (iscntrl(*cp)) ctrl++;
        if (isspace(*cp)) space++;
        if (isdigit(*cp)) digit++;
        if (islower(*cp)) lchar++;
        if (isupper(*cp)) uchar++;
        if (ispunct(*cp)) punct++;
        if (!isprint(*cp)) unprint++;
    }
    double len = (double)(cp-str);
    printf("control chars:      %.3f\n",ctrl/len);
    printf("space chars:        %.3f\n",space/len);
    printf("digits:             %.3f\n",digit/len);
    printf("lower chars:        %.3f\n",lchar/len);
    printf("upper chars:        %.3f\n",uchar/len);
    printf("puncts:             %.3f\n",punct/len);
    printf("unprintable chars:  %.3f\n",unprint/len);
}

//9-2
int my_strlen(const char*str,size_t length)
{
    for (size_t i=0;i<=length;i++)
    {
        if(*(str+i)=='\0') return i;
    }
    return length;
}

//9-3

char *my_strcpy(char *dst,const char *src,size_t dst_len)
{
    int overflow = 1;
    char *cpy=dst;
    for (; cpy-dst<dst_len; cpy++,src++)
    {
        if(*src == '\0') {overflow = 0; break;}
        *cpy = *src;
    }
    overflow? (*(cpy-1)='\0'): (*cpy='\0');
    return dst;
}
/*
{
    char *cpy = dst;
    for (; cpy-dst<dst_len; cpy++,src++)
    {
        if(*src == '\0') 
        {
            cpy++;
            break;
        }
        *cpy = *src;
    }
    *--cpy = '\0';
    return dst;
}
*/

//9-4
char *my_strcat(char *dst,char *src,size_t dst_len)
{
    int overflow = 1;
    char *cat = dst;
    for (;*cat !='\0';cat++);
    while (cat-dst < dst_len)
    {
        if(*src =='\0') {overflow = 0; break;}
        *cat = *src;
        cat++,src++;
    }
    overflow? (*(cat-1)='\0'): (*cat='\0');
    return dst;
}


//9-5 
//以下代码来自C & pointers official answer
//功能和上面my_strcat一样，只是溢出时截取的字符串不加NUL。感觉安全性不如上面的  
void my_strncat(char *dst, char *src, size_t dst_len)
{
    dst_len -= strlen(dst)+1;
    if (dst_len > 0)
    {
        strncat(dst,src,dst_len)
    }

}
//strncat(dst,src,dst_len-strlen(dst)-1)

//9-6
char *my_strcpy_end(char *dst,const char *src)
{
    for (;*dst!='\0';dst++);
    for (;*src!='\0';src++)
    {
        *dst = *src;
        dst++;
    }
    *dst='\0';
    return dst;
}

//9-7
char *my_strrchr(const char *str,int ch)
{
    const char *rchr = NULL;
    for (;*str!='\0';str++)
    {
        if(*str == ch) rchr = str;
    }
    return (char*)rchr;
}


//9-8
char *my_strnchr(const char *str,int ch,int which)
{
    static int count;
    for (;*str!='\0';str++)
    {
        if (*str == ch) count++;
        if (count == which) return (char*)str;
    }
    return NULL;
}

//9-9
int count_chars(const char *str,const char *chars)
{
    static int count;
    while ((str = strpbrk(str,chars)) != NULL)
    {
        count++;
        str++;
    }
    return 
}

// a mistake ~QaQ~
// in fact it is "count substr"
int __count_chars(const char *str,const char *chars)
{
    static int count;
    const char *search = chars;
    for (;*str!='\0';str++)
    {
        if (*str == *search) search++;
        if (*search =='\0')
        {
            count++;
            search = chars;
        }
    }
    return count;
}

//9-10
int palindrome(char *string)
{
    char *rstring = string;
    for (; *rstring!='\0';rstring++);
    //char *rstring = string + strlen(string);

    for (;string < rstring; string++,rstring--)
    {
        while(!isalpha(*string)) string++;
        while(!isalpha(*rstring)) rstring--;
        if(tolower(*string) != tolower(*rstring)) return 0;
    }
    return 1;
}


//9-11
int scan_the(const char *str)
{
    const char target[] = "the";
    const char *word = NULL;
    int start = 1,end = 1,count = 0;
    for (;*str!='\0';str++)
    {
        if (!isspace(*str) && start)
        {
            start = 0;
            end = 1;
            word = str;
        }
        if (isspace(*str) && end)
        {
            start = 1;
            end = 0;
            if (!strncmp(word,target,str-word)) count++;
        }
    }
    if (!strncmp(word,target,str-word)) count++;
    return count; 
}



//9- 12 and 13 and 14
void remove_zerochr(char *str)
{
    char *cp = str;
    //str遍历找到非零chr，保存在cp指向
    for (;*str!='\0';str++)
    {
        if (*str != '0')
        {
            *cp = *str;
            cp++;
        }
    }
    *cp = '\0';
}
int prepare_key(char *key)
{
    char *str = key;
    char ALPHABET[27]="ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    for (;*key!='\0';key++)
    {
        if (!isalpha(*key)) return 0;
        *key = toupper(*key);
        for (int i=0;i<=26;i++)
        {
            if (i==26) *key ='0';
            if (*key == ALPHABET[i])  
            {
                *(ALPHABET+i) ='0';
                break;
            }
        }
    }
    remove_zerochr(ALPHABET);
    remove_zerochr(str);
    strcat(str,ALPHABET);
    return 1;
}


void encrypt(char *data,char const *key)
{
    char ALPHABET[27]="ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    for (;*data!='\0';data++)
    {
        if (islower(*data)) 
        {
            for (int i=0;i<26;i++)
            {
                if (toupper(*data) == *(ALPHABET+i)) {*data = tolower(*(key+i));break;}
            }
        }
        else if (isupper(*data))
        {
            for (int i=0;i<26;i++)
            {
                if (*data == *(ALPHABET+i)) {*data = *(key+i);break;}
            }
        }
        else continue;
    }
}

void decrypt(char *data,char const *key)
{
    char ALPHABET[27]="ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    for (;*data!='\0';data++)
    {
        if (islower(*data)) 
        {
            for (int i=0;i<26;i++)
            {
                if (toupper(*data) == *(key+i)) {*data = tolower(*(ALPHABET+i));break;}
            }
        }
        else if (isupper(*data))
        {
            for (int i=0;i<26;i++)
            {
                if (*data == *(key+i)) {*data = *(ALPHABET+i);break;}
            }
        }
        else continue;
    }
}


//9-15
void dollers(char *dst,const char *src)
{
    int length = strlen(src);
    *dst++ = '$';
    for (int i=0; i<length-2; i++)
    {
        static int brk = (length-2)%3;
        if (i%3 == brk) 
        {
            if (i) *dst++ = ',';
        }
        *dst++ = *(src+i);
    }
    if (*(dst-1)== '$') *dst++ = '0';
    *dst++ = '.';
    for (int k=2; k>0; k--)
    {
        if (length >= k) *dst++ =*(src+length-k);
        else *dst++ ='0';
    }
    *dst = '\0';
}
/*
for (int k=3;k>0;k--)
{
    switch()
}
*/

//the whitespace is changed to '@' for visual print
//9-16
int format(char *format_string,const char *digit_string)
{
    size_t digit_len = strlen(digit_string), fstr_len=0;
    char *fstr_start = format_string;
    const char *digit_start = digit_string;
    int have_Lpoint = 0, end_digit = 0;
    if (!digit_len) return 0;
    for (; *format_string!='\0'; format_string++)
    {
        if (*format_string == '#') fstr_len++;
        if (*format_string == '.') have_Lpoint = 1;
    }
    for (; *digit_string!='\0'; digit_string++);
    for (format_string--,digit_string--; format_string >= fstr_start; format_string--)
    {
        if(digit_string < digit_start) end_digit = 1;
        switch (*format_string)
        {
        case '#':
            if (have_Lpoint <0)
            {
                *format_string = '0';
                have_Lpoint = 0;
            }
            else if (end_digit && (have_Lpoint==0)) *format_string = '@';
            else if (end_digit && have_Lpoint) *format_string = '0';
            else *format_string = *digit_string--;
            break;
        case '.':
            if(end_digit) have_Lpoint = -1;
            else have_Lpoint = 0;
            break;
        case ',':
            if(end_digit) *format_string = '@';
            break;
        }
    }
    if (fstr_len < digit_len) return 0;
    else return 1;
    // return fstr_len >= digit_len;
}


/*there is a bug about ',' */
//9-17
char *edit(char *patten,const char *digits)
{
    int signif = 0;
    char *retprt = NULL;
    char fillchar = *patten;
    for (patten++;*patten!='\0';patten++)
    {
        if (*digits == '\0') 
        {
            *patten = '\0';
            return retprt;
        }
        if (*digits != '0' && *digits != ' ') 
        {
            if(!signif)
            {
                signif =1;
                retprt = patten;
            }
        }
        switch(*patten)
        {
        case '#':
            if (signif) 
            {
                if(*digits == ' ') *patten = '0';
                else *patten = *digits;
                digits++;
            }
            else 
            {
                *patten = fillchar;
                digits++;
            }
            break;
        case '!':
            if (signif) *patten = *digits++;
            else
            {
                signif =1;
                retprt = patten;
                if(*digits == ' ') *patten = '0';
                else *patten = *digits;
                digits++;
            }
            break;
        default:
            if (!signif) *patten = fillchar;
            break;
        }
    }
    return retprt;
}


int main()
{
    
    gets(str);
    char_static(str); 

    
    char word[27]="TRAILBLAZERS";
    char str[100]="ATTACK AT DAWN";
    prepare_key(word);
    encrypt(str,word);
    decrypt(str,word);
    

    char dol[]="12345";
    char resurt[30]={0};
    dollers(resurt,dol);
    
    char digit[]="123456";
    char s[]="##,##.###";
    int t=format(s,digit);
    printf("%s\n",s);
    printf("%d\n",t);

    char strf[]="$#,##!.##";
    char dig[]="0";
    edit(strf,dig);
    printf("%s\n",strf);
    printf("%s",str);
    return 0;
}