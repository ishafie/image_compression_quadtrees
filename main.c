#include "includes/colorlist.h"

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

void 	test_decode(void)
{
	FILE	*fp;
	t_qt	*tree;

	tree = NULL;
	fp = fopen("test", "rb");
	if (!fp)
		err_what(FILE_ISSUE);
	decode_bin(&tree, fp);
	fclose(fp);
	printf("\n");
	draw_quadtree(tree, 0, TAILLE_X, 0, TAILLE_Y);
	MLV_actualise_window();
	MLV_wait_mouse(0, 0);
}

void 	test_encode(t_qt *qt)
{
	FILE	*fp;

	fp = fopen("test", "wb");
	if (!fp)
		err_what(FILE_ISSUE);
	encode(qt, fp);
	fclose(fp);
	printf("\n\n\n");
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
/*	printf("\t\t[%u] - [%u] - [%u] - [%u]\n", qt->no ? qt->no->n_node : 0, qt->ne ? qt->ne->n_node : 0, qt->se ? qt->se->n_node : 0, qt->so ? qt->so->n_node : 0);*/
	parcours_test(qt->no);
	parcours_test(qt->ne);
	parcours_test(qt->se);
	parcours_test(qt->so);
}

void 	test_decode_encode_graph(const char *filename)
{
	t_qt	*qt;

	decodage(filename, &qt, COLOR);
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
	char				*filename;

	g_nb_op_creation = 0;
	g_nb_op_parcours = 0;
	l_dist = NULL;
	lc = create_list_container(l_dist);
	qt = NULL;
	MLV_create_window("QUADTREE", "QUADTREE", TAILLE_X, TAILLE_Y);
	filename = start_screen();
	printf("filename = %s\n", filename);
	MLV_clear_window(MLV_COLOR_BLUE);
	img = MLV_load_image(filename);
	quadtree_maker2(&lc, img, &qt, OP);
	create_interface(qt);
	click_interface(&qt, filename);
	/*analyze_and_minimize(&qt);
	encodage(qt, "lion");*/
	printf("Fin.\n");
	MLV_wait_mouse(0, 0);
	free(filename);
	MLV_free_window();
	return (0);
}
