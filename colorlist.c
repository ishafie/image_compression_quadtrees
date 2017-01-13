#include "includes/colorlist.h"

t_cl			*create_colorlist(t_qt **qt, t_clc **c)
{
	t_cl		*newcl;

	newcl = (t_cl*)malloc(sizeof(t_cl));
	if (!newcl)
		malloc_handling();
	newcl->qt = qt;
	newcl->deleted = 0;
	newcl->next = NULL;
	newcl->prev = NULL;
	newcl->container = *c;
	if (qt && *qt)
		(*qt)->cl = newcl;
	return (newcl);
}

t_clc			*create_colorlist_container(t_qt **qt)
{
	t_clc		*newclc;

	newclc = (t_clc*)malloc(sizeof(t_clc));
	if (!newclc)
		malloc_handling();
	newclc->first = create_colorlist(qt, &newclc);
	newclc->last = newclc->first;
	return (newclc);
}

t_ci			*create_colorlist_index(t_qt **qt)
{
	t_ci		*newci;

	newci = (t_ci*)malloc(sizeof(t_ci));
	if (!newci)
		malloc_handling();
	newci->index = create_colorlist_container(qt);
	newci->next = NULL;
	return (newci);
}

void 		delete_tree_and_colorlist(t_qt **qt)
{
	if (!*qt)
		return ;
	delete_tree_and_colorlist(&(*qt)->no);
	delete_tree_and_colorlist(&(*qt)->ne);
	delete_tree_and_colorlist(&(*qt)->se);
	delete_tree_and_colorlist(&(*qt)->so);
	if (qt && *qt && (*qt)->cl && (*qt)->cl->container && (*qt)->deleted == 0)
	{
		delete_any_colorlist(&(*qt)->cl->container, (*qt)->cl);
		(*qt)->deleted = 1;
		free(*qt);
		*qt = NULL;
	}
}

t_cl 			*delete_any_colorlist(t_clc **c, t_cl *del)
{
	t_cl		*tmp;
	t_cl		*aux;

	if (!c || !(*c) || !del)
		return (del);
	aux = NULL;
	tmp = (*c)->last;
	while (tmp)
	{
		if (tmp == del && tmp)
		{
			printf("=> %p - %d ", (void*)(tmp), (*(tmp->qt))->n_node);
			if (tmp && (*c)->first == tmp)
				(*c)->first = (*c)->first->next;
			if (tmp && (*c)->last == tmp)
				(*c)->last = (*c)->last->prev;
			if (!tmp->prev)
			{
				aux = tmp;
				tmp = tmp->next;
				free(aux);
				aux = NULL;
				if (tmp)
					tmp->prev = NULL;
				return (tmp);
			}
			if (tmp)
				aux = tmp->prev;
			if (tmp->prev)
				tmp->prev->next = tmp->next;
			if (tmp->next)
				tmp->next->prev = tmp->prev;
			free(tmp);
			tmp = NULL;
			return (aux);
		}
		tmp = tmp->prev;
	}
	return (del);
}

void 			addback_colorlist(t_clc **c, t_qt **qt)
{
	t_cl		*prev;

	if (!*c)
		return ;
	if (!(*c)->last)
	{
		(*c)->first = create_colorlist(qt, c);
		(*c)->last = (*c)->first;
		return ;
	}
	prev = (*c)->last;
	(*c)->last->next = create_colorlist(qt, c);
	(*c)->last = (*c)->last->next;
	(*c)->last->prev = prev;
}

void 			addfront_colorindex(t_ci **c, t_qt **qt)
{
	t_ci		*newci;

	if (!*c)
	{
		*c = create_colorlist_index(qt);
		return ;
	}
	newci = create_colorlist_index(qt);
	newci->next = *c;
	*c = newci;
}
