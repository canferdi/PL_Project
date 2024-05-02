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

int identifierControl(){
    //TODO: Implement identifier control.
}

int integerControl(){
    //TODO: Implement integer control.
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
    
    return 0;
}