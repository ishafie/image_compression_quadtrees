#ifndef QUADTREE_STRUCT_H
# define QUADTREE_STRUCT_H

# define TAILLE_X 512
# define TAILLE_Y 512

#include "libinclude.h"


typedef struct					s_zone
{
	int							x1;
	int							x2;
	int							y1;
	int							y2;
}								t_zone;

typedef struct					s_quadtree
{
	struct s_quadtree			*par;
	struct s_quadtree			*no;
	struct s_quadtree			*ne;
	struct s_quadtree			*se;
	struct s_quadtree			*so;
	struct s_colorlist			*cl;
	int							deleted;
	unsigned int				n_node;
	double						dist;
	MLV_Color					color;
}								t_qt;

typedef struct					s_list
{
	struct s_list				*next;
	struct s_list				*prev;
	struct s_quadtree			*ptr;
	double						dist;
	struct s_zone				zone;
}								t_list;

typedef struct					s_list_container
{
	struct s_list				*first;
	struct s_list				*last;
}								t_lc;


#endif
