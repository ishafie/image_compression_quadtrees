#include "includes/quadtree.h"

/* ------------------------------------------------------------------ */
/*
 * Idée non fonctionnelle. (non terminée et ne marcherait que si toutes
 * les feuilles étaient à la meme hauteur.
 */
int		get_prof(t_qt *qt, int prof)
{
	if (!qt)
		return (prof);
	return max(
			max(get_prof(qt->no, prof + 1), get_prof(qt->ne, prof + 1)),
			max(get_prof(qt->se, prof + 1), get_prof(qt->so, prof + 1)));
}

int		determine_prof(int nb_color)
{
	int	pow;
	int nb;
	
	nb = 1;
	pow = 0;
	while (nb < nb_color)
	{
		nb *= 4;
		pow++;
	}
	return (pow);
}

void	link_node_to_prof(t_qt **qt, int prof)
{
	t_qt	*new_node;
	
	if (prof == 0)
		return ;
	new_node = create_tree();
	(*qt)->no = new_node;
	(*qt)->ne = new_node;
	(*qt)->se = new_node;
	(*qt)->so = new_node;
	link_node_to_prof(&(*qt)->no, prof - 1);
	link_node_to_prof(&(*qt)->ne, prof - 1);
	link_node_to_prof(&(*qt)->se, prof - 1);
	link_node_to_prof(&(*qt)->so, prof - 1);
}

void	minimise_prof(t_qt **qt, int nb_color, int max_prof)
{
	int	prof;
	
	prof = determine_prof(nb_color);
	printf("%d\n", prof);
	link_node_to_prof(qt, max_prof - prof);
}
/* ------------------------------------------------------------------ */

int		is_leaf(t_qt *qt)
{
	if (!(qt) || (!qt->no && !qt->ne && !qt->se && !qt->so))
		return (1);
	return (0);
}

void	check_every_color_doublon(t_qt **qt, t_qt **tmp, int *nb_color)
{
	if (!tmp || !*tmp)
		return ;
	if (is_leaf(*tmp))
	{
		*nb_color += 1;
		print_every_color_equal(qt, tmp, (*tmp)->color, nb_color);
	}
	check_every_color_doublon(qt, &((*tmp)->no), nb_color);
	check_every_color_doublon(qt, &((*tmp)->ne), nb_color);
	check_every_color_doublon(qt, &((*tmp)->se), nb_color);
	check_every_color_doublon(qt, &((*tmp)->so), nb_color);
}

int		count_node(t_qt *qt)
{
	if (!qt)
		return (0);
	return (1 + count_node(qt->no) + count_node(qt->ne) + count_node(qt->se) + count_node(qt->so));
}

void	free_tree(t_qt **qt)
{
	if (!*qt)
		return ;
	free_tree(&(*qt)->no);
	free_tree(&(*qt)->ne);
	free_tree(&(*qt)->se);
	free_tree(&(*qt)->so);
	if (*qt)
		free(*qt);
	*qt = NULL;
}

void	delete_pair_tree_and_relink(MLV_Image *img, t_qt **relink, t_qt **paire)
{
	if (!*paire || !*relink || *paire == *relink)
	{
		printf("Echec\n");
		return ;
	}
	(void)img;
	/*MLV_clear_window(MLV_COLOR_BLACK);
	draw_quadtree(*paire, img, 0, TAILLE_X, 0, TAILLE_Y);
	MLV_actualise_window();
	MLV_wait_mouse(0, 0);
	
	MLV_clear_window(MLV_COLOR_BLACK);
	draw_quadtree(*relink, img, 0, TAILLE_X, 0, TAILLE_Y);
	MLV_actualise_window();
	MLV_wait_mouse(0, 0);
	MLV_clear_window(MLV_COLOR_BLACK);
	draw_quadtree(g_test, img, 0, TAILLE_X, 0, TAILLE_Y);
	MLV_actualise_window();
	*/
	free_tree(paire);
	(*paire) = (*relink);
}

