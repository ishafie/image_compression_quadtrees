#include "includes/quadtree.h"

double		dist(t_color px, t_color moy)
{
	double powr;
	double powg;
	double powb;
	double powa;

	powr = (px.red - moy.red) * (px.red - moy.red);
	powg = (px.green - moy.green) * (px.green - moy.green);
	powb = (px.blue - moy.blue) * (px.blue - moy.blue);
	powa = (px.alpha - moy.alpha) * (px.alpha - moy.alpha);
	return (sqrt(powr + powg + powb + powa));
}

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
	}
	if ((*b)->so && (*a)->so)
	{
		MLV_Color_to_color((*a)->so->color, &x_a);
		MLV_Color_to_color((*b)->so->color, &x_b);
		ret += dist(x_a, x_b) / 4;
	}
	return (ret);
}

int		is_no_leaf(t_qt *a)
{
	if (!a)
		return (0);
	if (!is_leaf(a->no) || !is_leaf(a->ne) || !is_leaf(a->se) || !is_leaf(a->so))
		return (1);
	return (0);
}

double	get_dist_final(t_qt **a, t_qt **b)
{
	/*if (!is_no_leaf(*a) || !is_no_leaf(*b))
		return (10000);*/
	if (is_leaf(*a) && is_leaf(*b))
		return (get_dist((*a)->color, (*b)->color));
	else if (is_leaf(*a) && !is_leaf(*b))
		return (get_4_dist_color(b, (*a)->color));
	else if (is_leaf(*b) && !is_leaf(*a))
		return (get_4_dist_color(a, (*b)->color));
	return (get_4_dist(a, b));
}

double	distance_leaf_and_inner_tree(MLV_Color color, t_qt **a)
{
	double	ret;
	t_color	x;
	t_color	y;

	ret = 0;
	if (*a && (*a)->no)
	{
		MLV_Color_to_color((*a)->no->color, &x);
		MLV_Color_to_color(color, &y);
		ret += dist(y, x) / 4;
	}
	if (*a && (*a)->ne)
	{
		MLV_Color_to_color((*a)->ne->color, &x);
		MLV_Color_to_color(color, &y);
		ret += dist(y, x) / 4;
	}
	if (*a && (*a)->se)
	{
		MLV_Color_to_color((*a)->se->color, &x);
		MLV_Color_to_color(color, &y);
		ret += dist(y, x) / 4;
	}
	if (*a && (*a)->so)
	{
		MLV_Color_to_color((*a)->so->color, &x);
		MLV_Color_to_color(color, &y);
		ret += dist(y, x) / 4;
	}
	return (ret);
}

double	distance_two_inner_tree(t_qt **a, t_qt **b)
{
	t_color	x_a;
	t_color	x_b;

	if (!*a || !*b)
		return (0);
	if (*a && *b && is_leaf(*a) && is_leaf(*b))
	{
		MLV_Color_to_color((*a)->color, &x_a);
		MLV_Color_to_color((*b)->color, &x_b);
		return (dist(x_a, x_b));
	}
	else if (*b && *a && is_leaf(*a))
	{
		return (distance_leaf_and_inner_tree((*a)->color, b)
		+ distance_two_inner_tree(a, &(*b)->no)
		+ distance_two_inner_tree(a, &(*b)->ne)
		+ distance_two_inner_tree(a, &(*b)->se)
		+ distance_two_inner_tree(a, &(*b)->so));
	}
	else if (*a && *b && is_leaf(*b))
	{
		return (distance_leaf_and_inner_tree((*b)->color, a)
		+ distance_two_inner_tree(&(*a)->no, b)
		+ distance_two_inner_tree(&(*a)->ne, b)
		+ distance_two_inner_tree(&(*a)->se, b)
		+ distance_two_inner_tree(&(*a)->so, b));
	}
	return (distance_two_inner_tree(&(*a)->no, &(*b)->no)
	+ distance_two_inner_tree(&(*a)->ne, &(*b)->ne)
	+ distance_two_inner_tree(&(*a)->se, &(*b)->se)
	+ distance_two_inner_tree(&(*a)->so, &(*b)->so));
}
