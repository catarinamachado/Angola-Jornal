#include "MultiSet.h"
#include <glib.h>
#include <stdio.h>

typedef struct mset{
    GHashTable * htable;
    MemorySize fsize;
}*MultiSet;

typedef struct tup{
    Value value;
    long n;
}*Tuple;

Tuple mkTuple(Value v){
    Tuple t = (Tuple)g_malloc(sizeof(struct tup));
    t->n = 1;
    t->value = v;
    return t;
}

int tuplecmp(const void* a1 ,const void* a2){
    Tuple b1 = (Tuple)a1;
    Tuple b2 = (Tuple)a2;

    return b1->n >= b2->n;
}

void unmkTuple(Tuple t){
    g_free(t);
}

void unmkTuple_wraper(gpointer t){
   unmkTuple((Tuple)t);
}

MultiSet new(MemorySize fsize, FreeFunc ffunc){
    MultiSet t = (MultiSet)g_malloc( sizeof(struct mset) );
    t->htable = g_hash_table_new_full(g_str_hash, g_str_equal, ffunc, unmkTuple_wraper);
    t->fsize = fsize;
    return t;
}

void destroy(MultiSet mset){
    g_hash_table_destroy(mset->htable);
    g_free(mset);
}

MultiSet add(MultiSet set,Value element){

    if(g_hash_table_contains(set->htable,element)){
        Tuple t = (Tuple)g_hash_table_lookup(set->htable,element);
        t->n++;
    }else{
        Value elementcpy = g_memdup(element,set->fsize(element));
        Tuple t = mkTuple(elementcpy);
        g_hash_table_insert(set->htable, elementcpy, t);
    }

    return set;
}

void show(MultiSet set){
    Tuple t;
    GList *cur;
    GList *l = g_hash_table_get_values(set->htable);
    l = g_list_sort(l,tuplecmp);

    for(cur = l; cur ; cur = cur->next){
        t = (Tuple)cur->data;
        printf(" %s - %ld \n",t->value, t->n);
    }
}

long count(MultiSet set, Value element){
    if(g_hash_table_contains(set->htable,element)){
        Tuple t = g_hash_table_lookup(set->htable,element);
        return t->n;
    }else{
        return 0;
    }
}
