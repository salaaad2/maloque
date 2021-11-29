#ifndef M_STRUCTS_H_
#define M_STRUCTS_H_

#include "ft_malloc.h"

t_mlc * s_newnode( void );
t_mlc * s_getnode(void * addr);
t_mlc * s_getstruct(t_mlc * mlc);

#endif
