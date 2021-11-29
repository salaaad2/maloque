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

void
ft_free(void * ptr)
{
    t_mlc * tmp;
    int ret;

    ret = 0;
    if (ptr == NULL)
    { return ; }

    tmp = s_getnode(ptr);
    if (tmp != NULL)
    {
        printf("tmp->sz [%u]\n", tmp->sz);
        ret = munmap(ptr, tmp->sz);
    }

    if (ret != 0)
    { return ; }
}
