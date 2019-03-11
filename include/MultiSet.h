#ifndef multiSet_h
#define multiSet_h

#include <glib.h>

#define Value void*
typedef size_t (*MemorySize)(Value);
typedef void (*FreeFunc)(Value);

typedef struct mset *MultiSet;

MultiSet new( MemorySize fsize, FreeFunc ffunc );

void destroy(MultiSet mset);

MultiSet add(MultiSet set, Value element);

long count(MultiSet set, Value element);

void show(MultiSet set);

#endif
