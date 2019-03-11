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
    Tuple t = (Tuple)g_malloc( sizeof(struct tup) );
    t->n = 1;
    t->value = v;
    return t;
}

void unmkTuple(Tuple t){
    g_free(t);
}

void unmkTuple_wraper(gpointer t){
   unmkTuple((Tuple)t);
}

MultiSet new( MemorySize fsize, FreeFunc ffunc ){
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

    if( g_hash_table_contains(set->htable,element) ){
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
    GHashTableIter iter;
    gpointer key;
    Tuple value;

    g_hash_table_iter_init (&iter, set->htable );
    while (g_hash_table_iter_next (&iter, &key, &value))
    {
        printf(" %s :|> %ld \n",value->value, value->n);
    }
}

long count(MultiSet set, Value element){
    if( g_hash_table_contains(set->htable,element) ){
        Tuple t = g_hash_table_lookup(set->htable,element);
        return t->n;
    }else{
        return 0;
    }
}