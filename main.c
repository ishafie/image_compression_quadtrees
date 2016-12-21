#include "includes/quadtree.h"

void	test_color(void)
{
	MLV_Image *img;
	MLV_Color color;
	int	x;
	int y;

	x = 0;
	y = 0;
	img = MLV_load_image("img/mr_bean.jpg");

	while (y < TAILLE_Y)
	{
		while (x < TAILLE_X)
		{
			color = get_average_color_from_image(img, x, x + 32, y, y + 32);
			MLV_draw_filled_rectangle(x, y, 32, 32, color);
			x += 32;
		}
		x = 0;
		y += 32;
	}
}

void		test_decode_encode(t_qt *qt)
{
	int		i;
	int		len;
	t_qt	*tree;
	unsigned char	*buf;

	i = 0;
	len = count_node(qt);
	printf("%d\n", len);
	tree = NULL;
	buf = (unsigned char*)malloc(sizeof(unsigned char) * (len * 200));
	if (!buf)
		malloc_handling();
	while (i < len + 1)
		buf[i++] = 0;
	i = 0;
	encode(qt, &buf, &i);
	len = i;
	i = 0;
	while (i < len)
	{
		(void)buf;
		i++;
	}
	i = 0;
	printf("\n\n\n");
	decode(&tree, buf, &i, len);
	printf("\n");
	draw_quadtree(qt, 0, TAILLE_X, 0, TAILLE_Y);
	MLV_actualise_window();
	MLV_wait_mouse(0, 0);
	MLV_clear_window(MLV_COLOR_BLACK);
	MLV_actualise_window();
	draw_quadtree(tree, 0, TAILLE_X, 0, TAILLE_Y);
	MLV_actualise_window();
	MLV_wait_mouse(0, 0);
	write_in_file("lion", buf, len);
}

void	test_lstorder(t_list *l_dist, t_list *last)
{
	t_zone zone;

	fill_zone(&zone, 0, 0, 0, 0);
	add_order(&l_dist, &last, NULL, 1, zone);
	add_order(&l_dist, &last, NULL, 1, zone);
	add_order(&l_dist, &last, NULL, 10, zone);
	add_order(&l_dist, &last, NULL, 5, zone);
	add_order(&l_dist, &last, NULL, 2, zone);
	add_order(&l_dist, &last, NULL, 2, zone);
	add_order(&l_dist, &last, NULL, 6, zone);
	add_order(&l_dist, &last, NULL, 3, zone);
	add_order(&l_dist, &last, NULL, 4, zone);
	add_order(&l_dist, &last, NULL, 0, zone);
	display_list(l_dist, last);
}

void 	parcours_test(t_qt *qt)
{
	if (!qt)
		return ;
	printf("[%p] - > [%u] -> [%x]\n", (void*)qt, qt->n_node, qt->n_node);
	printf("\t\t[%u] - [%u] - [%u] - [%u]\n", qt->no ? qt->no->n_node : 0, qt->ne ? qt->ne->n_node : 0, qt->se ? qt->se->n_node : 0, qt->so ? qt->so->n_node : 0);
	parcours_test(qt->no);
	parcours_test(qt->ne);
	parcours_test(qt->se);
	parcours_test(qt->so);
}

void 	test_decode_encode_graph(const char *filename)
{
	t_qt	*qt;

	decodage(filename, &qt);
	printf("fin du decodage\n");
	MLV_wait_mouse(0, 0);
	MLV_clear_window(MLV_COLOR_BLACK);
	draw_quadtree(qt, 0, TAILLE_X, 0, TAILLE_Y);
	MLV_actualise_window();
	MLV_wait_mouse(0, 0);
}

int		main(void)
{
	t_qt				*qt;
	t_lc				*lc;
	t_list				*l_dist;
	MLV_Image 			*img;

	g_nb_op_creation = 0;
	g_nb_op_parcours = 0;
	lc = (t_lc*)malloc(sizeof(t_lc));
	l_dist = NULL;
	lc->first = l_dist;
	lc->last = l_dist;
	qt = NULL;
	MLV_create_window("QUADTREE", "QUADTREE", TAILLE_X, TAILLE_Y);
	img = MLV_load_image("img/lion.png");
	quadtree_maker2(&lc, img, &qt, OP);
	analyze_and_minimize(&qt);
	encodage(qt, "lion");
	MLV_clear_window(MLV_COLOR_BLUE);
	draw_quadtree(qt, 0, TAILLE_X, 0, TAILLE_Y);
	MLV_actualise_window();
	MLV_wait_mouse(0, 0);
	MLV_free_window();
	return (0);
}
