#ifndef AALTO_ARRAYTOOL_H
#define AALTO_ARRAYTOOL_H

#define CHECK(cond, msg)          if(!(cond)) printf("%s", msg)
#define MAKE_ARRAY(type, n)       malloc(sizeof(type) * n)
#define ARRAY_IDX(type, array, i) *((type *) array + i)

#endif
