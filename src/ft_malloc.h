#ifndef FT_MALLOC_H_
#define FT_MALLOC_H_

#include <sys/types.h>
#include <sys/mman.h>
#include <stdint.h>

#ifdef __linux
# define PG_SIZE 4096
#endif

void  ft_free(void * ptr);
void * ft_malloc(uint32_t size);
void * ft_realloc(void * ptr, uint32_t size);

#endif
