/*********************************/
/*   FT_MALLOC        (  //      */
/*   main              ( )/      */
/*   by salade         )(/       */
/*  ________________  ( /)       */
/* ()__)____________)))))   :^}  */
/*********************************/

#include "ft_malloc.h"

#include <stdio.h>
#include <unistd.h>

int
main( void )
{
    printf("kernel page size : [%d]\n", getpagesize());

    return 0;
}
