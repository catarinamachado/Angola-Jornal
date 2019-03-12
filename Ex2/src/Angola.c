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

void addlink(GString * tag, GString * title ){
    
    GString *a, *b;
    GSList *l,*tmp;

    if( g_hash_table_contains(taghtable,tag) ){
        l = (GSList *)g_hash_table_lookup(taghtable,tag);
        b = g_string_new(title->str);
        l = g_slist_prepend(l,b);
        g_hash_table_steal_extended(taghtable,tag, &a, &tmp);
        g_hash_table_insert(taghtable,a,l);
    }else{
        l = NULL;
        a = g_string_new(tag->str);
        b = g_string_new(title->str);
        l = g_slist_append(l,b);
        g_hash_table_insert(taghtable,a,l);
    }
    
}

void stringTotalFree(GString* s) { 
    g_string_free(s, TRUE);
}

void listTotalFree(GSList * list){
    g_slist_free_full(list, stringTotalFree);
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
        addlink(l->data,a->title);
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
    
    taghtable = g_hash_table_new_full(g_string_hash, g_string_equal, stringTotalFree, listTotalFree);

}

void f(gpointer key, gpointer value, gpointer user_data){
    GString* s = (GString*)key;
    GSList* l = (GSList*)value;
    printf(":| %s :> %d \n",s->str,(int)g_slist_length(l));

}


void trace(){
    
    // print
    
    g_hash_table_foreach(taghtable,f,NULL);
    
    g_hash_table_destroy(taghtable);
    
}