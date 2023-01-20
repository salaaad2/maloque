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

static t_mlc g_head = {
    .t_left = 0,
    .s_left = 0,
    .l_left = 0,
    .left   = NULL,
    .sz     = 0,
    .type   = 0,
    .mapped = NULL,
    .next   = NULL};

t_mlc * getHead( void )
{
    return (&g_head);
}

t_mlc * getTail( void )
{
    t_mlc * ptr = getHead();

    while (ptr->next != NULL)
    {
        ptr = ptr->next;
    }
    return ptr;
}

static void *
m_alloc(t_mlc * ptr, uint32_t size, uint32_t m)
{
    void * ret;

    /*
    ** if memory region is not allocated, in selected range
    ** ask the kernel for a new one
    */
    if (*ptr->left == 0)
    {
        ptr->mapped = mmap(
            NULL,
            m,
            PROT_READ|PROT_WRITE,
            MAP_PRIVATE|MAP_ANONYMOUS,
            0,
            0);
        ret = ptr->mapped;
    }
    else
    {
        t_mlc new_alloc = {0};
        t_mlc * p = getTail();

        new_alloc.mapped = ptr->mapped + (size + 1);
        p->mapped = &new_alloc;

        ret = (new_alloc.mapped);
    }
    if (ptr->mapped == MAP_FAILED)
    {
        return (NULL);
    }

    /*
    ** set ptr type, size
    */
    *ptr->left += size;
    return (ret);
}

void *
ft_malloc(uint32_t size)
{
    t_mlc* head;
    uint32_t m;

    head = getHead();
    /*
    ** which multiple of page size should we use ?
    */
    if (size < PG_TINY)
    {
        m = PG_TINY;
        head->left = &head->t_left;
    }
    else if (size < PG_SMALL)
    {
        m = PG_SMALL;
        head->left = &head->s_left;
    }
    else
    {
        m = PG_LARGE;
        head->left = &head->s_left;
    }

    if (head == NULL)
    {
        printf("Head could not be found\n");
    }
    return (m_alloc(head, size, m));
}
