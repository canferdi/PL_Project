#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/*enum tokenType
{
    IDENTIFIER,
    INTEGER,
    OPERATOR,
    BRACKET,
    STRING,
    KEYWORD,
    ENDOFLINE,
    COMMA,
    COMMENT
};*/

char keyWords[][10] = {"int", "text", "is", "loop", "times", "read", "write", "newLine"};
char operators[][1] = {"+", "-", "*", "/"};

int isInKeywords(char *str)
{
    for (int i = 0; i < 8; i++)
    {
        if (strcmp(str, keyWords[i]) == 0)
        {
            printf("keyword");
            return 1;
        }
    }
    return 0;
}

int isInOperators(char *str)
{
    for (int i = 0; i < 4; i++)
    {
        if (strcmp(str, operators[i]) == 0)
        {
            return 1;
        }
    }
    return 0;
}

int identifierControl(char *str)
{
    if (strlen(str) > 10)
    {
        printf("Error: Identifier is too long.\n");
        return 0;
    }
    else if (!isalpha(str[0]))
    {
        printf("Error: Identifier must start with a letter.\n");
        return 0;
    }
    else
    {
        printf("Identifier(%s)\n", str);
        return 0;
    }
}

int integerControl(int num)
{
    if (num < 0)
    {
        printf("Error: Integer is negative.\n");
        integerControl(0); // Recursive call to negative nums.
    }
    else
    {
        if (num > 99999999)
        {
            printf("Error: Integer is too long.\n");
            return 0;
        }
        else if (num < 0)
        {
            printf("Error: Integer is negative.\n");
            return 0;
        }
        else
        {
            printf("IntConts(%d)\n", num);
            return 1;
        }
    }
}

int operatorControl(char *str)
{
    int len = strlen(str);
    if (len)
    {
        printf("string 1 e eşit değil\n");
        return 0;
    }
    else if (isInOperators(str))
    {
        printf("Operator e girdi\n");
        printf("Operator(%c)\n", str);
        return 1;
    }
    else
    {
        printf("Operator değil\n");
        return 0;
    }
    
}

int bracketControl(char *str)
{
    // TODO: Implement bracket control.
}

int stringControl(char *str)
{
    // TODO: Implement string control.
}

int keywordControl(char *str)
{
    // TODO: Implement keyword control.
}

int endOfLineControl(char *str)
{
    // TODO: Implement end of line control.
}

int commaControl(char *str)
{
    // TODO: Implement comma control.
}

int commentControl(char *str)
{
    // TODO: Implement comment control.
}

int main()
{
    char str[] = "+";
    int lenght = strlen(str);
    printf("String uzunluğu: %\n", strlen(str));
    //operatorControl(str);

    return 0;
}