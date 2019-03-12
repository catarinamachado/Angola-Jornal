#include <Angola.h>
#include <glib.h>
#include <stdio.h>

typedef struct angola {
    GString * id;
    GString * author;
    GList * tags;
    GString * title;
    GString * category;
    GString * text;
} *Angola;

Angola mkAngola(){
    Angola a = (Angola)g_malloc( sizeof( struct angola));

    a->id = g_string_new("");
    a->author = g_string_new("");
    a->title = g_string_new("");
    a->category = g_string_new("");
    a->text = g_string_new("");
    a->tags = NULL;
    return a;
}

void unmkAngola(Angola a){
    GList *l;
    char * tmp;
    char * id = g_string_free(a->id,FALSE);
    char * author = g_string_free(a->author,FALSE);
    char * title = g_string_free(a->title,FALSE);
    char * category = g_string_free(a->category,FALSE);
    char * text = g_string_free(a->text,FALSE);

    printf("<pub id=\"%s\">\n",id);

    if(strstr(title,"---------"))
    {
        printf("<title></title>\n");
    }else{
        printf("<title>%s</title>\n",title);
    }

    printf("<author_date>%s</author_date>\n",author);
    printf("\t<tags>\n\t\t");
    for (l = a->tags; l != NULL; l = l->next)
    {
        tmp = g_string_free(l->data,FALSE);
        printf("<tag>%s</tag> ",tmp);
        g_free(tmp);
    }
    printf("\n\t</tags>\n");
    printf("\t<category>%s</category>\n",category);
    
    if( text[0]=='\n' )
        printf("<text>%s\n</text>\n",text);
    else
        printf("<text>\n%s\n</text>\n",text);

    printf("</pub>\n");

    g_free(id);
    g_free(author);
    g_free(title);
    g_free(category);
    g_free(text);
    g_list_free(a->tags);
    g_free(a);
}

void addId(Angola a, char* str){
    g_string_append(a->id,str);
}

void addAuthor(Angola a, char* str){
    g_string_append(a->author,str);
}

void addTag(Angola a, char* str){
    a->tags = g_list_append(a->tags, g_string_new(str));
}

void addTitle(Angola a, char* str){
    g_string_append(a->title,str);
}

void addCategory(Angola a, char* str){
    g_string_append(a->category,str);
}

void addText(Angola a, char* str){
    g_string_append(a->text,str);
}
