#include "includes/colorlist.h"

t_cl			*create_colorlist(t_qt **qt)
{
	t_cl		*newcl;

	newcl = (t_cl*)malloc(sizeof(t_cl));
	if (!newcl)
		malloc_handling();
	newcl->qt = qt;
	newcl->next = NULL;
	return (newcl);
}

t_clc			*create_colorlist_container(t_qt **qt)
{
	t_clc		*newclc;

	newclc = (t_clc*)malloc(sizeof(t_clc));
	if (!newclc)
		malloc_handling();
	newclc->first = create_colorlist(qt);
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

void 			addback_colorlist(t_clc **c, t_qt **qt)
{
	if (!*c)
		return ;
	if (!(*c)->last)
	{
		(*c)->first = create_colorlist(qt);
		(*c)->last = (*c)->first;
		return ;
	}
	(*c)->last->next = create_colorlist(qt);
	(*c)->last = (*c)->last->next;
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
