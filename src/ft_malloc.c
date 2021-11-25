/*********************************/
/*   FT_MALLOC        (  //      */
/*   malloc()          ( )/      */
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
m_alloc(void ** mapped, uint32_t size, uint32_t m, t_mlc * mlc)
{
    /*
    ** if memory region is not allocated,
    ** ask the kernel for a new one
    */
    void * ret;

    if (mlc->left == 0) {
        *mapped = mmap(NULL, m, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, 0, 0);
        ret = *mapped;
    } else {
        ret = (*mapped + (size + 1));
    }
    if (*mapped == MAP_FAILED || ret == MAP_FAILED)
    {
        printf("%s\n", strerror(errno));
        return (NULL);
    }
    /*
    ** increase left
    */
    mlc->left += (size + 1);
    mlc->size = size;
    return (ret);
}

void *
ft_malloc(uint32_t size)
{
    static t_mlc mlc;
    uint32_t m;
    uint32_t * left;
    void ** mapped;

    /*
    ** which multiple of page size should we use ?
    */
    if (size < PG_TINY) {
        m = PG_TINY;
    } else {
        if (size < PG_SMALL) {
            m = PG_SMALL;
        } else {
            m = PG_LARGE;
        }
    }
    return (m_alloc(mapped, size, m, &mlc));
}
