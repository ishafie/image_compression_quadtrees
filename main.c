#include "includes/quadtree.h"

int	main(void)
{
	MLV_Image *test;
	MLV_Color ret;
	
	MLV_create_window("QUADTREE", "QUADTREE", TAILLE_X, TAILLE_Y);
	test = MLV_load_image("img/lion.png");
	ret = get_average_color_from_image(test, 0, TAILLE_X, 0, TAILLE_Y);
	MLV_draw_filled_rectangle(0, 0, TAILLE_X, TAILLE_Y, ret);
	MLV_actualise_window();
	MLV_wait_mouse(0, 0);
	return (0);
}
