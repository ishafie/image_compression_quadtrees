#include "includes/quadtree.h"

t_qt		*create_tree(void)
{
	t_qt	*new_qt;
	
	new_qt = (t_qt*)malloc(sizeof(t_qt));
	if (!new_qt)
		malloc_handling();
	new_qt->no = NULL;
	new_qt->ne = NULL;
	new_qt->se = NULL;
	new_qt->so = NULL;
	new_qt->dist = -1;
	new_qt->color = MLV_COLOR_BLACK;
	return (new_qt);
}

static int	d(int x1, int x2)
{
	return (x2 - ((x2 - x1) / 2));
}


void	generate_tree_test(MLV_Image *img, int max_prof, t_qt **qt, int x1, int x2, int y1, int y2)
{
	(*qt) = create_tree();
	(*qt)->dist = get_error_dist(img, x1, x2, y1, y2, qt);
	if (max_prof == 0)
	{
		printf("x1 = %d -> x2 = %d | y1 = %d -> y2 = %d\n", x1, x2, y1, y2);
		return ;
	}
	printf("NO\n");
	generate_tree_test(img, max_prof - 1, &(*qt)->no, x1, d(x1, x2), y1, d(y1, y2));
	printf("NE\n");
	generate_tree_test(img, max_prof - 1, &(*qt)->ne, d(x1, x2), x2, y1, d(y1, y2));
	printf("SE\n");
	generate_tree_test(img, max_prof - 1, &(*qt)->se, d(x1, x2), x2, d(y1, y2), y2);
	printf("SO\n");
	generate_tree_test(img, max_prof - 1, &(*qt)->so, x1, d(x1, x2), d(y1, y2), y2);
}

double		dist(t_color px, t_color moy)
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

