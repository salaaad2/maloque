/*********************************/
/*   FT_MALLOC        (  //      */
/*   free()            ( )/      */
/*   by salade         )(/       */
/*  ________________  ( /)       */
/* ()__)____________)))))   :^}  */
/*********************************/

#include "ft_malloc.h"
#include <stdio.h>

void
ft_free(void * ptr)
{
    int  ret;

    ret = 0;
    if (ptr == NULL)
    { return ; }

    printf("%lu\n", sizeof(ptr));
    ret = munmap(ptr, sizeof(ptr));
    if (ret != 0)
        return;
}
