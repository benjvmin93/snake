#ifndef MEMORY_H
#define MEMORY_H

#include <stdlib.h>
#include <err.h>
#include <errno.h>

void *xmalloc(size_t size);
void *xcalloc(size_t nmemb, size_t size);

#endif