#include <stdio.h>
#include <stdlib.h>

char* only_alphabet(char*);
unsigned long long int string_length(char* string);

int main(void)
{
    char* string = "Shubham 1233 3434 343  32423%*&T&TR*R*&T*&R**$*$$848";
    char* new_string = NULL;

    new_string = only_alphabet(string);
    printf("only alphabet string [%s]\n", new_string);

    free(new_string);
    new_string = NULL;
    exit(0);
}

char* only_alphabet(char* string)
{
    char* new_string = NULL;
    unsigned long long int i;
    i = 0;
    unsigned long long int length = 0;
    while(string[i] != '\0')
    {
        if((string[i] >= 'A' && string[i] <= 'Z') || (string[i] >= 'a' && string[i] <= 'z'))
        {
            new_string = realloc(new_string, (length + 1) * sizeof(char));
            if(new_string == NULL)
            {
                puts("Error in allocating the meomary");
                exit(-1);
            }
            length = length + 1;
            new_string[length - 1] = string[i];
        }
        i = i + 1;
    }
    new_string = realloc(new_string, (length + 1) * sizeof(char));
     if(new_string == NULL)
    {
        puts("Error in allocating the meomary");
        exit(-1);
    }  
    length = length + 1;
    new_string[length - 1] = '\0';
    return (new_string);
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