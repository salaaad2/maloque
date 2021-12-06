/*********************************/
/*   FT_MALLOC        (  //      */
/*   structs           ( )/      */
/*   by salade         )(/       */
/*  ________________  ( /)       */
/* ()__)____________)))))   :^}  */
/*********************************/

#include "m_structs.h"

#include <stdio.h>
#include <strings.h>

int
u_lstsize(t_mlc *lst)
{
    int	i;

    if (lst == NULL)
        return (0);
    i = 0;
    while (lst != NULL)
    {
        lst = lst->next;
        i++;
    }
    return (i);
}

t_mlc	*
u_lstlast(t_mlc *lst)
{
    if (lst == NULL)
    {
        return (NULL);
    } else if (lst->next == NULL) {
        return (lst);
    }
    while (lst->next != NULL)
    {
        lst = lst->next;
    }
    return (lst);
}

int
u_lstswap(t_mlc * one, t_mlc * two)
{
    one->next = two->next;
    two->next = one;
    return (0);
}


void	u_lstdelone(t_mlc *lst, void (*del)(void *))
{
    if (lst != NULL)
    {
        del(lst->mapped);
        free(lst);
    }
}

void	u_lstclear(t_mlc **lst, void (*del)(void *))
{
    t_mlc	*tmp;
    t_mlc	*renext;

    if (lst == NULL)
    {
        return ;
    }
    tmp = *lst;
    while (tmp != NULL)
    {
        renext = tmp->next;
        del(tmp->mapped);
        free(tmp);
        tmp = renext;
    }
    *lst = NULL;
}

void	u_lstadd_front(t_mlc **alst, t_mlc *new)
{
    if (alst == NULL || new == NULL)
    {
        return ;
    }
    new->next = *alst;
    *alst = new;
}

void	u_lstadd_back(t_mlc **alst, t_mlc *new)
{
    t_mlc	*tmp;

    if (alst == NULL || new == NULL)
    {
        return ;
    }
    if (*alst == NULL)
    {
        *alst = new;
    }
    else
    {
        printf("lstlast (%p)\n", *alst);
        tmp = u_lstlast(*alst);
        tmp->next = new;
    }
}

t_mlc	*u_lstnew( void )
{
    t_mlc	*nlst;

    nlst = (t_mlc*)calloc(1, sizeof(t_mlc));
    if (nlst == NULL)
    {
        return (NULL);
    }
    nlst->next = NULL;
    return (nlst);
}
