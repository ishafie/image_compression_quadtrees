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

double	get_dist(MLV_Color x, MLV_Color y)
{
	t_color x_c;
	t_color y_c;
	
	MLV_Color_to_color(x, &x_c);
	MLV_Color_to_color(y, &y_c);
	return (dist(x_c, y_c));
}

double		get_4_dist_color(t_qt **b, MLV_Color b_c)
{
	double	ret;
	t_color	x;
	t_color	y;
	
	ret = 0;
	if ((*b)->no)
	{
		MLV_Color_to_color((*b)->no->color, &x);
		MLV_Color_to_color(b_c, &y);
		ret += dist(y, x) / 4;
	}
	if ((*b)->ne)
	{
		MLV_Color_to_color((*b)->ne->color, &x);
		MLV_Color_to_color(b_c, &y);
		ret += dist(y, x) / 4;
	}
	if ((*b)->se)
	{
		MLV_Color_to_color((*b)->se->color, &x);
		MLV_Color_to_color(b_c, &y);
		ret += dist(y, x) / 4;
	}
	if ((*b)->so)
	{
		MLV_Color_to_color((*b)->so->color, &x);
		MLV_Color_to_color(b_c, &y);
		ret += dist(y, x) / 4;
	}
	return (ret);
}

double		get_4_dist(t_qt **a, t_qt **b)
{
	double	ret;
	t_color	x_a;
	t_color	x_b;
	
	ret = 0;
	if ((*b)->no && (*a)->no)
	{
		MLV_Color_to_color((*a)->no->color, &x_a);
		MLV_Color_to_color((*b)->no->color, &x_b);
		ret += dist(x_a, x_b) / 4;
	}
	if ((*b)->ne && (*a)->ne)
	{
		MLV_Color_to_color((*a)->ne->color, &x_a);
		MLV_Color_to_color((*b)->ne->color, &x_b);
		ret += dist(x_a, x_b) / 4;
	}
	if ((*b)->se && (*a)->se)
	{
		MLV_Color_to_color((*a)->se->color, &x_a);
		MLV_Color_to_color((*b)->se->color, &x_b);
		ret += dist(x_a, x_b) / 4;
	}	if ((*b)->so && (*a)->so)
	{
		MLV_Color_to_color((*a)->so->color, &x_a);
		MLV_Color_to_color((*b)->so->color, &x_b);
		ret += dist(x_a, x_b) / 4;
	}	return (ret);
}

double	get_dist_final(t_qt **a, t_qt **b)
{
	if (is_leaf(*a) && is_leaf(*b))
		return (get_dist((*a)->color, (*b)->color));
	else if (is_leaf(*a) && !is_leaf(*b))
		return (get_4_dist_color(b, (*a)->color));
	else if (is_leaf(*b) && !is_leaf(*a))
		return (get_4_dist_color(a, (*b)->color));
	return (get_4_dist(a, b));
}

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

void	find_tree_min_dist(t_qt **qt, t_qt **paire)
{
	if (!*qt || !*paire)
		return ;
	if (*qt != *paire && color_equal((*qt)->color, (*paire)->color, 10))
	{
		printf("go in, maybe sous arbre !\n");
	}
	else if (*qt != *paire && !color_equal((*qt)->color, (*paire)->color, 30))
		return ;
	find_tree_min_dist(qt, &((*paire)->no));
	find_tree_min_dist(qt, &((*paire)->ne));
	find_tree_min_dist(qt, &((*paire)->se));
	find_tree_min_dist(qt, &((*paire)->so));
}

void	minimise_perte(t_qt **racine, t_qt **qt)
{
	if (!*racine)
		return ;
	find_tree_min_dist(racine, qt);
	minimise_perte(&(*racine)->no, qt);
	minimise_perte(&(*racine)->ne, qt);
	minimise_perte(&(*racine)->se, qt);
	minimise_perte(&(*racine)->so, qt);
}
