
%{
#include <stdio.h>
#include <glib.h>
#include <MultiSet.h>

GString * tbuffer;
MultiSet mset;
char* tmp;
%}

%%
tag:\{[^\}]+/\}              {add(mset,&yytext[5]);}

<*>.|\n         {}
%%

int yywrap(){
    return 1;
}

size_t stringsize( Value str){
    return strlen(str) + 1;
}

int main(){
    mset = new(stringsize, g_free);
    yylex();
    show(mset);
    destroy(mset);
    return 0;
}
