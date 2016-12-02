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

int		main(void)
{
	t_qt	*qt;
	MLV_Image *img;
	int		nb_color;
	
	nb_color = 0;
	qt = NULL;
	MLV_create_window("QUADTREE", "QUADTREE", TAILLE_X, TAILLE_Y);
	img = MLV_load_image("img/lion.png");
	quadtree_maker(img, &qt, OP);
	check_every_color_doublon(&qt, &qt, &nb_color);
	/*printf("nb of colors = %d\n", nb_color);*/
	draw_quadtree(qt, img, 0, TAILLE_X, 0, TAILLE_Y);
	MLV_actualise_window();
	g_test = qt;
	minimise_perte(img, &qt, &qt);
	MLV_actualise_window();
	MLV_wait_mouse(0, 0);

	/*test_color();
	MLV_actualise_window();
	MLV_wait_mouse(0, 0);*/
	return (0);
}
