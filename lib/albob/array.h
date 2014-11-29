/*
 * Insert big standard headers here
 */

#include <stdlib.h>

/* A iterator on arrays of pointer (null terminated). */
typedef struct array_iterator_t {
    void ** head; 
    int index;
} array_iterator_t;

void array_iterator_init(array_iterator_t * it, void ** head);
void * array_next(array_iterator_t * it);

