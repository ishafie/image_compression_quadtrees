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

void		test_decode_encode(MLV_Image *img, t_qt *qt)
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
	draw_quadtree(qt, img, 0, TAILLE_X, 0, TAILLE_Y);
	MLV_actualise_window();
	MLV_wait_mouse(0, 0);
	MLV_clear_window(MLV_COLOR_BLACK);
	MLV_actualise_window();
	draw_quadtree(tree, img, 0, TAILLE_X, 0, TAILLE_Y);
	MLV_actualise_window();
	MLV_wait_mouse(0, 0);
	write_in_file("lion", buf, len);
}

int		main(void)
{
	t_qt	*qt;
	MLV_Image *img;

	/*int		nb_color;

	nb_color = 0;*/
	qt = NULL;
	MLV_create_window("QUADTREE", "QUADTREE", TAILLE_X, TAILLE_Y);
	img = MLV_load_image("img/lion.png");
	quadtree_maker(img, &qt, OP);
	/*check_every_color_doublon(&qt, &qt, &nb_color);*/
	/*printf("nb of colors = %d\n", nb_color);*/
	g_test = qt;

	return (0);
	minimise_perte(img, &(qt->no), &(qt->ne));
	minimise_perte(img, &(qt->no), &(qt->se));
	minimise_perte(img, &(qt->no), &(qt->so));

	minimise_perte(img, &(qt->ne), &(qt->no));
	minimise_perte(img, &(qt->ne), &(qt->se));
	minimise_perte(img, &(qt->ne), &(qt->so));

	minimise_perte(img, &(qt->se), &(qt->no));
	minimise_perte(img, &(qt->se), &(qt->ne));
	minimise_perte(img, &(qt->se), &(qt->so));

	minimise_perte(img, &(qt->so), &(qt->no));
	minimise_perte(img, &(qt->so), &(qt->ne));
	minimise_perte(img, &(qt->so), &(qt->se));

	MLV_wait_mouse(0, 0);
	MLV_clear_window(MLV_COLOR_BLACK);
	draw_quadtree(qt, img, 0, TAILLE_X, 0, TAILLE_Y);
	MLV_actualise_window();
	printf("fin\n");
	MLV_wait_mouse(0, 0);
	/*test_color();
	MLV_actualise_window();
	MLV_wait_mouse(0, 0);*/
	MLV_free_window();
	return (0);
}
