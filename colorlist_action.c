#include "includes/colorlist.h"

int			count_color(t_ci *c)
{
	t_ci	*tmp;
	int		i;

	i = 0;
	tmp = c;
	while (tmp)
	{
		count_color_line(tmp->index);
		i++;
		tmp = tmp->next;
	}
	return (i);
}

int			count_color_line(t_clc *c)
{
	int		i;
	t_cl	*tmp;

	i= 0;
	if (!c || !c || !c->first)
		return (0);
	tmp = c->first;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

t_ci		*check_colorindex(t_ci **ci, t_qt **qt)
{
	t_ci	*tmp;
	t_qt	**qtmp;

	if (!ci || !*ci || !(*ci)->index || !qt || !*qt)
		return (NULL);
	tmp = *ci;
	while (tmp)
	{
		if (tmp->index && tmp->index->first && tmp->index->first->qt)
		{
			qtmp = tmp->index->first->qt;
			if (qtmp && *qtmp && color_equal((*qtmp)->color, (*qt)->color, 10))
				return (tmp);
		}
		tmp = tmp->next;
	}
	return (NULL);
}

void 		update_colorlist(t_ci **ci, t_qt **qt)
{
	t_ci	*tmpci;

	if (!qt || !*qt)
		return ;
	if ((tmpci = check_colorindex(ci, qt)))
		addback_colorlist(&(tmpci->index), qt);
	else
		addfront_colorindex(ci, qt);
	update_colorlist(ci, &(*qt)->no);
	update_colorlist(ci, &(*qt)->ne);
	update_colorlist(ci, &(*qt)->se);
	update_colorlist(ci, &(*qt)->so);
}
