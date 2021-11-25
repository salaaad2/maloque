#ifndef FT_MALLOC_H_
#define FT_MALLOC_H_

#include <sys/types.h>
#include <sys/mman.h>
#include <stdint.h>
#include <stdlib.h>

#ifdef __linux
# define PG_SIZE 4096
#endif

#define PG_TINY PG_SIZE * 100
#define PG_SMALL PG_SIZE * 1000
#define PG_LARGE PG_SIZE * 10000

typedef struct s_mlc {
    uint32_t left;
    uint32_t sz;
    void * mapped;
    struct s_mlc * next;
} t_mlc;

void  ft_free(void * ptr);
void * ft_malloc(uint32_t size);
void * ft_realloc(void * ptr, uint32_t size);

#endif
