#include <stdio.h>
#include <stdlib.h>

struct Date{
    int name;
};

int main(void){

    char* p_ch = NULL;
    short* p_sh = NULL;
    int* p_int = NULL;
    long int* p_lo_int = NULL;
    long long int* p_lng_lng = NULL;
    float* p_flt = NULL;
    double* p_dble = NULL;
    struct Date* date = NULL;
    int (*pa)[5];
    double (*pd)[3];

    printf("pointer= %llu\n", p_ch + 1);
    printf("pointer= %llu\n", p_sh + 1);
    printf("pointer= %llu\n", p_int + 1);
    printf("pointer= %llu\n", p_lo_int + 1);
    printf("pointer= %llu\n", p_lng_lng + 1);
    printf("pointer= %llu\n", p_flt + 1);
    printf("pointer= %llu\n", p_dble + 1);
    printf("pointer= %llu\n", date + 1);
    printf("pointer= %llu\n", pa + 1);
    printf("pointer= %llu\n", pd + 1);

    p_ch = 100;
    p_sh = 100;
    p_int = 100;
    p_lo_int = 100;
    p_lng_lng = 100;
    p_flt =    100;
    p_dble = 100;
    date = 100;
    pa = 100;
    pd = 100;

    printf("pointer= %llu\n", p_ch - 1);
    printf("pointer= %llu\n", p_sh - 1);
    printf("pointer= %llu\n", p_int - 1);
    printf("pointer= %llu\n", p_lo_int - 1);
    printf("pointer= %llu\n", p_lng_lng - 1);
    printf("pointer= %llu\n", p_flt - 1);
    printf("pointer= %llu\n", p_dble - 1);
    printf("pointer= %llu\n", date - 1);
    printf("pointer= %llu\n", pa - 1);
    printf("pointer= %llu\n", pd - 1);

    return 0;
}