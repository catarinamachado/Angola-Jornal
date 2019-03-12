%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char buffer[2000];
char dir[2000];
char *t;
FILE* fdes;
int id;

%}

dig [0-9]

%x COPY NAME

%%

"<pub id=\""                            {BEGIN NAME;buffer[0] ='\0';}                
<NAME>\">                               {strcat(buffer,".html"); sprintf(dir,"out/%s",buffer); fdes = fopen(dir,"w"); fprintf(fdes,"<html>\n"); BEGIN COPY;}
<NAME>" "                               {strcat(buffer,"-");}
<NAME>.                                 {strcat(buffer,yytext);}
<COPY>"</pub>"                          {fprintf(fdes,"</html>");fclose(fdes); BEGIN INITIAL;}
<COPY>.|\n                              {fprintf(fdes,"%s",yytext);}
<*>.|\n                                 {}

%%

int yywrap(){
    return 1;
}

int main(){
    buffer[0]=dir[0]='\0';
    yylex();
    return 0;
}