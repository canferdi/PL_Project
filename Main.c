#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char keyWords[][10] = {"int", "text", "is", "loop", "times", "read", "write", "newLine"};
char operators[][1] = {"+", "-", "*", "/"};
char specialChars[] = {'+', '-', '*', '/', '.', '\n', ',', '{', '}'};

FILE *createFile(char *filePath);

int strToInt(char *intStr)
{
    int number = atoi(intStr);
    return number;
}

int isSpecial(char indexCharacter)
{
    int index = 0;
    while (specialChars[index] != '\0')
    {
        if (indexCharacter == specialChars[index])
            return 1;
        index++;
    }
    return 0;
}

void reset(char *str)
{
    int uzunluk = strlen(str);
    for (int i = 0; i < uzunluk; i++)
    {
        str[i] = '\0';
    }
}

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

int identifierControl(char *str, FILE *ptr)
{
    if (strlen(str) > 10)
    {
        fprintf(ptr, "Error: Identifier is too long.\n");
        return 0;
    }
    else if (!isalpha(str[0]))
    {
        fprintf(ptr, "Error: Identifier must start with a letter.\n");
        return 0;
    }
    else
    {
        fprintf(ptr, "Identifier(%s)\n", str);
        return 0;
    }
}

int integerControl(int num, FILE *ptr)
{
    if (num < 0)
    {
        fprintf(ptr, "Error: Integer is negative.\n");
        integerControl(0, ptr); // Recursive call to negative nums.
    }
    else
    {
        if (num > 99999999)
        {
            fprintf(ptr, "Error: Integer is too long.\n");
            return 0;
        }
        else if (num < 0)
        {
            fprintf(ptr, "Error: Integer is negative.\n");
            return 0;
        }
        else
        {
            fprintf(ptr, "IntConts(%d)\n", num);
            return 1;
        }
    }
}

int operatorControl(char *str, FILE *ptr)
{
    if (strlen(str) != 1)
    {
        return 0;
    }
    else if (isInOperators(str[0]))
    {
        fprintf(ptr, "Operator(%s)\n", str);
        return 1;
    }
    else
    {
        return 0;
    }
}

int bracketControl(char *str, FILE *ptr)
{
    if (str[0] == '{')
    {
        fprintf(ptr, "LeftCurlyBracket\n");
        return 1;
    }
    else if (str[0] == '}')
    {
        fprintf(ptr, "RightCurlyBracket\n");
        return 1;
    }
    else
    {
        return 0;
    }
}
int stringControl(char *str, FILE *ptr)
{
    if (strlen(str) > 256)
    {
        fprintf(ptr, "String constant exceeds 256 characters!");
        return 0;
    }
    else
    {
        fprintf(ptr, "String(\"%s\")\n", str);
        return 1;
    }
}

int keywordControl(char *str, FILE *ptr)
{
    if (isInKeywords(str))
    {
        fprintf(ptr, "Keyword(%s)\n", str);
        return 1;
    }
    else
    {
        return 0;
    }
}

int endOfLineControl(char *str, FILE *ptr)
{

    if (str[0] == '.')
    {
        fprintf(ptr, "EndOfLine\n");
        return 1;
    }
    else
    {
        return 0;
    }
}

int commaControl(char str[100], FILE *ptr)
{
    if (str[0] == ',')
    {
        fprintf(ptr, "Comma\n");
        return 1;
    }
    else
    {
        return 0;
    }
}

