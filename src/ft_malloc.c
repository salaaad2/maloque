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
    .left =   NULL,
    .sz =     0,
    .type =   0,
    .mapped = NULL,
    .next =   NULL};

t_mlc * getHead( void )
{
    return (&g_head);
}

static void *
m_alloc(void ** mapped, uint32_t size, uint32_t m)
{
    void * ret;
    t_mlc * ptr = getHead();

    /*
    ** if memory region is not allocated, in selected range
    ** ask the kernel for a new one
    */
    if (ptr->left == 0) {
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
    ptr->left += size;
    return (ret);
}

void *
ft_malloc(uint32_t size)
{
    t_mlc* mlc;
    uint32_t m;
    void * mapped;

    mlc = getHead();
    /*
    ** which multiple of page size should we use ?
    */
    if (size < PG_TINY) {
        m = PG_TINY;
        mlc->left = &mlc->t_left;
    } else {
        if (size < PG_SMALL) {
            m = PG_SMALL;
            mlc->left = &mlc->s_left;
        } else {
            m = PG_LARGE;
            mlc->left = &mlc->s_left;
        }
    }
    if (mlc == NULL) {
        printf("head is now mlc(%p). init\n", mlc);
    } else {
        printf("second call (%p). init\n", mlc);
    }
    return (m_alloc(&mapped, size, m));
}
