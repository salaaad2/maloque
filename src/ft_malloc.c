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

t_mlc * g_head;

t_mlc * gethead( void )
{
    return (g_head);
}

void *
m_alloc(void ** mapped, uint32_t size, uint32_t m)
{
    t_mlc new = {0, 0, 0, NULL, 0, 0, NULL, NULL};
    void * ret;

    /*
    ** if memory region is not allocated, in selected range
    ** ask the kernel for a new one
    */
    if (*g_head->left == 0) {
        printf("mmap(%u)\n", m);
        *mapped = mmap(NULL, m, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, 0, 0);
        ret = *mapped;
    } else {
        printf("mapped memory is still present on page\n");
        ret = (*mapped + (size + 1));
    }
    if (*mapped == MAP_FAILED)
    {
        printf("%s\n", strerror(errno));
        return (NULL);
    }
    /*
    ** set ptr type, size
    */
    *g_head->left += size;
    new.mapped = ret;
    new.sz = size;
    new.type = m;
    u_lstadd_back(&g_head, &new);
    return (ret);
}

void *
ft_malloc(uint32_t size)
{
    static t_mlc mlc = {0, 0, 0, NULL, 0, 0, NULL, NULL};
    uint32_t m;
    void * mapped;

    /*
    ** which multiple of page size should we use ?
    */
    if (size < PG_TINY) {
        m = PG_TINY;
        mlc.left = &mlc.t_left;
    } else {
        if (size < PG_SMALL) {
            m = PG_SMALL;
            mlc.left = &mlc.s_left;
        } else {
            m = PG_LARGE;
            mlc.left = &mlc.s_left;
        }
    }
    if (g_head == NULL) {
        printf("head is now mlc(%p). init\n", g_head);
        g_head = &mlc;
    } else {
        printf("second call (%p). init\n", g_head);
    }
    return (m_alloc(&mapped, size, m));
}
