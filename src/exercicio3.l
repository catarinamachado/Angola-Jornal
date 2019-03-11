
%{
#include <stdio.h>
#include <MultiSet.h>

char tbuffer[4000];
int p = 0;
MultiSet mset;
%}

%x TAG

%%
tag:\{          {BEGIN TAG;}
<TAG>\}         {tbuffer[p] = '\0'; add(mset,tbuffer); p=0; BEGIN INITIAL;}
<TAG>.          {tbuffer[p] = yytext[0]; p++;}
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
    printf(">>filtragem vai ser iniciada\n");
    yylex();
    printf(">>filtragem terminou\n");
    show(mset);
    destroy(mset);
    return 0;
}
