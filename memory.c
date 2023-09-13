#include "memory.h"

void *xmalloc(size_t size)
{
    void *ptr = malloc(size);
    if (ptr == NULL)
    {
        err(errno, "Fail allocate memory");
    }
    return ptr;
}

void *xcalloc(size_t nmemb, size_t size)
{
    void *ptr = calloc(nmemb, size);
    if (ptr == NULL)
    {
        err(errno, "Fail allocate memory");
    }
    return ptr;
}