int		min(int a, int b)
{
	return (a < b ? a : b);
}

void	print_colordiff(t_qt *a, t_qt *racine)
{
	if (!racine)
		return ;
	if (a && a->no)
		printf("colordiff NO = %d\n", color_diff(a->no->color, racine->color));
	if (a && a->ne)
		printf("colordiff NE = %d\n", color_diff(a->ne->color, racine->color));
	if (a && a->se)
		printf("colordiff SE = %d\n", color_diff(a->se->color, racine->color));
	if (a && a->so)
		printf("colordiff SO = %d\n", color_diff(a->so->color, racine->color));
		
}

void	go_to_low_colordiff(MLV_Image *img, t_qt **racine, t_qt **qt)
{
	print_colordiff(*qt, *racine);
	if (*racine && *qt && (*qt)->no && (*qt)->no != *racine && color_diff((*qt)->no->color, (*racine)->color) < 45)
	{
		printf("PAIRE NO\n");
		minimise_perte_hub(img, racine, &((*qt)->no));
	}
	if (*racine && *qt && (*qt)->ne && (*qt)->ne != *racine && color_diff((*qt)->ne->color, (*racine)->color) < 45)
	{
		printf("PAIRE NE\n");
		minimise_perte_hub(img, racine, &((*qt)->ne));
	}
	if (*racine && *qt && (*qt)->se && (*qt)->se != *racine && color_diff((*qt)->se->color, (*racine)->color) < 45)
	{
		printf("PAIRE SE\n");
		minimise_perte_hub(img, racine, &((*qt)->se));
	}
	if (*racine && *qt && (*qt)->so && (*qt)->so != *racine && color_diff((*qt)->so->color, (*racine)->color) < 45)
	{
		printf("PAIRE SO\n");
		minimise_perte_hub(img, racine, &((*qt)->so));
	}
}

int		is_part_of(t_qt *a, t_qt *b)
{
	if (!a)
		return (0);
	if (a == b)
		return (1);
	return (is_part_of(a->no, b) + is_part_of(a->ne, b) + is_part_of(a->se, b) + is_part_of(a->so, b));
}

void	check_dist_and_relink(MLV_Image *img, t_qt **racine, t_qt **qt, double dist)
{
	if (dist >= 30 || is_part_of(*qt, *racine) || is_part_of(*racine, *qt))
		return ;
	delete_pair_tree_and_relink(img, racine, qt);
}

void	minimise_perte_hub(MLV_Image *img, t_qt **racine, t_qt **qt)
{
	double dist;
	
	dist = 0;
	if (!*racine || *qt == *racine || !*qt)
		return ;
	printf("HERE : ");
	if (color_equal((*qt)->color, (*racine)->color, 20))
	{
		dist = get_dist_final(racine, qt);
		printf("dist = %f\n", dist);
		MLV_actualise_window();
		check_dist_and_relink(img, racine, qt, dist);
		if (dist < 30)
		{
			MLV_wait_mouse(0, 0);
			MLV_clear_window(MLV_COLOR_BLACK);
			draw_quadtree(g_test, img, 0, TAILLE_X, 0, TAILLE_Y);
			MLV_actualise_window();
		}
	}
	go_to_low_colordiff(img, racine, qt);
}

void	minimise_perte(MLV_Image *img, t_qt **racine, t_qt **qt)
{
	if (!*racine)
		return ;
	minimise_perte_hub(img, racine, qt);
	printf("RACINE NO\n");
	minimise_perte(img, &((*racine)->no), qt);
	printf("RACINE NE\n");
	minimise_perte(img, &((*racine)->ne), qt);
	printf("RACINE SE\n");
	minimise_perte(img, &((*racine)->se), qt);
	printf("RACINE SO\n");
	minimise_perte(img, &((*racine)->so), qt);
}
