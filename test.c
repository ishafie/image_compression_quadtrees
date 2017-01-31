#include "includes/quadtree.h"
#include "includes/test.h"
#include "includes/err.h"

void 		test_colorlist(t_ci *ci)
{
	t_ci	*tmp;
	t_cl	*tl;
	int		i;

	i = 0;
	tmp = ci;
	while (tmp && i < 1) /* 30 = long | 7 = short*/
	{
		display_colorlist(tmp->index);
		tmp = tmp->next;
		i++;
	}
	return ;
	tl = tmp->index->last->prev;
	display_colorlist(tmp->index);

	MLV_wait_mouse(0, 0);
	tl = delete_any_colorlist(&(tmp->index), tl);
	display_colorlist(tmp->index);
	tl = delete_any_colorlist(&(tmp->index), tl);
	display_colorlist(tmp->index);
	MLV_wait_mouse(0, 0);
	/*while (tl)
	{
		display_colorlist(tmp->index);
		if (tl && tl->deleted != 1 && tl->qt && (*(tl->qt))
			&& (*(tl->qt))->n_node)
			printf("node : %d\n", (*(tl->qt))->n_node);
		tl = delete_any_colorlist(&(tmp->index), tl);
		printf("\n list : ");
		MLV_wait_mouse(0, 0);
	}*/
}

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
	parcours_test(qt->no);
	parcours_test(qt->ne);
	parcours_test(qt->se);
	parcours_test(qt->so);
}

void 	test_decode_encode_graph(const char *filename)
{
	t_qt	*qt;

	hub_decode_graph(filename, &qt, COLOR);
	printf("fin du hub_decode_graph\n");
	MLV_wait_mouse(0, 0);
	MLV_clear_window(MLV_COLOR_BLACK);
	draw_quadtree(qt, 0, TAILLE_X, 0, TAILLE_Y);
	MLV_actualise_window();
	MLV_wait_mouse(0, 0);
}
