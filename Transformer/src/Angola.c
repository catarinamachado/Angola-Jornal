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
    GList * lines;
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

void unmkTuple(Tuple t){
   g_string_free(t->id, TRUE);
   g_string_free(t->title, TRUE);
   g_free(t);
}

void stringTotalFree(GString * str){
    g_string_free(str, TRUE);
}

void addlink(GString * tag, GString* id, GString * title ){
    GString *a, *b;
    GHashTable *l,*tmp;
    Tuple t;

    if(g_hash_table_contains(taghtable,tag)){
        l = (GHashTable *)g_hash_table_lookup(taghtable,tag);
        t = mkTuple(id,title);
        g_hash_table_insert(l,t->id,t);

        g_hash_table_steal_extended(taghtable,tag, &a, &tmp);
        g_hash_table_insert(taghtable,a,l);
    } else {
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
    a->tags = NULL;
    a->lines = NULL;
    return a;
}

void unmkAngola(Angola a){
    g_string_free(a->id,TRUE);
    g_string_free(a->author,TRUE);
    g_string_free(a->title,TRUE);
    g_string_free(a->category,TRUE);
    g_list_free(a->tags);
    g_list_free(a->lines);
    g_free(a);
}

void printHTML(Angola a){
    GList *l;
    char *tmp;
    char tmpOriginal[2000];
    char *ptr;
    char *id = a->id->str;
    char *author = a->author->str;
    char *title = a->title->str;
    char *category = a->category->str;

    printf("<pub id=\"%s\">\n", id);

    printf("<head>\n");

    if (strstr(title, "---------"))
    {
        printf("\t<title></title>\n");
    }
    else
    {
        printf("\t<title>%s</title>\n", title);
    }

    printf("</head>\n");
    printf("<body>\n");

    printf("\t<h1><p align='center'>\n\t\t<font color='#2874A6'>%s</font>\n\t</p></h1>\n", title);

    printf("\t<div style='padding: 20px'>\n");
    printf("\t<author_date><h3>\n\t\t<font color='#85C1E9'>%s</font>\n\t</h3></author_date>\n", author);

    printf("\t<p><tags><b>Tags:</b> \n");
    for (l = a->tags; l != NULL; l = l->next){
        addlink(l->data, a->id, a->title);

        tmp = g_string_free(l->data, FALSE);
        strcpy(tmpOriginal, tmp);

        for (ptr = tmp; *ptr != '\0'; ptr++){
            if (*ptr == ' ')
                *ptr = '-';
        }

        printf("\t\t<a href=\"%s.html\"><tag>#%s</tag></a>\n", tmp, tmpOriginal);

        g_free(tmp);
    }
    printf("\t</tags></p>\n");

    printf("\t<p><category><b>Categoria:</b> %s</category></p>\n", category);

    printf("\t</div>\n");

    printf("\t<text>\n");

    printf("\t<div style='float: left; width: 50%%;'>\n");
    printf("\t<div style='padding: 20px'>\n");
    guint length = g_list_length(a->lines);
    int i = 0;

    for (l = a->lines; l != NULL; l = l->next)
    {
        tmp = g_string_free(l->data, FALSE);
        printf("\t\t<p align='justify'>%s</p>\n", tmp);

        if (i == length / 2){
            printf("\t<br><br>\n\t<a href=\"tags.html\"><tag>Regressar para Tags.html</tag></a>\n");
            printf("\t</div>");
            printf("</div>\n");

            printf("\t<div style='float: left; width: 49%%;'>\n");
            printf("\t<div style='padding: 20px'>\n");
        }

        g_free(tmp);
        i++;
    }

    printf("\t</div>");
    printf("</div>\n");

    printf("\t</text>\n");

    printf("</body>\n");

    printf("</pub>\n");
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

void addLine(Angola a, char* str){
    a->lines = g_list_append(a->lines, g_string_new(str));
}

void tag(){
    taghtable = g_hash_table_new_full(g_string_hash, g_string_equal, stringTotalFree, g_hash_table_destroy );
}

void title_index_function(gpointer key, gpointer value, gpointer user_data){
    GString* s = (GString*)key;
    GList* l = g_hash_table_get_values((GHashTable*)value);
    GList* cur;
    Tuple tmp;
    char buffer[2000];
    char bufferOriginal[2000];
    char *ptr;

    strcpy(bufferOriginal,s->str);
    strcpy(buffer,s->str);
    for(ptr = buffer;*ptr != '\0'; ptr++ )
        if( *ptr == ' ' )
            *ptr = '-';

    printf("<pub id=\"%s\">\n", buffer);

    printf("<head>\n");
    printf("\t<title>%s</title>\n", bufferOriginal);
    printf("</head>\n");

    printf("<body>\n");

    printf("\t<h1><p align='center'><font color='#2874A6'>%s</font></p></h1>\n", bufferOriginal);

    printf("\t<h2>Número de ocorrências: <font color='#2874A6'>%d</font></h2>\n", (int)g_list_length(l));

    printf("<ul>\n");

    for(cur = l; cur; cur = cur->next){
        tmp = (Tuple)cur->data;

        printf("\t<li><a href=\"%s.html\">%s</a></li>\n",tmp->id->str,tmp->title->str);
    }

    printf("</ul>\n");

    printf("\t<br><br><br><br><br><br><br><a href=\"tags.html\"><tag>Regressar para Tags.html</tag></a>");

    printf("</body>\n");

    printf("</pub>\n");
}

void printTagTitlesHTML(){
    g_hash_table_foreach(taghtable, title_index_function, NULL);
}

void printTagsHTML(){
    printf("<pub id=\"tags\">\n");

    printf("<head>\n");
    printf("\t<title>Tags</title>\n");
    printf("</head>\n");

    printf("<body>\n");
    printf("\t<h1><p align='center'><font color='#2874A6'>Tags</font></p></h1>\n");

    printf("\t<div style='float: left; width: 33%%;'>\n");
    printf("\t<ul>\n");

    guint length = g_hash_table_size(taghtable);
    int i = 0;

    GHashTableIter iter;
    gpointer key, value;

    g_hash_table_iter_init(&iter, taghtable);
    while (g_hash_table_iter_next(&iter, &key, &value)){
        if (i == length / 3){
            printf("\t</ul>\n");
            printf("\t</div>\n");
            printf("\t<div style='float: left; width: 33%%;'>\n");
            printf("\t<ul>\n");
        }
        if (i == ((2 * length) / 3)){
            printf("\t</ul>\n");
            printf("\t</div>\n");
            printf("\t<div style='float: right; width: 33%%;'>\n");
            printf("\t<ul>\n");
        }

        GString *s = (GString *)key;
        char buffer[2000];
        char *ptr;

        strcpy(buffer, s->str);
        for (ptr = buffer; *ptr != '\0'; ptr++){
            if (*ptr == ' ')
                *ptr = '-';
        }

        GList *l = g_hash_table_get_values((GHashTable *)value);

        printf("\t\t<li><a href=\"%s.html\">%s</a><font color='#2874A6'> (%d)</font></li>\n", buffer, s->str, (int)g_list_length(l));

        i++;
    }

    printf("</body>\n");
    printf("</pub>\n");
}


void trace(){
    printTagsHTML();

    printTagTitlesHTML();

    g_hash_table_destroy(taghtable);
}
