
%{
#include <stdio.h>
#include <glib.h>
#include <Angola.h>

GString * tbuffer;
Angola a;
char *tmp;
%}
dig [0-9]
%x TAG IDT CATEGORY TITLE UDATE TEXT

%%

<*>\n\n\n           {}
<*>\n.\n            {}
\<pub\>             {a = mkAngola();}
\<\/pub\>           {printHTML(a); unmkAngola(a);}

tag:\{              {tbuffer = g_string_new("");BEGIN TAG;}
<TAG>\}             {tmp = g_string_free(tbuffer,FALSE); addTag(a,tmp); g_free(tmp); BEGIN INITIAL;}
<TAG>\/             {g_string_append_c(tbuffer,'-');}
<TAG>.              {g_string_append_c(tbuffer,yytext[0]);}

\#ID                {tbuffer = g_string_new("post-");BEGIN IDT;}
<IDT>{dig}+         {g_string_append(tbuffer,yytext);}
<IDT>\}\n           {tmp = g_string_free(tbuffer,FALSE); addId(a,tmp); g_free(tmp); BEGIN CATEGORY;tbuffer = g_string_new("");}

<CATEGORY>\n\n      {tmp = g_string_free(tbuffer,FALSE); addCategory(a,tmp); g_free(tmp); BEGIN TITLE;tbuffer = g_string_new("");}
<CATEGORY>.         {g_string_append_c(tbuffer,yytext[0]);}

<TITLE>.            {g_string_append_c(tbuffer,yytext[0]);}
<TITLE>\n           {tmp = g_string_free(tbuffer,FALSE); addTitle(a,tmp); g_free(tmp); BEGIN INITIAL;}

\#DATE\:            {BEGIN UDATE;tbuffer = g_string_new("");}
<UDATE>" "\[.*\]" " {}
<UDATE>.            {g_string_append_c(tbuffer,yytext[0]);}
<UDATE>\n           {tmp = g_string_free(tbuffer,FALSE); addAuthor(a,tmp); g_free(tmp); BEGIN TEXT; tbuffer = g_string_new("");}

<TEXT>.             {g_string_append_c(tbuffer,yytext[0]);}
<TEXT>\n            {}
<TEXT>\n\n          {tmp = g_string_free(tbuffer,FALSE); addLine(a,tmp); g_free(tmp); BEGIN TEXT; tbuffer = g_string_new("");}
<TEXT>\[.*\]\n      {}
<TEXT>\<\/pub\>     {tmp = g_string_free(tbuffer,FALSE); addLine(a,tmp); g_free(tmp); BEGIN INITIAL; printHTML(a); unmkAngola(a);}
<TEXT>Etiquetas\:   {tmp = g_string_free(tbuffer,FALSE); addLine(a,tmp); g_free(tmp); BEGIN INITIAL;}

<*>.|\n             {}

%%

int yywrap(){
    return 1;
}

int main(){
    START_TAGGING;
    yylex();
    STOP_TAGGING;
    return 0;
}
