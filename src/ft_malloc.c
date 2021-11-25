/*********************************/
/*   FT_MALLOC        (  //      */
/*   malloc            ( )/      */
/*   by salade         )(/       */
/*  ________________  ( /)       */
/* ()__)____________)))))   :^}  */
/*********************************/

#include "ft_malloc.h"

/*
** remove me
*/
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>

static void *
m_alloc(void ** mapped, uint32_t m, uint32_t * left, uint32_t size)
{
    /*
    ** if memory region is not allocated,
    ** ask the kernel for a new one
    */
    void * ret;

    if (*left == 0) {
        *mapped = mmap(NULL, m, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, 0, 0);
        printf("%s\n", strerror(errno));
        ret = *mapped;
    } else {
        ret = (*mapped + (size + 1));
    }
    if (*mapped == MAP_FAILED || ret == MAP_FAILED)
    {
        return (NULL);
    }
    /*
    ** increase left
    */
    *left += (size + 1);
    return (ret);
}

void *
ft_malloc(uint32_t size)
{
    static uint32_t tiny_left = 0;
    static uint32_t small_left = 0;
    static uint32_t large_left = 0;
    static void * tiny_mapped = 0;
    static void * small_mapped = 0;
    static void * large_mapped = 0;
    uint32_t m;
    uint32_t * left;
    void ** mapped;
    int cfd;
    int off;

    m = 0;
    cfd = 0;
    off = 0;
    left = 0;
    /*
    ** which multiple of page size should we use ?
    */
    if ((size + tiny_left) < PG_TINY / 10) {
        m = PG_TINY;
        left = &tiny_left;
        mapped = &tiny_mapped;
        write(1, "tiny \n", 6);
    } else {
        if ((size + small_left) < PG_SMALL / 10) {
            write(1, "small\n", 6);
            m = PG_SMALL;
            left = &small_left;
            mapped = &small_mapped;
        } else {
            write(1, "large\n", 6);
            m = PG_LARGE;
            left = &large_left;
            mapped = &large_mapped;
        }
    }
    return (m_alloc(mapped, m, left, size));
}
