#include <stdio.h>
#include <string.h>
#include "main.h"

int main()
{
    char filename[50];
    int top=-1;

    printf("Enter the file name with extension\n");
    scanf("%s",filename);

    if(validate_file(filename)==1)
    {
        printf("INFO:: Invalid file\n");
        return 0;
    }

    read_and_print_words(filename);
    // Check unbalanced symbols
    while (top >= 0) {
        char msg[100];
        sprintf(msg, "Unmatched opening '%c'", pop());
        addError(msg, -1); // -1 = unknown line (global)
    }


    printf("\n\n---------------- Summary Table -----------------\n");
    printf("%-20s %-20s %-10s\n", "Token", "Type", "Line No");
    printf("--------------------------------------------------\n");

    for (int i = 0; i < token_count; i++)
    {
        printf("%-20s %-20s %-10d\n", tokens[i].word, tokens[i].type, tokens[i].lineno);
    }
    
    if (error_count > 0) 
    {
        printf("\n\n---------------- Errors -----------------\n");
        for (int i = 0; i < error_count; i++)
        {
            if (errors[i].line_no != -1)
                printf("Line %d: %s\n", errors[i].line_no, errors[i].message);
            else
                printf("Error: %s\n", errors[i].message);
        }
    } 
    else 
    {
        printf("\nNo syntax errors detected.\n");
    }

}