/*********************************/
/*   FT_MALLOC        (  //      */
/*   malloc()          ( )/      */
/*   by salade         )(/       */
/*  ________________  ( /)       */
/* ()__)____________)))))   :^}  */
/*********************************/

#include "m_structs.h"

#include <stdio.h>
#include <strings.h>

/*
** keep struct in memory for klater use.
** this is a fake global variable
*/
t_mlc *
s_getstruct(t_mlc * mlc)
{
    static t_mlc * ptr = NULL;

    printf("call to get\n");
    if (ptr == NULL) {
        printf("setstruct(%u)\n", mlc->sz);
        ptr = mlc;
        ptr->t_left = 0;
        ptr->s_left = 0;
        ptr->l_left = 0;
        ptr->left = &ptr->t_left;
    } else {
        printf("return static ptr\n");
    }
    return (ptr);
}

/*
** create a node on the stack.
** place it at the end of the global struct
*/
t_mlc *
s_newnode( void )
{
    t_mlc * ptr;
    t_mlc new;

    printf("new node\n");
    bzero(&new, sizeof(t_mlc));
    ptr = s_getstruct(NULL);
    while (ptr) {
        printf("one step closer to the last\n");
        ptr = ptr->next;
    }
    ptr = &new;
    return (ptr);
}

/*
** get node from address
** this is useful for free and realloc
*/
t_mlc *
s_getnode(void * addr)
{
    t_mlc * ptr;
    int i;

    i = 0;
    ptr = s_getstruct(NULL);
    while (ptr->next)
    {
        if (ptr->mapped == addr) {
            break ;
        }
        printf("%d th element\n", i);
        i++;
        ptr = ptr->next;
    }
    return (ptr);
}

t_mlc *
s_getlast( void )
{
    t_mlc * ptr;

    ptr = s_getstruct(NULL);
    while (ptr->next)
    {
        ptr = ptr->next;
    }
    return (ptr);
}
