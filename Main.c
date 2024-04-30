#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char keyWords[][10] = {"int", "text", "is", "loop", "times", "read", "write", "newLine"};

int isKeyWord(char word[])
{
    int i = 0;
    while (strcmp(keyWords[i], "") != 0)
    {
        if (strcmp(word, keyWords[i]) == 0)
            return 1;
        i++;
    }
    return 0;
}

char *tokenControl(char *string)
{
    char firstChar = string[0];
    char lastChar = string[strlen(string) - 1];
    char *ret = malloc(strlen(string) + 10);
    // keyWord Control
    if (isKeyWord(string))
    {
        sprintf(ret, "KeyWord(%s)", string);
        return ret;
    }
    // Identifier Control
    else if (isalpha(firstChar))
    {
        int i = 0;
        while ((isdigit(string[i]) || string[i] == '_' || isalpha(string[i])) && string[i] != '\0')
        {
            i++;
        }
        if (i == strlen(string) && strlen(string) <= 10)
        {
            sprintf(ret, "Identifier(%s)", string);
            return ret;
        }
        else if (strlen(string) > 10 && i == strlen(string))
        {
            printf("Identifier lenght cannot be larger than 10!");
            exit(1);
        }
        else
        {
            printf("Unavailable token type name!");
            exit(1);
        }
    }
    // Operator Control
    else if ((firstChar == '+' || firstChar == '-' || firstChar == '*' || firstChar == '/') && strlen(string) == 1)
    {
        sprintf(ret, "Operator(%c)", firstChar);
        return ret;
    }
    // Integer constant control
    else if (isdigit(firstChar) || firstChar == '-')
    {
        int k = 0;
        if (firstChar == '-')
        {
            while (isdigit(string[k + 1]) && string[k + 1] != '\0')
            {
                k++;
            }
            if (strlen(string) == k + 1)
            {
                return "IntConst(0)";
            }
            else
            {
                return "Unavailable token type name!";
            }
        }

        int i = 0;
        while (isdigit(string[i]) && string[i] != '\0')
        {
            i++;
        }
        if (strlen(string) == i && strlen(string) <= 8)
        {
            sprintf(ret, "IntConst(%s)", string);
            return ret;
        }
        else if (strlen(string) > 8 && i == strlen(string))
        {
            printf("Integer constant  lenght cannot be larger than 8!");
            exit(1);
        }
        // TODO: ADD 0 VALUE CHANGE NEGATİVE VALUES.
        else
        {
            printf("Unavailable token type name!");
            exit(1);
        }
    }
  
    else if (firstChar == '{' || firstChar == '}')
    {
        sprintf(ret, "CurlyBracket(%c)", firstChar);
        return ret;
    }
    // String Const control
    else if (firstChar == '"' && lastChar == '"')
    {
        int b = strlen(string) - 2;
        char copy[b];
        strncpy(copy, string + 1, b);
        copy[b] = '\0';

        char karakter = '"';
        char *result = strchr(copy, karakter);

        if (strlen(copy) > 256)
        {
            printf("String constant cannot exceed 256 characters.!");
            exit(1);
        }
        else if (result != NULL)
        {
            printf("String constant cannot include '\"' character.!");
            exit(1);
        }
        else
        {
            sprintf(ret, "String(\"%s\")", copy);
            return ret;
        }
    }
    // End of Line Control
    else if (firstChar == '.' && strlen(string) == 1)
    {
        return "EndOfLine";
    }
    

}

int main()
{
    //deneme1  
    int ab = '"';
    char *bb = tokenControl(".");
    char *kk = "arab";
    printf("%s\n", bb);
    char denem[] = "\"araba";
}