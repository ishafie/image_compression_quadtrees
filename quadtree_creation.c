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
	new_qt->dist = 0;
	new_qt->color = MLV_COLOR_WHITE;
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

double	dist(t_color px, t_color moy)
{
	double powr;
	double powg;
	double powb;
	double powa;
	
	powr = (px.red - moy.red) * (px.red - moy.red);
	powg = (px.green - moy.green) * (px.green - moy.green);
	powb = (px.blue - moy.blue) * (px.blue - moy.blue);
	powa = (px.alpha - moy.alpha) * (px.alpha - moy.alpha);
	return (sqrt(powr + powg + powb + powa));
}

double	get_error_dist(MLV_Image *img, int x1, int x2, int y1, int y2, t_qt **qt)
{
	t_color		moy;
	t_color		px;
	double		distance;
	int			save_x1;
	
	save_x1 = x1;
	distance = 0;
	moy = get_average_rgba_from_image(img, x1, x2, y1, y2);
	(void)qt;
	(*qt)->color = MLV_convert_rgba_to_color(moy.red, moy.green, moy.blue, moy.alpha);
	while (y1 < y2)
	{
		while (x1 < x2)
		{
			MLV_get_pixel_on_image(img, x1, y1, &(px.red), &(px.green),
				&(px.blue), &(px.alpha));
			distance += dist(px, moy); 
			x1++;
		}
		x1 = save_x1;
		y1++;
	}
	return (distance);
}

void	generate_tree(MLV_Image *img, int max_prof, t_qt **qt, int x1, int x2, int y1, int y2)
{
	(*qt) = create_tree();
	(*qt)->dist = get_error_dist(img, x1, x2, y1, y2, qt);
	if (max_prof == 0)
		return ;
	generate_tree(img, max_prof - 1, &(*qt)->no, x1, d(x1, x2), y1, d(y1, y2));
	generate_tree(img, max_prof - 1, &(*qt)->ne, d(x1, x2), x2, y1, d(y1, y2));
	generate_tree(img, max_prof - 1, &(*qt)->se, d(x1, x2), x2, d(y1, y2), y2);
	generate_tree(img, max_prof - 1, &(*qt)->so, x1, d(x1, x2), d(y1, y2), y2);
}
