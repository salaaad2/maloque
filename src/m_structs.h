#ifndef M_STRUCTS_H_
#define M_STRUCTS_H_

#include "ft_malloc.h"

t_mlc * s_newnode( t_mlc * head );
t_mlc * s_getnode(void * addr);
t_mlc * s_getstruct(t_mlc * mlc);
t_mlc * s_getlast( void );

#endif
