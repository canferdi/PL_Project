#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char keyWords[][10] = {"int", "text", "is", "loop", "times", "read", "write", "newLine"};
char operators[][1] = {"+", "-", "*", "/"};

// Helper method for keyword control.
int isInKeywords(char *str)
{
    for (int i = 0; i < 8; i++)
    {
        if (strcmp(str, keyWords[i]) == 0)
        {
            return 1; // Keyword found.
        }
    }
    return 0; // Keyword not found.
}

// Helper method for operator control.
int isInOperators(char str)
{
    for (int i = 0; i < 4; i++)
    {
        if (str == operators[0][i])
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
    if (!strlen(str) == 1)
    {
        return 0;
    }
    else if (isInOperators(str[0]))
    {
        printf("Operator(%s)\n", str);
        return 1;
    }
    else
    {
        return 0;
    }
}

int bracketControl(char *str)
{
    if (str[0] == '{')
    {
        printf("LeftCurlyBracket\n");
        return 1;
    }
    else if (str[0] == '}')
    {
        printf("RightCurlyBracket\n");
        return 1;
    }
    else
    {
        return 0;
    }
}

int stringControl(char *str)
{
    char *start = strstr(str, "\"");     // Find the start of the string.
    char *end = strstr(start + 1, "\""); // Find the end of the string.
    if (start != NULL && end != NULL)
    {
        printf("String(");
        for (char *ptr = start + 1; ptr < end; ptr++)
        {
            printf("%c", *ptr);
        }
        printf(")\n");
        return 1;
    }
    else
    {
        return 0;
    }
}

int keywordControl(char *str)
{
    if (isInKeywords(str))
    {
        printf("Keyword(%s)\n", str);
        return 1;
    }
    else
    {
        return 0;
    }
}

int endOfLineControl(char *str)
{
    if (str[0] == '.')
    {
        printf("EndOfLine\n");
        return 1;
    }
    else
    {
        return 0;
    }
}

int commaControl(char *str)
{
    if (str == ",")
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int commentControl(char *str)
{
    char *start = strstr(str, "/*"); // Find the start of the comment.
    char *end = strstr(str, "*/");   // Find the end of the comment.
    if (start != NULL && end != NULL)
    {
        printf("Comment(");
        for (char *ptr = start + 2; ptr < end; ptr++)
        {
            printf("%c", *ptr);
        }
        printf(")\n");
        return 1;
    }
    else
    {
        return 0;
    }
}

int main()
{

    return 0;
}