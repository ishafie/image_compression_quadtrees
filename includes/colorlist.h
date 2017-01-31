#ifndef COLORLIST_H
# define COLORLIST_H

# include "quadtree_struct.h"

typedef struct							s_colorlist
{
	struct s_quadtree					**qt;
	int									deleted;
	struct s_colorlist					*next;
	struct s_colorlist					*prev;
	struct s_colorlist_container		*container;
}										t_cl;

typedef struct							s_colorlist_index
{
	struct s_colorlist_container		*index;
	struct s_colorlist_index			*next;
}										t_ci;

typedef struct							s_colorlist_container
{
	struct s_colorlist					*first;
	struct s_colorlist					*last;
}										t_clc;

void 			delete_tree_and_colorlist(t_qt **qt);
t_cl 			*delete_any_colorlist(t_clc **c, t_cl *del);
void 			addback_colorlist(t_clc **c, t_qt **qt);
void 			addfront_colorindex(t_ci **c, t_qt **qt);
void 			update_colorlist(t_ci **ci, t_qt **qt);
void 			addfront_colorindex(t_ci **c, t_qt **qt);
int				count_color_line(t_clc *c);
int				count_color(t_ci *c);
void 			minimize2(t_ci **c, t_qt ***garbage_collector);
void 			delete_colorlist(t_ci **ci);

void 			display_colorlist(t_clc *clc);
void 			display_colorlist_otherway(t_clc *clc);
void 			test_colorlist(t_ci *ci);
t_qt			*test_search_nb(unsigned int node, t_qt *b);
#endif
