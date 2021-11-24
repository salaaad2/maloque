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
#include <stdio.h>
#include <errno.h>

void *
ft_malloc(uint32_t size)
{
    static uint32_t left = 0;
    static void * mapped = 0;
    uint32_t m;
    void * ret;
    int cfd;
    int off;

    m = 0;
    cfd = 0;
    off = 0;
    /*
    ** which multiple of page size should we use ?
    */
    if (size < PG_TINY / 4) {
        m = PG_TINY;
    } else {
        if (size < PG_SMALL / 4) {
            m = PG_SMALL;
        } else {
            m = PG_LARGE;
        }
    }
    /*
    ** if memory region is not allocated,
    ** ask the kernel for a new one
    */
    if (left == 0) {
        mapped = mmap(NULL, m, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, 0, 0);
        printf("%s\n", strerror(errno));
        ret = mapped;
    } else {
        ret = (mapped + size);
    }

    if (mapped == MAP_FAILED)
        return (NULL);
    /*
    ** increase left
    */
    left += size;
    return (ret);
}
