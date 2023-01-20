/*********************************/
/*   FT_MALLOC        (  //      */
/*   free()            ( )/      */
/*   by salade         )(/       */
/*  ________________  ( /)       */
/* ()__)____________)))))   :^}  */
/*********************************/

#include "ft_malloc.h"
#include "m_structs.h"

#include <stdio.h>

t_mlc * getHead( void );

static t_mlc *
getnode(void * ptr)
{
    t_mlc * tmp;

    (void)ptr;
    tmp = getHead();
    printf("free this with head : (%p)\n", tmp);
    if (tmp == NULL)
        return (NULL);
    while(tmp->next != NULL) {
        printf("address : (%p) sz : %d\n", tmp, tmp->sz);
        tmp = tmp->next;
    }
    return (tmp);
}

void
ft_free(void * ptr)
{
    t_mlc * tmp;

    tmp = getnode(ptr);
    (void)ptr;
    (void)tmp;
}
