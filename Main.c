#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char keyWords[][10] = {"int", "text", "is", "loop", "times", "read", "write", "newLine"};

enum tokenType {
    IDENTIFIER,
    INTEGER,
    OPERATOR,
    BRACKET,
    STRING,
    KEYWORD,
    ENDOFLINE,
    COMMA,
    COMMENT
};


int identifierControl(const char *str){
    if(strlen(str) > 10){
        printf("Error: Identifier is too long.\n");
    }
    else
    {
        /* code */
    }
    

}

int integerControl(int num){
    if(num > 99999999){
        printf("Error: Integer is too long.\n");
    }
    else if (num < 0)
    {
        printf("Error: Integer is negative.\n");
    }
    else
    {
        printf("IntConts(%d)\n", num);
    }
}

int operatorControl(){
   //TODO: Implement operator control.
}

int bracketControl(){
    //TODO: Implement bracket control.
}

int stringControl(){
    //TODO: Implement string control.
}

int keywordControl(){
    //TODO: Implement keyword control.
}

int endOfLineControl(){
    //TODO: Implement end of line control.
}

int commaControl(){
    //TODO: Implement comma control.
}

int commentControl(){
    //TODO: Implement comment control.
}




int main() {
    integerControl(123);
    
    return 0;
}