#include<stdio.h>
//10-1
struct Phone
{
    int num1;
    int num2;
    int num3;
};
struct PhoneInfo
{
    char date[10];
    char time[10];
    struct Phone src_phone;
    struct Phone dst_phone;
    struct Phone pay_phone;
};
/*another:
enum PHONE_TYPE{CALLED, CALLING, BILLED}

struct PhoneInfo
{
    ...
    struct Phone numbers[3];
}
*/


//10-2
struct FullCash
{
    float suggest_price;
    float actual_price;
    float sales_tax;
    float licensing_fee;
};
struct Rent
{
    float suggest_price;
    float actual_price;
    float down_payment;
    float security_deposit;
    float monthly_payment;
    int lease_term;
};
struct Loan
{
    float suggest_price;
    float actual_price;
    float sales_tax;
    float licensing_fee;
    float down_payment;
    int loan_duration;
    float interest_rate;
    float monthly_payment;
    char bank_name[20];
};
struct SaleInfo
{
    char name[20];
    char address[40];
    char model[20];
    enum {FULLCASH, RENT, LOAN} type;
    union
    {
        struct FullCash cashinfo;
        struct Rent rentinfo;
        struct Loan loaninfo;
    }info;
};


//10-3
struct MISC
{
    unsigned opcode:16;
};
struct BRANCH
{
    unsigned offset:8;
    unsigned opcode:8;
};
struct SGL_OP
{
    unsigned dst_reg:3;
    unsigned dst_mode:3;
    unsigned opcode:10;
};
struct DBL_OP
{
    unsigned dst_reg:3;
    unsigned dst_mode:3;
    unsigned src_reg:3;
    unsigned src_mode:3;
    unsigned opcode:4;
};
struct REG_SRC
{
    unsigned dst_reg:3;
    unsigned dst_mode:3;
    unsigned src_reg:3;
    unsigned op_code:7;
};

typedef union 
{
    unsigned short addr;
    struct MISC misc;
    struct BRANCH branch;
    struct SGL_OP sgl_op;
    struct REG_SRC reg_ssrc;
    struct DBL_OP dbl_op;    
}machine_inst;

int main()
{
    machine_inst x;
    return 0;
}