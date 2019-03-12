%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char buffer[500];
char dir[500];
FILE* fdes;


%}

dig [0-9]

%x COPY NAME

%%
"<pub id=\""                            {buffer[0]=dir[0]='\0';
                                         BEGIN NAME;}                
<NAME>\">                               {strcat(buffer,".html");
                                         sprintf(dir,"out/%s",buffer);
                                         fdes = fopen(dir,"w"); 
                                         fprintf(fdes,"<html>\n"); 
                                         BEGIN COPY;}
<NAME>.                                 {strcat(buffer,yytext);}
<COPY>"</pub>"                          {fprintf(fdes,"</html>");
                                         fclose(fdes);
                                         BEGIN INITIAL;}
<COPY>.|\n                              {putc(yytext[0] ,fdes);}
<*>.|\n                                 {}
%%

int yywrap(){
    return 1;
}

int main(){
    yylex();
    return 0;
}