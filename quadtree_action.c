#include "includes/quadtree.h"

int		is_leaf(t_qt *qt)
{
	if (!(qt) || (!qt->no && !qt->ne && !qt->se && !qt->so))
		return (1);
	return (0);
}
