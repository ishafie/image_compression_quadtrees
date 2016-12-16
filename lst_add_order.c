#include "includes/quadtree.h"

t_list	*ft_lstnew(t_qt *ptr, double dist, t_zone zone)
{
	t_list	*new;

	new = (t_list*)malloc(sizeof(t_list));
	if (new)
	{
		new->ptr = ptr;
		new->dist = dist;
		new->next = NULL;
		fill_zone(&(new->zone), zone.x1, zone.x2, zone.y1, zone.y2);
		new->processed = 0;
		return (new);
	}
	return (NULL);
}

int		ft_lstadd_back(t_list **lst, t_qt *ptr, double dist, t_zone zone)
{
	t_list	*tmp;
	t_list	*elem;

	if ((*lst) == NULL)
	{
		if (!((*lst) = ft_lstnew(ptr, dist, zone)))
			return (-1);
		return (1);
	}
	tmp = (*lst);
	while (tmp->next != NULL)
		tmp = tmp->next;
	if (!(elem = ft_lstnew(ptr, dist, zone)))
		return (-1);
	tmp->next = elem;
	return (1);
}

int add_front_recur(t_list **l, t_qt *ptr, double dist, t_zone zone)
{
	t_list *tmp;

	tmp = NULL;
	if (!((tmp) = ft_lstnew(ptr, dist, zone)))
		return (-1);
	tmp->next = *l;
	*l = tmp;
	return (1);
}

int add_end_recur(t_list **l, t_qt *ptr, double dist, t_zone zone)
{
	t_list *tmp;

	tmp = NULL;
	if (!(tmp = ft_lstnew(ptr, dist, zone)))
		return (-1);
	(*l)->next = tmp;
	return (1);
}

int	add_order_any_recur(t_list **l, t_qt *ptr, double dist, t_zone zone)
{
	t_list *tmp;
	t_list *save;

	save = NULL;
	tmp = *l;
	while (tmp->next != NULL)
	{
		if (tmp->next->dist <= dist)
		{
			if (!(save = ft_lstnew(ptr, dist, zone)))
				return (-1);
			save->next = tmp->next;
			tmp->next = save;
			return (1);
		}
		tmp = tmp->next;
	}
	if (tmp->dist >= dist)
	{
		return (add_end_recur(&tmp, ptr, dist, zone));
	}
	return (1);
}

int add_order(t_list **l, t_qt *ptr, double dist, t_zone zone)
{
	if (*l == NULL)
	{
		return (ft_lstadd_back(l, ptr, dist, zone));
	}
	if (dist >= (*l)->dist)
		return (add_front_recur(l, ptr, dist, zone));
	if (add_order_any_recur(l, ptr, dist, zone) == -1)
		return (-1);
	return (1);
}

void	display_list(t_list *l)
{
	t_list *tmp;
	int		i;
	
	i = 0;
	tmp = l;
	if (!tmp)
		return ;
	while (tmp)
	{
		printf("%f\n", tmp->dist);
		tmp = tmp->next;
		i++;
	}
}
