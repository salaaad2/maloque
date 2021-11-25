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
tiny_tests(void)
{
    char * str;
    char * str2;
    char * rstr;
    char * rstr2;
    int i;

    printf("---------------tiny tests : -------------");
    i = -1;
    str = ft_malloc(12);
    str2 = ft_malloc(14);
    rstr = malloc(12);
    rstr2 = malloc(14);
    if (str != NULL)
    {
        while (++i < 12)
        { rstr[i] = ('a' + i); }
        i = -1;
        while (++i < 14)
        { rstr2[i] = ('k' + i); }
        i = -1;
        while (++i < 12)
        { str[i] = ('a' + i); }
        i = -1;
        while (++i < 14)
        { str2[i] = ('k' + i); }
        printf("str : [%s][%lu]\n", str, strlen(str));
        printf("str2 : [%s][%lu]\n", str2, strlen(str2));
        printf("str : [%s][%lu]\n", str, strlen(str));
        printf("rstr : [%s][%lu]\n", rstr, strlen(rstr));
        printf("rstr2 : [%s][%lu]\n", rstr2, strlen(rstr2));
        printf("rstr : [%s][%lu]\n", rstr, strlen(rstr));
    } else {
        printf("malloc() failed\n");
        return (1);
    }
    printf("---------------END TINY tests : -------------\n");
    return 0;
}

int
main( void )
{
    printf("=========FT_MALLOC=======\nTINY:%u\nSMALL:%u\nLARGE:%u\n", PG_TINY, PG_SMALL, PG_LARGE);
    return (tiny_tests());
}
