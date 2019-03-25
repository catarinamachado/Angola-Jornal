%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

char buffer[500];
char dir[500];
char dirout[500];
FILE* fdes;


%}

dig [0-9]

%x COPY NAME

%%
"<pub id=\""                            {buffer[0]=dir[0]='\0';
                                         BEGIN NAME;}                
<NAME>\">                               {strcat(buffer,".html");
                                         sprintf(dir,"%s%s",dirout,buffer);
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

int main(int argc, char *argv[]){
    struct stat st = {0};
    if(argc > 1){
        strcpy(dirout,argv[1]);
        strcat(dirout,"/");
        if (stat(dirout, &st) == -1) {
            mkdir(dirout, 0777);
    }
    }else{
        strcpy(dirout,"");
    }
    yylex();
    return 0;
}




