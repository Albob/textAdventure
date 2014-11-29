/*
 * Insert standard lolilol header here
 */

#include "array.h"


void array_iterator_init(array_iterator_t * it, void ** head)
{
    it->head = head;
    it->index = 0;
}

void * array_next(array_iterator_t * it)
{
    void * value = it->head[it->index];
    if (value != NULL) {
        it->index++;
    }
    return value;
}

