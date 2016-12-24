#include "includes/quadtree.h"

int 		click_save_button_bin_color(int x, int y)
{
	if (x > 0 && x < TAILLE_X / 8 && y > 0 && y < TAILLE_Y / 9 + 30)
		return (1);
	return (0);
}

int 		click_save_button_bin_bandw(int x, int y)
{
	if (x > TAILLE_X / 7 && x < TAILLE_X / 7 + TAILLE_X / 8
		&& y > 0 && y < TAILLE_Y / 9 + 30)
		return (1);
	return (0);
}

int 		click_save_button_graph_color(int x, int y)
{
	if (x > TAILLE_X - TAILLE_X / 7 && x < TAILLE_X
		&& y > 0 && y < TAILLE_Y / 9 + 30)
		return (1);
	return (0);
}

int 		click_save_button_graph_bandw(int x, int y)
{
	if (x > TAILLE_X - (TAILLE_X / 7 + 7) * 2 && x < TAILLE_X - (TAILLE_X / 7) * 2 + TAILLE_X / 8
		&& y > 0 && y < TAILLE_Y / 9 + 30)
		return (1);
	return (0);
}

int 		click_mini_button(int x, int y)
{
	if (x > 0 && x < TAILLE_X / 8
		&& y > TAILLE_Y - TAILLE_Y / 9 - 20 && y < TAILLE_Y)
		return (1);
	return (0);
}

int 		click_open_img_button(int x, int y)
{
	if (x > TAILLE_X - TAILLE_X / 7 && x < TAILLE_X
		&& y > TAILLE_Y - TAILLE_Y / 9 - 20 && y < TAILLE_Y)
		return (1);
	return (0);
}

void 		click_interface(t_qt **qt, char *filename)
{
	int		x;
	int		y;
	int		mini;

	mini = 0;
	while (42 && qt)
	{
		MLV_wait_mouse(&x, &y);
		if (click_save_button_bin_color(x, y))
			encode_bin(*qt, filename, COLOR);
		if (click_save_button_bin_bandw(x, y))
			encode_bin(*qt, filename, NOCOLOR);
		if (click_mini_button(x, y))
		{
			if (mini == 0)
				analyze_and_minimize(qt);
			else
				printf("Minimisation impossible sur cet arbre.\n");
			mini = 1;
		}
		if (click_save_button_graph_color(x, y))
			encodage_graph(*qt, filename, COLOR);
		if (click_save_button_graph_bandw(x, y))
			encodage_graph(*qt, filename, NOCOLOR);
		if (click_open_img_button(x, y))
			open_img(qt, &filename, &mini);
	}
}
