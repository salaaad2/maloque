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
s_newnode( t_mlc * head )
{
    t_mlc * ptr;
    t_mlc new;

    ptr = head;
    printf("new node --\nhead size : %d\n", head->sz);
    bzero(&new, sizeof(t_mlc));
    while (ptr->next != NULL) {
        ptr = ptr->next;
    }
    ptr->next = &new;
    return (ptr->next);
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
