/*********************************/
/*   FT_MALLOC        (  //      */
/*   main              ( )/      */
/*   by salade         )(/       */
/*  ________________  ( /)       */
/* ()__)____________)))))   :^}  */
/*********************************/

#include "ft_malloc.h"

#include <stdio.h>
#include <string.h>
#include <unistd.h>

int
main( void )
{
    printf("kernel page size : [%d]\n", getpagesize());
    char * str;
    char * str2;
    int i;

    i = -1;
    str = ft_malloc(12);
    str2 = ft_malloc(14);
    if (str != NULL && str2 != NULL)
    {
        while (++i < 11)
        { str[i] = ('a' + i); }
        i = -1;
        while (++i < 14)
        { str2[i] = ('k' + i); }
        printf("str : [%s][%lu]\n", str, strlen(str));
        printf("str2 : [%s][%lu]\n", str2, strlen(str2));
        printf("str : [%s][%lu]\n", str, strlen(str));
        printf("str2 : [%s][%lu]\n", str2, strlen(str2));
    } else {
        printf("malloc() failed\n");
    }
    return 0;
}
