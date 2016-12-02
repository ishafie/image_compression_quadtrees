#include "includes/quadtree.h"

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
	}
	return (ret);
}

int		is_no_leaf(t_qt *a)
{
	if (!a)
		return (0);
	return (1 + is_no_leaf(a->no) + is_no_leaf(a->ne) + is_no_leaf(a->se) + is_no_leaf(a->so));
}

double	get_dist_final(t_qt **a, t_qt **b)
{
	if (is_no_leaf(*a) > 1 || is_no_leaf(*b) > 1)
		return (10000);
	if (is_leaf(*a) && is_leaf(*b))
		return (get_dist((*a)->color, (*b)->color));
	else if (is_leaf(*a) && !is_leaf(*b))
		return (get_4_dist_color(b, (*a)->color));
	else if (is_leaf(*b) && !is_leaf(*a))
		return (get_4_dist_color(a, (*b)->color));
	return (get_4_dist(a, b));
}
