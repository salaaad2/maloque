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
    t_mlc * head;
    t_mlc * ptr;
    void * ret;

    /*
    ** keep pointer to head to remember space left for
    ** each region (tiny, small, large)
     */

    head = s_getstruct(NULL);
    ptr = s_newnode(head);

    /*
    ** if memory region is not allocated, in selected range
    ** ask the kernel for a new one
    */
    if (*head->left == 0) {
        printf("mmap(%u)\n", m);
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
    ** set ptr type, size
    */
    *head->left += size;
    ptr->next = NULL;
    ptr->mapped = *mapped;
    ptr->sz = size;
    ptr->type = m;
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
    if (mlc.next == NULL) {
        printf("before init\n");
        s_getstruct(&mlc);
    }
    return (m_alloc(&mapped, size, m));
}
