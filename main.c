#include "includes/quadtree.h"

int		main(void)
{
	t_qt				*qt;
	t_lc				*lc;
	t_list				*l_dist;
	MLV_Image 			*img;
	char				*filename;

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
	click_interface(&qt, filename, img);
	/*analyze_and_minimize(&qt);
	encodage(qt, "lion");*/
	printf("Fin.\n");
	MLV_wait_mouse(0, 0);
	free(filename);
	MLV_free_window();
	return (0);
}
