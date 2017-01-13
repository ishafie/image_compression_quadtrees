#include "includes/colorlist.h"

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

void 		display_colorlist(t_clc *clc)
{
	t_cl	*tmp;

	if (!clc)
	{
		printf("vide\n");
		return ;
	}
	tmp = clc->first;
	while (tmp)
	{
		if ((*(tmp->qt)))
			printf("%d - ", (*(tmp->qt))->n_node);
		tmp = tmp->next;
	}
	printf("\n");
}

void 		test_colorlist(t_ci *ci)
{
	t_ci	*tmp;
	t_cl	*tl;
	int		i;

	i = 0;
	tmp = ci;
	while (tmp && i < 30)
	{
		tmp = tmp->next;
		i++;
	}
	tl = tmp->index->last;
	display_colorlist(tmp->index);

	MLV_wait_mouse(0, 0);
	while (tl)
	{
		if (tl && tl->deleted != 1 && tl->qt && (*(tl->qt))
			&& (*(tl->qt))->n_node)
			printf("node : %d\n", (*(tl->qt))->n_node);
		tl = delete_any_colorlist(&(tmp->index), tl);
		MLV_wait_mouse(0, 0);
	}
}

void 		click_interface(t_qt **qt, char *filename)
{
	int		x;
	int		y;
	int		mini;
	t_ci	*ci;

	ci = NULL;
	mini = 0;
	while (42 && qt)
	{
		ci = NULL;
		MLV_wait_mouse(&x, &y);
		if (click_save_button_bin_color(x, y))
			encode_bin(*qt, filename, COLOR);
		if (click_save_button_bin_bandw(x, y))
			encode_bin(*qt, filename, NOCOLOR);
		if (click_mini_button(x, y))
		{
			if (mini == 0)
			{
				ci = NULL;
				/*analyze_minimize_and_draw(qt);*/
				printf("Debut minimisation\n");
				update_colorlist(&ci, qt);
				/*test_colorlist(ci);*/
				minimize2(&ci);
				printf("pret ?\n");
				MLV_wait_mouse(0, 0);
				printf("lets go !\n");
				MLV_clear_window(MLV_COLOR_BLACK);
				draw_quadtree(*qt, 0, TAILLE_X, 0, TAILLE_Y);
				MLV_actualise_window();
				printf("Fin minimisation\n");
			}
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
