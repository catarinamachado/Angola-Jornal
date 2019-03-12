#include <Angola.h>
#include <glib.h>
#include <stdio.h>

GHashTable * taghtable;

typedef struct angola {
    GString * id;
    GString * author;
    GList * tags;
    GString * title;
    GString * category;
    GString * text;
} *Angola;

typedef struct tuple {
    GString * id;
    GString * title;
} *Tuple;

Tuple mkTuple(GString * id, GString * title){
    Tuple t = (Tuple)malloc(sizeof(struct tuple));
    t->id = g_string_new(id->str);
    t->title = g_string_new(title->str);
    return t;
}

void unmkTuple( Tuple t ){
   g_string_free(t->id, TRUE);
   g_string_free(t->title, TRUE);
   g_free(t);
}

void stringTotalFree( GString * str){
    g_string_free(str, TRUE);
}

void addlink(GString * tag, GString* id,GString * title ){
    
    GString *a, *b;
    GHashTable *l,*tmp;
    Tuple t;

    if( g_hash_table_contains(taghtable,tag) ){
        l = (GHashTable *)g_hash_table_lookup(taghtable,tag);
        t = mkTuple(id,title);
        g_hash_table_insert(l,t->id,t);

        g_hash_table_steal_extended(taghtable,tag, &a, &tmp);
        g_hash_table_insert(taghtable,a,l);
    }else{
        l = g_hash_table_new_full(g_string_hash,g_string_equal,NULL,unmkTuple);
        a = g_string_new(tag->str);
        t = mkTuple(id,title);
        g_hash_table_insert(l,t->id,t);
        g_hash_table_insert(taghtable,a,l);
    }
    
}

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
    char * id = a->id->str;
    char * author = a->author->str;
    char * title = a->title->str;
    char * category = a->category->str;
    char * text = a->text->str; 

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
        addlink(l->data,a->id,a->title);
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

    g_string_free(a->id,TRUE);
    g_string_free(a->author,TRUE);
    g_string_free(a->title,TRUE);
    g_string_free(a->category,TRUE);
    g_string_free(a->text,TRUE);
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

void tag(){
    
    taghtable = g_hash_table_new_full(g_string_hash, g_string_equal, stringTotalFree, g_hash_table_destroy );

}

void f(gpointer key, gpointer value, gpointer user_data){
    GString* s = (GString*)key;
    GList* l = g_hash_table_get_values((GHashTable*)value);
    GList* cur;
    Tuple tmp;
    char buffer[2000];
    char *ptr;

    strcpy(buffer,s->str);
    for(ptr = buffer;*ptr != '\0'; ptr++ )
        if( *ptr == ' ' )
            *ptr = '-';

    printf("<pub id=\"%s\">\n",buffer);
    printf("\t<h1>%d</h1>\n",(int)g_list_length(l));
    for(cur = l; cur; cur = cur->next){
        tmp = (Tuple)cur->data;

        printf("\t\t<a href=\"%s.html\">%s</a>\n",tmp->id->str,tmp->title->str);
    }
    printf("</pub>\n");
}

void fm(gpointer key, gpointer value, gpointer user_data){
    GString* s = (GString*)key;
    char buffer[2000];
    char *ptr;

    strcpy(buffer,s->str);
    for(ptr = buffer;*ptr != '\0'; ptr++ )
        if( *ptr == ' ' )
            *ptr = '-';

    printf("\t\t<a href=\"%s.html\">%s</a>\n",buffer,buffer);
}


void trace(){
    
    printf("<pub id=\"tags\">\n");
    g_hash_table_foreach(taghtable,fm,NULL);
    printf("</pub>\n");

    g_hash_table_foreach(taghtable,f,NULL);
    
    g_hash_table_destroy(taghtable);
    
}