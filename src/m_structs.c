/*********************************/
/*   FT_MALLOC        (  //      */
/*   malloc()          ( )/      */
/*   by salade         )(/       */
/*  ________________  ( /)       */
/* ()__)____________)))))   :^}  */
/*********************************/

#include "m_structs.h"

/*
** keep struct in memory for klater use.
** this is a fake global variable
*/
t_mlc *
s_getstruct(t_mlc * mlc)
{
    static t_mlc * ptr = NULL;

    if (mlc != NULL) {
        ptr = mlc;
    }
    return (mlc);
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

    ptr = s_getstruct(NULL);
    while (ptr) {
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

    ptr = s_getstruct(NULL);
    while (ptr->next)
    {
        if (ptr->mapped == addr) {
            break ;
        }
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
