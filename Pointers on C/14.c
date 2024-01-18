void print_ledger_long(int);
void print_ledger_detailed(int);
void print_ledger_default(int);
//14-1
void print_ledger(int num)
{
    #ifdef OPTION_LONG
    print_ledger_long(num);
    #define OPTION
    #endif
    #ifdef OPTION_DETAILED
    print_ledger_detailed(num);
    #define OPTION
    #endif
    #ifndef OPTION
    print_ledger_default(num);
    #endif
}


#include "cpu_type.h"
//14-2
int cpu_type()
{
    #if defined(VAX)
    return CPU_VAX;
    #elif defined(M68000)
    return CPU_68000;
    #elif defined(M68020)
    return CPU_68020;
    #elif defined(I80386)
    return CPU_80386;
    #elif defined(X6809)
    return CPU_X6809;
    #elif defined(U3B2)
    return CPU_3B2;
    #else
    return CPU_UNKNOWN;
}

