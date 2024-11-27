#include <stdio.h>
#include <stdlib.h>

void frequency_count_char(char*);
unsigned long long int string_length(char*);

int main(void)
{
    char* string = "{w9[M84]$!mjDXP/ *Vf?aHaTbB9p.:qP, Kx*Sw9qE: f&%T8f%VUf{@]c6McM.ir8Nbuz&Q3X5n%49!yuG;G!8kXRw,C{ZE]_(LzDFe7(;cB#EDuC]4c}5Gya-x/0)U2#hPkPZGdRNE.weaGmAG5,6]";

    frequency_count_char(string);

    exit(0);
}

void frequency_count_char(char* string)
{
    unsigned long long int length;
    length = string_length(string);
    char current_char;
    unsigned long long int i;
    i = 0;
    unsigned long long int count;
    
    while(i < length)
    {
        count = 0;
        current_char = string[i];
        unsigned long long int j;
        j = 0;
        while(j < i)
        {
            if(string[j] == current_char)
            {
                break;
            }
            j = j + 1;
        }

        if(j < i)
        {
            i = i + 1;
            continue;
        }

        if(j == i)   
        {
            j = 0;
            while(j < length)
            {
                if(string[j] == current_char)
                {
                    count = count + 1;
                }
                j = j + 1;
            }
            printf("char = [%c], count [%llu]\n", current_char, count);
        }
        i = i + 1;
    }

}

unsigned long long int string_length(char* string)
{
    unsigned long long int length = 0;
    unsigned long long int i;
    i = 0;
    while(string[i] != '\0')
    {
        length = length + 1;
        i = i + 1;
    }

    return (length);
}
