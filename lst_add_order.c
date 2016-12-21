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
		new->prev = NULL;
		fill_zone(&(new->zone), zone.x1, zone.x2, zone.y1, zone.y2);
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
	(*l)->prev = NULL;
	if ((*l)->next)
		(*l)->next->prev = (*l);
	return (1);
}

int add_end_recur(t_list **l, t_qt *ptr, double dist, t_zone zone)
{
	t_list	*tmp;

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
	while (tmp->prev != NULL)
	{
		if (tmp->prev->dist >= dist)
		{
			if (!(save = ft_lstnew(ptr, dist, zone)))
				return (-1);
			save->next = tmp;
			save->prev = tmp->prev;
			save->prev->next = save;
			tmp->prev = save;
			tmp->prev->next = tmp;
			return (1);
		}
		g_nb_op_creation++;
		tmp = tmp->prev;
	}
	return (1);
}

/*int add_order(t_list **l, t_qt *ptr, double dist, t_zone zone)
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
}*/
int add_order(t_list **l, t_list **last, t_qt *ptr, double dist, t_zone zone)
{
	t_list	*prev;

	if (*l == NULL)
	{
		*l = ft_lstnew(ptr, dist, zone);
		*last = *l;
		(*last)->prev = NULL;
		(*l)->prev = NULL;
	}
	else if (dist >= (*l)->dist)
		return (add_front_recur(l, ptr, dist, zone));
	else if (*last && dist <= (*last)->dist)
	{
		add_end_recur(last, ptr, dist, zone);
		prev = *last;
		*last = (*last)->next;
		(*last)->prev = prev;
	}
	else
	{
		add_order_any_recur(last, ptr, dist, zone);
	}
	return (1);
}

void	display_list(t_list *l, t_list *last)
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
		if (tmp->prev)
		{
			printf("\tprev = %f\n", tmp->prev->dist);
		}
		tmp = tmp->next;
		i++;
	}
	if (last)
	{
		printf("Last = %f\n", last->dist);
		if (last->prev)
			printf("Last prev = %f\n", last->prev->dist);
	}
	printf("Nombre de deplacements dans la liste : %d\n", g_nb_op_creation);
}
