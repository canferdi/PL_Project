#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

FILE *fptr;

char keyWords[][10] = {"int", "text", "is", "loop", "times", "read", "write", "newLine"};
char specialLetters[] = "+-*/{}.,";

char *deleteBlanks(char str[]);
void fileReading(char *filePath);
char *substring(char *str, int start, int end);
char *tokenControl(char *string);

char *substring(char *str, int start, int end) {
    int len = end - start + 1;
    char *substr = (char *)malloc((len + 1) * sizeof(char));

    for (int currentPosition = start; currentPosition <= end; currentPosition++) {
        substr[currentPosition - start] = str[currentPosition];
    }

    substr[len] = '\0'; // Yeni stringin sonuna null karakter ekliyoruz.

    return substr;
}

void fileReading(char *filePath) {

    
    fptr = fopen(filePath, "r");

    char myString[100];

    while (fgets(myString, 100, fptr)) {

        int startIndex = 0;
        int endIndex = 0;
        int currentPosition = 0;
        while (currentPosition < strlen(myString)) {
            int value = myString[currentPosition];
            // Integer tokenizer.
            if (isdigit(myString[startIndex])) {
                //printf("integer tokenizer control\n");
                if (isdigit(myString[currentPosition])) {
                    endIndex++;
                    currentPosition++;
                    continue;

                } else if (startIndex != endIndex ) {
                    char *toToken = substring(myString, startIndex, endIndex - 1);
                    sleep(0.1);
                    char *willPrinted = tokenControl(toToken);
                    printf("%s\n", willPrinted);
                    startIndex = endIndex;
                    free(willPrinted);  free(toToken);
                    
                }
            }
            
            // Identifier tokenizer.
             if (isalpha(myString[startIndex]) || myString[startIndex] == '_' || myString[startIndex]=='"') {
                //printf("identifier tokenizer control\n");
               
                 if (strchr(specialLetters, value) == NULL && value != 32 && value!=10 ) {
                    endIndex++;
                    currentPosition++;
                    //printf("\nsayi");
                    continue;
                    
                    
                }                 
                 else if (startIndex != endIndex ) {
                       
                       
                   char *toToken = substring(myString, startIndex, endIndex - 1);
                   sleep(0.1);
                                 
                    char *willPrinted = tokenControl(toToken);
                    sleep(0.1);
                    printf("%s\n", willPrinted);
                    free(toToken);
                    free(willPrinted);
                    startIndex = endIndex;
                  //  printf("\nelseifli");
                    
                    
                }

            }
                  
             if (strchr(specialLetters, value) != NULL && value!=32 && value!=10) {

                char ch = value;
                char str[2]={value,'\0'};
              //  sprintf(str, "%c", ch);           
                char *willPrinted = tokenControl(str);
                printf("%s\n", willPrinted);
                startIndex = endIndex;
            
            }

            currentPosition++;
            startIndex++;
            endIndex++;
        }
    }
}

char *deleteBlanks(char str[]) {
    int len = strlen(str);
    char *newStr = (char *)malloc((len + 1) * sizeof(char)); // Yeni string için yeterli alanı tahsis ediyoruz.
    int j = 0;

    for (int currentPosition = 0; str[currentPosition]; currentPosition++) {
        if (str[currentPosition] != ' ') {
            newStr[j++] = str[currentPosition];
        }
    }

    newStr[j] = '\0'; // Yeni stringin sonuna null karakter ekliyoruz.

    return newStr;
}

int isKeyWord(char word[]) {
    int currentPosition = 0;
    while (strcmp(keyWords[currentPosition], "") != 0) {
        if (strcmp(word, keyWords[currentPosition]) == 0)
            return 1;
        currentPosition++;
    }
    return 0;
}

char *tokenControl(char *string) {
    char firstChar = string[0];
    char lastChar = string[strlen(string) - 1];
    char *ret = (char *)malloc(strlen(string) + 10);
    // keyWord Control
    if (isKeyWord(string)) {
        //printf("keyword control\n");
        sprintf(ret, "KeyWord(%s)", string);
        return ret;
    }
    // Identifier Control
    else if (isalpha(firstChar)) {
        //printf("identifier control token\n");
        int currentPosition = 0;
        while ((isdigit(string[currentPosition]) || string[currentPosition] == '_' || isalpha(string[currentPosition])) && string[currentPosition] != '\0') {
            currentPosition++;
        }
        if (currentPosition == strlen(string) && strlen(string) <= 10) {
            sprintf(ret, "Identifier(%s)", string);
            return ret;
        } else if (strlen(string) > 10 && currentPosition == strlen(string)) {
            printf("Identifier lenght cannot be larger than 10!");
            exit(1);
        } else {
            printf("Unavailable token type name!");
            exit(1);
        }
    }
    // Operator Control
    else if ((firstChar == '+' || firstChar == '-' || firstChar == '*' || firstChar == '/') && strlen(string) == 1) {
        //printf("operator control\n");
        sprintf(ret, "Operator(%c)", firstChar);
        return ret;
    }
    // Integer constant control
    else if (isdigit(firstChar) || firstChar == '-') {
        //printf("integer constant\n");
        int k = 0;
        if (firstChar == '-') {
            while (isdigit(string[k + 1]) && string[k + 1] != '\0') {
                k++;
            }
            if (strlen(string) == k + 1) {
                return "IntConst(0)";
            } else {
                return "Unavailable token type name!";
            }
        }

        int currentPosition = 0;
        while (isdigit(string[currentPosition]) && string[currentPosition] != '\0') {
            currentPosition++;
        }
        if (strlen(string) == currentPosition && strlen(string) <= 8) {
            sprintf(ret, "IntConst(%s)", string);
            return ret;
        } else if (strlen(string) > 8 && currentPosition == strlen(string)) {
            printf("Integer constant  lenght cannot be larger than 8!");
            exit(1);
        }
        // TODO: ADD 0 VALUE CHANGE NEGATİVE VALUES.
        else {
            printf("Unavailable token type name!");
            exit(1);
        }
    }

    else if (firstChar == '{' || firstChar == '}') {
        sprintf(ret, "CurlyBracket(%c)", firstChar);
        return ret;
    }
    // String Const control
    else if (firstChar == '"' && lastChar == '"') {
        int b = strlen(string) - 2;
        char copy[b];
        strncpy(copy, string + 1, b);
        copy[b] = '\0';

        char karakter = '"';
        char *result = strchr(copy, karakter);

        if (strlen(copy) > 256) {
            printf("String constant cannot exceed 256 characters.!");
            exit(1);
        } else if (result != NULL) {
            printf("String constant cannot include '\"' character.!");
            exit(1);
        } else {
            sprintf(ret, "String(\"%s\")", copy);
            return ret;
        }
    }
    // End of Line and Comma Control
    else if (firstChar == '.' || firstChar == ',' && strlen(string) == 1) {
        if (firstChar == '.') {
            return "EndOfLine";
        } else {
            return "Comma";
        }
    }
}

int main() {
    // deneme1
    // deneme2

    /* int ab = '"';
     char *bb = tokenControl(".");
     free(bb);
     char *kk = "arab";
     printf("%s\n", bb);
     char denem[] = "\"araba";
     */
    
    fileReading("aa.txt");
    fclose(fptr);
}