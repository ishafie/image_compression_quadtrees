#include "includes/quadtree.h"

void 		create_qtc(t_qt **qt, char **filename, char *text)
{
	FILE		*fp;

	free(*filename);
	*filename = text;
	delete_tree(qt);
	*qt = NULL;
	fp = fopen(text, "rb");
	if (!fp)
		err_what(FILE_ISSUE);
	decode_bin(qt, fp);
	fclose(fp);
}

void 		create_gmc(t_qt **qt, char **filename, char *text)
{
	free(*filename);
	*filename = text;
	delete_tree(qt);
	*qt = NULL;
	decodage(*filename, qt, COLOR);
}

void 		create_qtn(t_qt **qt, char **filename, char *text)
{
	FILE		*fp;

	free(*filename);
	*filename = text;
	delete_tree(qt);
	*qt = NULL;
	fp = fopen(text, "rb");
	if (!fp)
		err_what(FILE_ISSUE);
	decode_bin_nocolor(qt, fp);
	fclose(fp);
}

void 		create_gmn(t_qt **qt, char **filename, char *text)
{
	free(*filename);
	*filename = text;
	delete_tree(qt);
	*qt = NULL;
	decodage(*filename, qt, NOCOLOR);
}

void 		create_img(t_qt **qt, char **filename, char *text)
{
	t_list		*l;
	t_lc		*lc;
	MLV_Image	*img;

	free(*filename);
	*filename = text;
	delete_tree(qt);
	*qt = NULL;
	l = NULL;
	lc = create_list_container(l);
	img = MLV_load_image(text);
	quadtree_maker2(&lc, img, qt, OP);
	MLV_clear_window(MLV_COLOR_BLACK);
}

void 		open_img(t_qt **qt, char **filename, int *mini)
{
	char		*text;
	struct stat	sb;

	text = NULL;
	MLV_wait_input_box(TAILLE_X / 6, TAILLE_Y - TAILLE_Y / 3, TAILLE_X - TAILLE_X / 5, 100,
		MLV_COLOR_BLACK, MLV_COLOR_BLACK, MLV_COLOR_GREY,
		"Tapez le chemin de votre image : ", &text);
	if (stat(text, &sb) != -1)
	{
		*mini = 1;
		if (is_img(text))
		{
			*mini = 0;
			create_img(qt, filename, text);
		}
		else if (is_qtn(text))
			create_qtn(qt, filename, text);
		else if (is_gmn(text))
			create_gmn(qt, filename, text);
		else if (is_gmc(text))
			create_gmc(qt, filename, text);
		else if (is_qtc(text))
			create_qtc(qt, filename, text);
	}
	MLV_clear_window(MLV_COLOR_BLACK);
	create_interface(*qt);
}

void 		create_interface(t_qt *qt)
{
	MLV_Font *font;

	font = MLV_load_font("resources/panforte.ttf", 12);
	draw_quadtree(qt, 0, TAILLE_X, 0, TAILLE_Y);
	draw_interface(font);
	MLV_actualise_window();
}
