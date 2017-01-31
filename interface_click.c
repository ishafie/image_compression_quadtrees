#include "includes/quadtree.h"
#include "includes/colorlist.h"
#include "includes/err.h"

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

void 		display_colorlist_otherway(t_clc *clc)
{
	t_cl	*tmp;

	if (!clc)
	{
		printf("vide\n");
		return ;
	}
	tmp = clc->last;
	while (tmp)
	{
		if ((*(tmp->qt)))
			printf("%d - ", (*(tmp->qt))->n_node);
		tmp = tmp->prev;
	}
	printf("\n");
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


void 		set_garbage(t_qt **qt, t_qt **g_c)
{
	unsigned int n;

	n = 0;
	if (!qt || !(*qt))
		return ;
	set_garbage(&(*qt)->no, g_c);
	set_garbage(&(*qt)->ne, g_c);
	set_garbage(&(*qt)->se, g_c);
	set_garbage(&(*qt)->so, g_c);
	n = (*qt)->n_node;
	(*qt)->deleted = 1;
	g_c[n] = *qt;
}

void 		delete_garbage_tree(t_qt **garbage_collector)
{
	int		i;
	t_qt	**tmp;

	tmp = NULL;
	i = (OP_MINI * 4);
	while (i)
	{
		if (garbage_collector[i])
			set_garbage(&garbage_collector[i], garbage_collector);
		i--;
	}
	i = (OP_MINI * 4);
	while (i)
	{
		if (garbage_collector[i])
		{
			if ((garbage_collector[i])->par && (garbage_collector[i])->par->no == garbage_collector[i])
				tmp = &(garbage_collector[i])->par->no;
			if ((garbage_collector[i])->par && (garbage_collector[i])->par->ne == garbage_collector[i])
				tmp = &(garbage_collector[i])->par->ne;
			if ((garbage_collector[i])->par && (garbage_collector[i])->par->se == garbage_collector[i])
				tmp = &(garbage_collector[i])->par->se;
			if ((garbage_collector[i])->par && (garbage_collector[i])->par->so == garbage_collector[i])
				tmp = &(garbage_collector[i])->par->so;
			/*free(garbage_collector[i]);*/
			garbage_collector[i] = NULL;
			if (tmp && *tmp)
				*tmp = NULL;
		}
		i--;
	}
}

/*void 		delete_garbage_tree(t_qt **qt, t_qt **g_c)
{
	unsigned int n;

	n = 0;
	if (!qt || !(*qt))
		return ;
	if ((*qt)->no)
		delete_garbage_tree(&(*qt)->no, g_c);
	if ((*qt)->ne)
		delete_garbage_tree(&(*qt)->ne, g_c);
	if ((*qt)->se)
		delete_garbage_tree(&(*qt)->se, g_c);
	if ((*qt)->so)
		delete_garbage_tree(&(*qt)->so, g_c);
	n = (*qt)->n_node;
	if ((*qt)->deleted == 1)
		return ;
	(*qt)->no = NULL;
	(*qt)->ne = NULL;
	(*qt)->se = NULL;
	(*qt)->so = NULL;
	(*qt)->par = NULL;
	(*qt)->deleted = 1;
	free(*qt);
	*qt = NULL;
	g_c[n] = NULL;
}*/

void 		click_interface(t_qt **qt, char *filename, MLV_Image *img)
{
	int		x;
	int		y;
	int		mini;
	t_ci	*ci;
	t_list	*l_dist;
	t_lc	*lc;
	t_qt	**garbage_collector;

	garbage_collector = NULL;
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
				garbage_collector = (t_qt**)malloc(sizeof(t_qt*) * (OP_MINI * 4 + 1));
				if (!garbage_collector)
					malloc_handling();
				ci = NULL;
				delete_tree(qt);
				l_dist = NULL;
				lc = create_list_container(l_dist);
				create_tree(0); /* reset du nombre de noeud */
				quadtree_maker2(&lc, img, qt, OP_MINI);
				printf("Debut minimisation\n");
				update_colorlist(&ci, qt);
				minimize2(&ci, &garbage_collector);
				delete_colorlist(&ci);
				MLV_clear_window(MLV_COLOR_BLACK);
				create_interface(*qt);
				delete_garbage_tree(garbage_collector);
				printf("Fin minimisation\n");
			}
			else
				printf("Minimisation impossible sur cet arbre.\n");
			mini = 1;
		}
		if (click_save_button_graph_color(x, y))
			hub_encode_graph(*qt, filename, COLOR);
		if (click_save_button_graph_bandw(x, y))
			hub_encode_graph(*qt, filename, NOCOLOR);
		if (click_open_img_button(x, y))
			open_img(qt, &filename, &mini, &img);
	}
}
