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

void 		fill_thread_args(t_thread *args, t_qt **qt, t_lc **l, MLV_Image *img, int x1, int x2, int y1, int y2)
{
	args->qt = qt;
	args->l = l;
	args->img = img;
	args->x1 = x1;
	args->x2 = x2;
	args->y1 = y1;
	args->y2 = y2;
}

void 		*create_list_and_tree_thread(void *args)
{
	t_zone		zone;
	t_thread	*arg;
	t_qt		**qt;
	t_lc		**l;
	MLV_Image	*img;
	int			x1, x2, y1, y2;

	arg = (t_thread*)args;
	qt = arg->qt;
	l = arg->l;
	img = arg->img;
	x1 = arg->x1;
	x2 = arg->x2;
	y1 = arg->y1;
	y2 = arg->y2;
	(*qt) = create_tree();
	(*qt)->dist = get_error_dist(img, x1, x2, y1, y2, qt);
	fill_zone(&zone, x1, x2, y1, y2);
	add_order(&(*l)->first, &(*l)->last, (*qt), (*qt)->dist, zone);
	return (NULL);
}

void 		create_list_and_tree(t_qt **qt, t_lc **l, MLV_Image *img, int x1, int x2, int y1, int y2)
{
	t_zone zone;
	/*int pthread_create(pthread_t *thread, pthread_attr_t *attr, void *(*start_routine) (void *), void *arg);*/
	(*qt) = create_tree();
	(*qt)->dist = get_error_dist(img, x1, x2, y1, y2, qt);
	fill_zone(&zone, x1, x2, y1, y2);
	add_order(&(*l)->first, &(*l)->last, (*qt), (*qt)->dist, zone);
}

int			join_thread(pthread_t *thread_store, int nb_thread)
{
	static int nb_closed = 0;
	int		i;

	i = 0;
	for (i = 0; i < nb_thread; i++)
	{
		if (!pthread_join(thread_store[i], NULL))
			nb_closed++;
	}
	free(thread_store);
	return (1);
}

int			gen_tree(t_lc **l, MLV_Image *img, t_qt **qt, t_zone zone)
{
	int					nb_thread;
	t_zone				save;
	pthread_t			*thread_store;
	t_thread			args[4];

	nb_thread = 0;
	fill_zone(&save, zone.x1, zone.x2, zone.y1, zone.y2);
	if (!(*qt))
	{
		(*qt) = create_tree();
		(*qt)->dist = get_error_dist(img, zone.x1, zone.x2, zone.y1, zone.y2, qt);
		add_order(&(*l)->first, &(*l)->last,(*qt), (*qt)->dist, zone);
	}

	/*thread_store = (pthread_t*)malloc(sizeof(pthread_t) * 4);
	if (!thread_store)
		malloc_handling();
	fill_thread_args(&args[0], &((*qt)->no), l, img, save.x1, d(save.x1, save.x2), save.y1, d(save.y1, save.y2));
	fill_thread_args(&args[1], &((*qt)->ne), l, img, d(save.x1, save.x2), save.x2, save.y1, d(save.y1, save.y2));
	fill_thread_args(&args[2], &((*qt)->se), l, img, d(save.x1, save.x2), save.x2, d(save.y1, save.y2), save.y2);
	fill_thread_args(&args[3], &((*qt)->so), l, img, save.x1, d(save.x1, save.x2), d(save.y1, save.y2), save.y2);
	if (!(*qt)->no)
	{
		if (pthread_create(&thread_store[nb_thread], NULL, create_list_and_tree_thread, (void*)&args[0]))
			exit(EXIT_FAILURE);
		nb_thread++;
	}
	if (!(*qt)->ne)
	{
		if (pthread_create(&thread_store[nb_thread], NULL, create_list_and_tree_thread, (void*)&args[1]))
			exit(EXIT_FAILURE);
		nb_thread++;
	}
	if (!(*qt)->se)
	{
		if (pthread_create(&thread_store[nb_thread], NULL, create_list_and_tree_thread, (void*)&args[2]))
			exit(EXIT_FAILURE);
		nb_thread++;
	}
	if (!(*qt)->so)
	{
		if (pthread_create(&thread_store[nb_thread], NULL, create_list_and_tree_thread, (void*)&args[3]))
			exit(EXIT_FAILURE);
		nb_thread++;
	}
	join_thread(thread_store, nb_thread);
	*/

	(void)args;
	(void)thread_store;
	(void)nb_thread;
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

t_list	*go_to_not_processed(t_lc **l, t_list **prev)
{
	t_list	*tmp;

	tmp = (*l)->first;
	*prev = NULL;
	while (tmp)
	{
		g_nb_op_parcours++;
		if (tmp->processed == 0)
			return tmp;
		*prev = tmp;
		tmp = tmp->next;
	}
	return NULL;
}

void	print_zone(t_zone z)
{
	printf("(%d,%d) - (%d, %d)\n", z.x1, z.x2, z.y1, z.y2);
}

void	quadtree_maker2(t_lc **l, MLV_Image *img, t_qt **qt, int operations)
{
	int		i;
	t_zone zone;
	t_list	*tmp;

	if (!*l)
		return ;
	tmp = NULL;
	fill_zone(&zone, 0, TAILLE_X, 0, TAILLE_Y);
	i = 0;
	gen_tree(l, img, qt, zone);
	if (!*qt)
		err_what(0);
	while (i < operations)
	{
		/*printf("i = %d\n", i);*/
		/*tmp = go_to_not_processed(l, &prev);
		if (!tmp)
			return ;*/
		if (!(*l)->first)
			return ;
		go_to_worst(l, img, &((*l)->first->ptr), (*l)->first->zone);
		/*tmp->processed = 1;*/
		/*analyze_and_minimize(l, qt);*/
		if ((*l)->first)
		{
			tmp = (*l)->first;
			(*l)->first = (*l)->first->next;
			free(tmp);
			tmp = NULL;
		}
		/*
		if (prev)
		{
			prev->next = tmp->next;
			free(tmp);
			tmp = NULL;
		}
		else
		{
			if ((*l)->first)
			{
				tmp = (*l)->first;
				(*l)->first = (*l)->first->next;
				free(tmp);
			}
		}*/
		if (DISPLAY == TRUE)
		{
			MLV_clear_window(MLV_COLOR_BLACK);
			draw_quadtree(*qt, 0, TAILLE_X, 0, TAILLE_Y);
			MLV_actualise_window();
		}
		i++;
	}

}
