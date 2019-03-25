
%{
#include <stdio.h>
#include <glib.h>
#include <MultiSet.h>

GString * tbuffer;
MultiSet mset;
char* tmp;
%}

%x TAG

%%
tag:\{          {tbuffer = g_string_new("");BEGIN TAG;}
<TAG>\}         {tmp = g_string_free(tbuffer,FALSE); add(mset,tmp); g_free(tmp); BEGIN INITIAL;}
<TAG>.          {g_string_append_c(tbuffer,yytext[0]);}
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
