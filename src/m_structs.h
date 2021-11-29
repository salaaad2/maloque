#ifndef M_STRUCTS_H_
#define M_STRUCTS_H_

#include "ft_malloc.h"

t_mlc	* s_getstruct(t_mlc * mlc);
t_mlc	* u_lstlast(t_mlc *lst);
t_mlc	*u_lstnew( void );
void	u_lstadd_back(t_mlc **alst, t_mlc *new);
void	u_lstadd_front(t_mlc **alst, t_mlc *new);
void	u_lstclear(t_mlc **lst, void (*del)(void *));
void	u_lstdelone(t_mlc *lst, void (*del)(void *));
int	u_lstsize(t_mlc *lst);
int	u_lstswap(t_mlc * one, t_mlc * two);

#endif
