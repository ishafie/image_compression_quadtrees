#include "includes/quadtree.h"

t_qt	*create_tree(void)
{
	t_qt	*new_qt;
	
	new_qt = (t_qt*)malloc(sizeof(t_qt));
	/*if (!new_qt)
		malloc_handling();*/
	new_qt->no = NULL;
	new_qt->ne = NULL;
	new_qt->se = NULL;
	new_qt->so = NULL;
	return (new_qt);
}

static int		d(int x1, int x2)
{
	return (x2 - ((x2 - x1) / 2));
}

/*
void	generate_tree(MLV_Image *img, int max_prof, t_qt **qt, int x1, int x2, int y1, int y2)
{
	MLV_Color color;
	
	color = MLV_COLOR_BLACK;
	if (max_prof == 0)
	{
		printf("x1 = %d -> x2 = %d | y1 = %d -> y2 = %d\n", x1, x2, y1, y2);
		return ;
	}
	color = get_average_color_from_image(img, x1, x2, y1, y2);
	(*qt) = create_tree(color);
	printf("NO\n");
	generate_tree(img, max_prof - 1, &(*qt)->no, x1, d(x1, x2), y1, d(y1, y2));
	printf("NE\n");
	generate_tree(img, max_prof - 1, &(*qt)->ne, d(x1, x2), x2, y1, d(y1, y2));
	printf("SE\n");
	generate_tree(img, max_prof - 1, &(*qt)->se, d(x1, x2), x2, d(y1, y2), y2);
	printf("SO\n");
	generate_tree(img, max_prof - 1, &(*qt)->so, x1, d(x1, x2), d(y1, y2), y2);
}*/

void	generate_tree(MLV_Image *img, int max_prof, t_qt **qt, int x1, int x2, int y1, int y2)
{
	(*qt) = create_tree();
	if (max_prof == 0)
		return ;
	generate_tree(img, max_prof - 1, &(*qt)->no, x1, d(x1, x2), y1, d(y1, y2));
	generate_tree(img, max_prof - 1, &(*qt)->ne, d(x1, x2), x2, y1, d(y1, y2));
	generate_tree(img, max_prof - 1, &(*qt)->se, d(x1, x2), x2, d(y1, y2), y2);
	generate_tree(img, max_prof - 1, &(*qt)->so, x1, d(x1, x2), d(y1, y2), y2);
}
