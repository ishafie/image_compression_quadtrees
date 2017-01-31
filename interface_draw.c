#include "includes/quadtree.h"
#include "includes/err.h"

void 		draw_save_button_bin_color(MLV_Font *font) /* from 0 to taille_x / 8 */
{
	MLV_Image	*img;

	if ((img = MLV_load_image("resources/save_color.png")) == NULL)
		err_what(IMG_NOT_FOUND);
	MLV_draw_image(img, 7, 0);
	MLV_draw_text_box_with_font(0, TAILLE_Y / 9, TAILLE_X / 8, 30,
		"Save as bin\nin color", font, 1, MLV_COLOR_WHITE, MLV_COLOR_BLACK, MLV_COLOR_WHITE,
		MLV_TEXT_CENTER, MLV_HORIZONTAL_CENTER, MLV_VERTICAL_CENTER);
}

void 		draw_save_button_bin_bandw(MLV_Font *font)
{
	MLV_Image	*img;

	if ((img = MLV_load_image("resources/save_bn.png")) == NULL)
		err_what(IMG_NOT_FOUND);
	MLV_draw_image(img, TAILLE_X / 7, 0);
	MLV_draw_text_box_with_font(TAILLE_X / 7 - 7, TAILLE_Y / 9, TAILLE_X / 8, 30,
		"Save as bin\nin b & w", font, 1, MLV_COLOR_WHITE, MLV_COLOR_BLACK, MLV_COLOR_WHITE,
		MLV_TEXT_CENTER, MLV_HORIZONTAL_CENTER, MLV_VERTICAL_CENTER);
}

void 		draw_save_button_graph_color(MLV_Font *font)
{
	MLV_Image	*img;

	if ((img = MLV_load_image("resources/save_color.png")) == NULL)
		err_what(IMG_NOT_FOUND);
	MLV_draw_image(img, TAILLE_X - TAILLE_X / 7, 0);
	MLV_draw_text_box_with_font(TAILLE_X - TAILLE_X / 7 - 7, TAILLE_Y / 9, TAILLE_X / 8, 30,
		"Save as graph\nin color", font, 1, MLV_COLOR_WHITE, MLV_COLOR_BLACK, MLV_COLOR_WHITE,
		MLV_TEXT_CENTER, MLV_HORIZONTAL_CENTER, MLV_VERTICAL_CENTER);
}

void 		draw_save_button_graph_bandw(MLV_Font *font)
{
	MLV_Image	*img;

	if ((img = MLV_load_image("resources/save_bn.png")) == NULL)
		err_what(IMG_NOT_FOUND);
	MLV_draw_image(img, TAILLE_X - (TAILLE_X / 7) * 2 - 7, 0);
	MLV_draw_text_box_with_font(TAILLE_X - (TAILLE_X / 7 + 7) * 2, TAILLE_Y / 9, TAILLE_X / 8, 30,
		"Save as graph\nin b & w", font, 1, MLV_COLOR_WHITE, MLV_COLOR_BLACK, MLV_COLOR_WHITE,
		MLV_TEXT_CENTER, MLV_HORIZONTAL_CENTER, MLV_VERTICAL_CENTER);
}

void 		draw_mini_button(MLV_Font *font)
{
	MLV_Image	*img;

	if ((img = MLV_load_image("resources/mini.png")) == NULL)
		err_what(IMG_NOT_FOUND);
	MLV_draw_image(img, 5, TAILLE_Y - TAILLE_Y / 9 - 20);
	MLV_draw_text_box_with_font(0, TAILLE_Y - 20, TAILLE_X / 8, 20,
		"Minimiser", font, 1, MLV_COLOR_WHITE, MLV_COLOR_BLACK, MLV_COLOR_WHITE,
		MLV_TEXT_CENTER, MLV_HORIZONTAL_CENTER, MLV_VERTICAL_CENTER);
}

void 		draw_open_img_button(MLV_Font *font)
{
	MLV_Image	*img;

	if ((img = MLV_load_image("resources/open.png")) == NULL)
		err_what(IMG_NOT_FOUND);
	MLV_draw_image(img, TAILLE_X - TAILLE_X / 7 + 5, TAILLE_Y - TAILLE_Y / 9 - 20);
	MLV_draw_text_box_with_font(TAILLE_X - TAILLE_X / 7, TAILLE_Y - 20, TAILLE_X / 8, 20,
		"Open img", font, 1, MLV_COLOR_WHITE, MLV_COLOR_BLACK, MLV_COLOR_WHITE,
		MLV_TEXT_CENTER, MLV_HORIZONTAL_CENTER, MLV_VERTICAL_CENTER);
}

void 		draw_interface(MLV_Font *font)
{
	draw_save_button_bin_color(font);
	draw_save_button_bin_bandw(font);
	draw_mini_button(font);
	draw_save_button_graph_color(font);
	draw_save_button_graph_bandw(font);
	draw_open_img_button(font);
}
