#include "includes/quadtree.h"

t_qt		*create_tree(void)
{
	t_qt	*new_qt;
	static unsigned int n_node = 0;

	new_qt = (t_qt*)malloc(sizeof(t_qt));
	if (!new_qt)
		malloc_handling();
	new_qt->no = NULL;
	new_qt->ne = NULL;
	new_qt->se = NULL;
	new_qt->so = NULL;
	new_qt->dist = -1;
	new_qt->n_node = n_node;
	new_qt->color = MLV_COLOR_BLUE;
	new_qt->cl = NULL;
	n_node++;
	return (new_qt);
}

void 		delete_tree(t_qt **qt)
{
	if (!*qt)
		return ;
	delete_tree(&(*qt)->no);
	delete_tree(&(*qt)->ne);
	delete_tree(&(*qt)->se);
	delete_tree(&(*qt)->so);
	free(*qt);
	*qt = NULL;
}

static int	d(int x1, int x2)
{
	return (x2 - ((x2 - x1) / 2));
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

void 		create_list_and_tree(t_qt **qt, t_lc **l, MLV_Image *img, int x1, int x2, int y1, int y2)
{
	t_zone	zone;

	(*qt) = create_tree();
	(*qt)->dist = get_error_dist(img, x1, x2, y1, y2, qt);;
	if ((*qt)->dist <= 80.0 && (x2 - x1) > 1 && (y2 - y1) > 1) /* pour accelerer la creation meme si perte */
		return ;
	fill_zone(&zone, x1, x2, y1, y2);
	add_order(&(*l)->first, &(*l)->last, (*qt), (*qt)->dist, zone);
}

int			gen_tree(t_lc **l, MLV_Image *img, t_qt **qt, t_zone zone)
{
	t_zone				save;

	fill_zone(&save, zone.x1, zone.x2, zone.y1, zone.y2);
	if (!(*qt))
	{
		(*qt) = create_tree();
		(*qt)->dist = get_error_dist(img, zone.x1, zone.x2, zone.y1, zone.y2, qt);
		add_order(&(*l)->first, &(*l)->last,(*qt), (*qt)->dist, zone);
	}
	if (!(*qt)->no)
		create_list_and_tree(&(*qt)->no, l, img, save.x1, d(save.x1, save.x2), save.y1, d(save.y1, save.y2));
	if (!(*qt)->ne)
		create_list_and_tree(&(*qt)->ne, l, img, d(save.x1, save.x2), save.x2, save.y1, d(save.y1, save.y2));
	if (!(*qt)->se)
		create_list_and_tree(&(*qt)->se, l, img, d(save.x1, save.x2), save.x2, d(save.y1, save.y2), save.y2);
	if (!(*qt)->so)
		create_list_and_tree(&(*qt)->so, l, img, save.x1, d(save.x1, save.x2), d(save.y1, save.y2), save.y2);
	return (1);
}

double	find_worst(t_qt *qt, double worst)
{
	if (!qt)
		return (worst);
	return max(
			max(find_worst(qt->no, qt->dist), find_worst(qt->ne, qt->dist)),
			max(find_worst(qt->se, qt->dist), find_worst(qt->so, qt->dist)));
}

void	go_to_worst(t_lc **l, MLV_Image *img, t_qt **qt, t_zone zone)
{
	if (!(*qt))
		return ;
	gen_tree(l, img, qt, zone);
}

/*void	quadtree_maker(MLV_Image *img, t_qt **qt, int operations)
{
	int		i;
	double	worst;

	i = 0;
	worst = -1;
	gen_tree(img, qt, 0, TAILLE_X, 0, TAILLE_Y);
	if (!*qt)
	while (i < operations)
		err_what(0);
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


void	print_zone(t_zone z)
{
	printf("(%d,%d) - (%d, %d)\n", z.x1, z.x2, z.y1, z.y2);
}

void	quadtree_maker2(t_lc **l, MLV_Image *img, t_qt **qt, int operations)
{
	int		i;
	int		pct;
	float	pct_calc;
	t_zone zone;
	t_list	*tmp;

	pct = 0;
	if (!*l)
		return ;
	tmp = NULL;
	fill_zone(&zone, 0, TAILLE_X, 0, TAILLE_Y);
	i = 0;
	gen_tree(l, img, qt, zone);
	if (!*qt)
		err_what(0);
	printf("Creation de l'arbre entier...\n");
	while (i < operations)
	{
		if (!(*l)->first)
		{
			printf("100%%\n");
			return ;
		}
		go_to_worst(l, img, &((*l)->first->ptr), (*l)->first->zone);
		if ((*l)->first)
		{
			tmp = (*l)->first;
			(*l)->first = (*l)->first->next;
			free(tmp);
			tmp = NULL;
		}
		if (DISPLAY == TRUE)
		{
			MLV_clear_window(MLV_COLOR_BLACK);
			draw_quadtree(*qt, 0, TAILLE_X, 0, TAILLE_Y);
			MLV_actualise_window();
		}
		pct_calc = ((float)i / (float)operations) * 100;
		if (operations != 0 && (int)pct_calc >= pct + 5)
		{
			pct = (int)pct_calc;
			printf("%d%%\n", pct);
		}
		i++;
	}
	printf("100%%\n");
}