double		get_error_dist(MLV_Image *img, int x1, int x2, int y1, int y2, t_qt **qt)
{
	t_color		moy;
	t_color		px;
	double		distance;
	int			save_x1;
	
	save_x1 = x1;
	distance = 0;
	moy = get_average_rgba_from_image(img, x1, x2, y1, y2);
	if (*qt)
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

static double	max(double a, double b)
{
	return (a > b ? a : b);
}

double			worst_zone(double no, double ne, double se, double so)
{
	return (max(max(no, ne), max(so, se)));
}

int		generate_tree(MLV_Image *img, int max_prof, t_qt **qt, int x1, int x2, int y1, int y2)
{	
	if (!*qt)
		(*qt) = create_tree();
		(void)max_prof;
	/*(*qt)->dist = get_error_dist(img, x1, x2, y1, y2, qt);*/
	/*if (max_prof == 0)
		return ;*/
	if (!(*qt)->no)
		(*qt)->no = create_tree();
	if (!(*qt)->ne)
		(*qt)->ne = create_tree();
	if (!(*qt)->se)
		(*qt)->se = create_tree();
	if (!(*qt)->so)
		(*qt)->so = create_tree();
	(*qt)->no->dist = get_error_dist(img, x1, d(x1, x2), y1, d(y1, y2), qt);
	(*qt)->ne->dist = get_error_dist(img, d(x1, x2), x2, y1, d(y1, y2), qt);
	(*qt)->se->dist = get_error_dist(img, d(x1, x2), x2, d(y1, y2), y2, qt);
	(*qt)->so->dist = get_error_dist(img, x1, d(x1, x2), d(y1, y2), y2, qt);
	return (worst_zone((*qt)->no->dist, (*qt)->ne->dist, (*qt)->se->dist, (*qt)->so->dist));
/*	if ((*qt)->no->dist == best)
		generate_tree(img, max_prof - 1, &(*qt)->no, x1, d(x1, x2), y1, d(y1, y2));
	else if ((*qt)->ne->dist == best)
		generate_tree(img, max_prof - 1, &(*qt)->ne, d(x1, x2), x2, y1, d(y1, y2));
	else if ((*qt)->se->dist == best)
		generate_tree(img, max_prof - 1, &(*qt)->se, d(x1, x2), x2, d(y1, y2), y2);
	else if ((*qt)->so->dist == best)
		generate_tree(img, max_prof - 1, &(*qt)->so, x1, d(x1, x2), d(y1, y2), y2);*/
	/*	
	generate_tree(img, max_prof - 1, &(*qt)->no, x1, d(x1, x2), y1, d(y1, y2));
	generate_tree(img, max_prof - 1, &(*qt)->ne, d(x1, x2), x2, y1, d(y1, y2));
	generate_tree(img, max_prof - 1, &(*qt)->se, d(x1, x2), x2, d(y1, y2), y2);
	generate_tree(img, max_prof - 1, &(*qt)->so, x1, d(x1, x2), d(y1, y2), y2);
	* */
}

void		gen_tree(MLV_Image *img, t_qt **qt, int x1, int x2, int y1, int y2)
{
	if (!(*qt))
	{
		(*qt) = create_tree();
		(*qt)->dist = get_error_dist(img, x1, x2, y1, y2, qt);;
	}
	if (!(*qt)->no)
		(*qt)->no = create_tree();
	if (!(*qt)->ne)
		(*qt)->ne = create_tree();
	if (!(*qt)->se)
		(*qt)->se = create_tree();
	if (!(*qt)->so)
		(*qt)->so = create_tree();
	(*qt)->no->dist = get_error_dist(img, x1, d(x1, x2), y1, d(y1, y2), &((*qt)->no));
	(*qt)->ne->dist = get_error_dist(img, d(x1, x2), x2, y1, d(y1, y2), &((*qt)->ne));
	(*qt)->se->dist = get_error_dist(img, d(x1, x2), x2, d(y1, y2), y2, &((*qt)->se));
	(*qt)->so->dist = get_error_dist(img, x1, d(x1, x2), d(y1, y2), y2, &((*qt)->so));
}

double	find_worst(t_qt *qt, double worst)
{
	if (!qt)
		return (worst);
	return max(
			max(find_worst(qt->no, qt->dist), find_worst(qt->ne, qt->dist)),
			max(find_worst(qt->se, qt->dist), find_worst(qt->so, qt->dist)));

}

void	go_to_worst(MLV_Image *img, double worst, t_qt **qt, int x1, int x2, int y1, int y2)
{
	if (!(*qt))
		return ;
	if ((*qt)->dist == worst)
	{
		gen_tree(img, qt, x1, x2, y1, y2);
		return ;
	}
	go_to_worst(img, worst, &(*qt)->no, x1, d(x1, x2), y1, d(y1, y2));
	go_to_worst(img, worst, &(*qt)->ne, d(x1, x2), x2, y1, d(y1, y2));
	go_to_worst(img, worst, &(*qt)->se, d(x1, x2), x2, d(y1, y2), y2);
	go_to_worst(img, worst, &(*qt)->so, x1, d(x1, x2), d(y1, y2), y2);		
}

void	quadtree_maker(MLV_Image *img, t_qt **qt, int operations)
{
	int		i;
	double	worst;
	
	i = 0;
	worst = -1;
	gen_tree(img, qt, 0, TAILLE_X, 0, TAILLE_Y);
	if (!*qt)
		err_what(0);
	while (i < operations)
	{
		worst = find_worst(*qt, (*qt)->dist);
		/*printf("worst = %f\n", worst);*/
		go_to_worst(img, worst, qt, 0, TAILLE_X, 0, TAILLE_Y);
		i++;
	}
}

/*void	parcours_tree(MLV_Image *img, int max_prof, t_qt **qt, int x1, int x2, int y1, int y2)
{
	int	worst;
	
	worst = -1;
	(void)worst;
	if (!(*qt))
		worst = generate_tree(img, max_prof, qt, x1, x2, y1, y2);
	find_worst(*qt, (*qt)->dist);
}*/
