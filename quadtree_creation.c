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
	new_qt->color = MLV_COLOR_BLUE;
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

double	max(double a, double b)
{
	return (a > b ? a : b);
}

void		fill_zone(t_zone *zone, int x1, int x2, int y1, int y2)
{
	(*zone).x1 = x1;
	(*zone).x2 = x2;
	(*zone).y1 = y1;
	(*zone).y2 = y2;
}

void		gen_tree(t_list **l, MLV_Image *img, t_qt **qt, t_zone zone)
{
	t_zone save;
	
	fill_zone(&save, zone.x1, zone.x2, zone.y1, zone.y2);
	if (!(*qt))
	{
		(*qt) = create_tree();
		(*qt)->dist = get_error_dist(img, zone.x1, zone.x2, zone.y1, zone.y2, qt);
		add_order(l, (*qt), (*qt)->dist, zone);
	}
	if (!(*qt)->no)
	{
		(*qt)->no = create_tree();
		(*qt)->no->dist = get_error_dist(img, save.x1, d(save.x1, save.x2), save.y1, d(save.y1, save.y2), &((*qt)->no));
		fill_zone(&zone, save.x1, d(save.x1, save.x2), save.y1, d(save.y1, save.y2));
		add_order(l, (*qt)->no, (*qt)->no->dist, zone);
	}
	if (!(*qt)->ne)
	{
		(*qt)->ne = create_tree();
		(*qt)->ne->dist = get_error_dist(img, d(save.x1, save.x2), save.x2, save.y1, d(save.y1, save.y2), &((*qt)->ne));
		fill_zone(&zone, d(save.x1, save.x2), save.x2, save.y1, d(save.y1, save.y2));
		add_order(l, (*qt)->ne, (*qt)->ne->dist, zone);
	}
	if (!(*qt)->se)
	{
		(*qt)->se = create_tree();
		(*qt)->se->dist = get_error_dist(img, d(save.x1, save.x2), save.x2, d(save.y1, save.y2), save.y2, &((*qt)->se));
		fill_zone(&zone, d(save.x1, save.x2), save.x2, d(save.y1, save.y2), save.y2);
		add_order(l, (*qt)->se, (*qt)->se->dist, zone);
	}
	if (!(*qt)->so)
	{
		(*qt)->so = create_tree();
		(*qt)->so->dist = get_error_dist(img, save.x1, d(save.x1, save.x2), d(save.y1, save.y2), save.y2, &((*qt)->so));
		fill_zone(&zone, save.x1, d(save.x1, save.x2), d(save.y1, save.y2), save.y2);
		add_order(l, (*qt)->so, (*qt)->so->dist, zone);
	}
}

double	find_worst(t_qt *qt, double worst)
{
	if (!qt)
		return (worst);
	return max(
			max(find_worst(qt->no, qt->dist), find_worst(qt->ne, qt->dist)),
			max(find_worst(qt->se, qt->dist), find_worst(qt->so, qt->dist)));

}

void	go_to_worst(t_list **l, MLV_Image *img, double worst, t_qt **qt, t_zone zone)
{
	(void)worst;
	if (!(*qt))
		return ;
	gen_tree(l, img, qt, zone);
/*	if ((*qt)->dist == worst)
	{
		gen_tree(l, img, qt, x1, x2, y1, y2);
		return ;
	}
	go_to_worst(l, img, worst, &(*qt)->no, x1, d(x1, x2), y1, d(y1, y2));
	go_to_worst(l, img, worst, &(*qt)->ne, d(x1, x2), x2, y1, d(y1, y2));
	go_to_worst(l, img, worst, &(*qt)->se, d(x1, x2), x2, d(y1, y2), y2);
	go_to_worst(l, img, worst, &(*qt)->so, x1, d(x1, x2), d(y1, y2), y2);*/
}

/*void	quadtree_maker(MLV_Image *img, t_qt **qt, int operations)
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
		go_to_worst(img, worst, qt, 0, TAILLE_X, 0, TAILLE_Y);
		if (DISPLAY == TRUE)
		{
			MLV_clear_window(MLV_COLOR_BLACK);
			draw_quadtree(*qt, 0, TAILLE_X, 0, TAILLE_Y);
			MLV_actualise_window();
		}
		i++;
	}
}*/

t_list	*go_to_not_processed(t_list **l)
{
	t_list	*tmp;
	
	tmp = *l;
	while (tmp)
	{
		if (tmp->processed == 0)
		{
			printf("dist = %f\n", tmp->dist);
			return tmp;
		}
		tmp = tmp->next;
	}
	return NULL;
}

void	print_zone(t_zone z)
{
	printf("(%d,%d) - (%d, %d)\n", z.x1, z.x2, z.y1, z.y2);
}

void	quadtree_maker2(t_list **l, MLV_Image *img, t_qt **qt, int operations)
{
	int		i;
	t_zone zone;
	t_list	*tmp;
	
	tmp = *l;
	fill_zone(&zone, 0, TAILLE_X, 0, TAILLE_Y);
	i = 0;
	gen_tree(l, img, qt, zone);
	if (!*qt)
		err_what(0);
	print_zone((*l)->next->next->zone);
	while (i < operations)
	{
		tmp = go_to_not_processed(l);
		if (!tmp)
			return ;
		tmp->processed = 1;
		print_zone(tmp->zone);
		go_to_worst(l, img, tmp->dist, &(tmp->ptr), tmp->zone);
		if (DISPLAY == TRUE)
		{
			MLV_clear_window(MLV_COLOR_BLACK);
			draw_quadtree(*qt, 0, TAILLE_X, 0, TAILLE_Y);
			MLV_actualise_window();
		}
		i++;
	}

}

