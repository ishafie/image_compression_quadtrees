#include "includes/quadtree.h"

t_qt	*create_tree(MLV_Color color)
{
	t_qt	*new_qt;
	
	new_qt = (t_qt*)malloc(sizeof(t_qt));
	/*if (!new_qt)
		malloc_handling();*/
	new_qt->no = NULL;
	new_qt->ne = NULL;
	new_qt->se = NULL;
	new_qt->so = NULL;
	new_qt->color = color;
	return (new_qt);
}

void generate_tree(int prof, int max_prof, t_qt **qt)
{
	if (!qt || !*qt)
		return ;
	if (max_prof == 0)
	{
		/*(*qt)->color = get_average_color_from_image();*/
		return ;
	}
	generate_tree(prof + 1, max_prof - 1, &(*qt)->no);
	generate_tree(prof + 1, max_prof - 1, &(*qt)->ne);
	generate_tree(prof + 1, max_prof - 1, &(*qt)->se);
	generate_tree(prof + 1, max_prof - 1, &(*qt)->so);
}
