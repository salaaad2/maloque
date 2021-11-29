/*********************************/
/*   FT_MALLOC        (  //      */
/*   malloc()          ( )/      */
/*   by salade         )(/       */
/*  ________________  ( /)       */
/* ()__)____________)))))   :^}  */
/*********************************/

#include "ft_malloc.h"
#include "m_structs.h"

/*
** remove me
*/
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>

static void *
m_alloc(void ** mapped, uint32_t size, uint32_t m)
{
    /*
    ** if memory region is not allocated,
    ** ask the kernel for a new one
    */
    static t_mlc * head = NULL;
    t_mlc * ptr = s_newnode();
    void * ret;

    if (head == NULL)
    { head = s_getstruct(NULL); }

    if (ptr->left == 0) {
        printf("");
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
    ptr->sz = size;
    return (ret);
}

void *
ft_malloc(uint32_t size)
{
    static t_mlc mlc;
    uint32_t m;
    void * mapped;

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
    if (mlc.next == NULL) {
        s_getstruct(&mlc);
    }
    return (m_alloc(&mapped, size, m));
}