void fileReading(char *filePath)
{
    FILE *fptr;
    fptr = fopen(filePath, "r");
    FILE *newPtr;
    newPtr = createFile(filePath);

    char lineString[100];
    char tokenString[257] = {'\0'}; // for tokenStrings to identify which token it is.
    int commentControl = 0;
    int strconControl = 0;
    int tokenIndex = 0;
    // Read the line content and print it
    while (fgets(lineString, 100, fptr))
    { // Beginning of everyline of the file.
        int index = 0;
        // indexes of the string which will be parameterized.
        int startIndex = 0;
        while (lineString[index] != '\0')
        { // Beginning of everyindex of the line.

            char charOfIndex = lineString[index];
            char charOfStart = lineString[startIndex];

            char commentStrings[] = {charOfIndex, lineString[index + 1], '\0'};
            int commentCondition = strcmp("/*", commentStrings) == 0 && tokenString[0] == '\0';
            // Comment finding
            if (commentCondition && !commentControl)
            { // If they are the same:

                index = index + 2;
                startIndex = index;
                commentControl = 1;

                continue;
            }
            else if (commentControl && tokenString[0] == '\0')
            { // If commentControl is 1, it means searching for "*/".
                if (strcmp("*/", commentStrings) == 0)
                {
                    index = index + 2;
                    startIndex = index;
                    commentControl = 0;
                }
                else
                {
                    index++;
                }
                continue;
            }
            // String tokenizer.
            if (charOfIndex == '"' && strconControl == 0 && tokenString[0] == '\0')
            { // If strconControl is 1, it means searching for "*/".
                index++;
                startIndex = index;
                strconControl = 1;
                continue;
            }
            else if (strconControl == 1 && charOfIndex == '"')
            {
                stringControl(tokenString, newPtr);
                strconControl = 0;
                index++;
                startIndex++;
                reset(tokenString);
                tokenIndex = 0;
                continue;
            }
            else if (strconControl)
            {
                tokenString[tokenIndex++] = charOfIndex;
                tokenString[tokenIndex] = '\0';
                index++;
                startIndex++;
                continue;
            }

            // Integer tokenizer.
            // Finds integer and tokenizes it.
            int firstCond = isdigit(charOfStart);
            int secondCond = (charOfStart == '-' && isdigit(lineString[startIndex + 1]));
            int condition = isdigit(charOfIndex) || (charOfIndex == '-' && index == startIndex);

            if (firstCond || secondCond)
            {
                if (condition)
                {
                    tokenString[tokenIndex++] = lineString[index++];
                    continue;
                }
                // If enters else block, it means end of the integer token and it is time to tokenize the value.
                else
                {
                    startIndex = index;
                    tokenString[tokenIndex] = '\0';

                    int returnedInt = strToInt(tokenString);
                    integerControl(returnedInt, newPtr);
                    reset(tokenString);
                    tokenIndex = 0;

                    continue;
                }
                // nonInteger tokenizer.
                // Finds nonIntegers and tokenizes it.
            }
            else
            {
                int condition = charOfIndex != ' ' && charOfIndex != '\n';
                int condition2 = !isSpecial(charOfIndex) && charOfIndex != '"';

                if (condition && condition2)
                {
                    tokenString[tokenIndex++] = lineString[index++];
                    continue;
                }
                // If enters else block, it means end of the nonInteger token and it is time to tokenize the value.
                else
                {
                    startIndex = index;
                    tokenString[tokenIndex] = '\0';

                    if (keywordControl(tokenString, newPtr))
                    {
                    }
                    else if (isalpha(charOfStart))
                    {
                        identifierControl(tokenString, newPtr);
                    }
                    if (charOfIndex == '/' && lineString[index + 1] == '*')
                    {
                        if (commentControl)
                        {
                            continue;
                        }
                        else
                        {
                            reset(tokenString);
                            tokenIndex = 0;

                            continue;
                        }
                    }
                    if (isSpecial(charOfIndex))
                    {
                        tokenString[0] = charOfIndex;
                        tokenString[1] = '\0';
                    }

                    if (isInOperators(charOfIndex))
                    {
                        operatorControl(tokenString, newPtr);
                    }

                    if (charOfIndex == '{' || charOfIndex == '}')
                    {
                        bracketControl(tokenString, newPtr);
                    }
                    if (charOfIndex == '.')
                    {
                        endOfLineControl(tokenString, newPtr);
                    }
                    if (charOfIndex = ',')
                    {
                        commaControl(tokenString, newPtr);
                    }

                    reset(tokenString);
                    tokenIndex = 0;

                    if (lineString[index] == '"')
                        continue;
                }
            }

            startIndex++;
            index++;
            // Every end of the index, we check the next index.
        }
    }
    if (commentControl)
    {
        fprintf(newPtr, "Error! Comment part is not completed!");
    }
    if (strconControl)
    {
        fprintf(newPtr, "Error! String constant part is not completed!");
    }

    fclose(fptr);
    fclose(newPtr);
}

FILE *createFile(char *filePath)
{
    // Creates a file with correct extension.
    // Takes the file name and combine it with file extension ".lex".
    int len = strlen(filePath);
    char newPath[len + 1];
    int i = 0;
    if (!strstr(filePath, ".sta"))
    {
        printf("Only acceptable for .sta file extension type!");
        return NULL;
    }
    while (filePath[i] != '.')
    {
        newPath[i] = filePath[i];
        i++;
    }
    newPath[i] = '\0';
    char sendPath[len + 1];
    sprintf(sendPath, "%s.lex", newPath);
    FILE *ptr;
    ptr = fopen(sendPath, "w");

    return ptr;
}

int main()
{

    fileReading("aa.sta");

    return 0;
}