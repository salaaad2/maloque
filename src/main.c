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

void *
test_alloc(int32_t size, uint8_t c)
{
    char * str;
    char * str2;
    char * rstr;
    char * rstr2;
    int32_t i;

    i = -1;
    str = ft_malloc(size);
    str2 = ft_malloc(size + 4);
    rstr = malloc(size);
    rstr2 = malloc(size + 4);
    if (str != NULL)
    {
        while (++i < size)
        { rstr[i] = c; }
        i = -1;
        while (++i < (size + 4))
        { rstr2[i] = c + 1; }
        i = -1;
        while (++i < size)
        { str[i] = c; }
        i = -1;
        while (++i < (size + 4))
        { str2[i] = c + 1; }
        printf("str : [%.20s][%lu]\n", str, strlen(str));
        printf("str2 : [%.20s][%lu]\n", str2, strlen(str2));
        printf("str : [%.20s][%lu]\n", str, strlen(str));
        printf("rstr : [%.20s][%lu]\n", rstr, strlen(rstr));
        printf("rstr2 : [%.20s][%lu]\n", rstr2, strlen(rstr2));
        printf("rstr : [%.20s][%lu]\n", rstr, strlen(rstr));
    } else {
        printf("malloc() failed\n");
        return (NULL);
    }
    return (str);
}



int
main( void )
{
    char * strtiny;
    char * strsmall;
    printf("=========FT_MALLOC=======\nTINY:%u\nSMALL:%u\nLARGE:%u\n", PG_TINY, PG_SMALL, PG_LARGE);
    printf("---------------TINY      : -------------\n");
    if ((strtiny = test_alloc(12, 'a')) == NULL)
    { printf("tiny tests failed\n");
      return (1); }
    printf("---------------END TINY  : -------------\n");

    printf("---------------SMALL     : -------------\n");
    if ((strsmall = test_alloc(2000, 'k')) == NULL)
    { printf("small tests failed\n");
      return (1); }
    printf("---------------END SMALL : -------------\n");

    printf("=========VERIFY OVERLAP====== \n");
    printf("str allocated from tiny page : \n[%s][%lu]\n", strtiny, strlen(strtiny));
    printf("str allocated from small page : \n[%.20s][%lu]\n", strsmall, strlen(strsmall));
    printf("=========VERIFY FREE ( SIGSEGV )====== \n");
    printf("str allocated from tiny page is located at\n[%p][%lu]\n", strtiny, strlen(strtiny));
    printf("str allocated from small page is located at\n[%p][%lu]\n", strsmall, strlen(strsmall));
    /* ft_free(strtiny); */
    ft_free(strsmall);
    printf("SEGV NOW :\n %s\n", strtiny);
    printf("SEGV NOW :\n %s\n", strsmall);
    return (0);
}
