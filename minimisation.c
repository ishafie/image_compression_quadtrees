#include "includes/quadtree.h"
#include "includes/colorlist.h"
#include "includes/err.h"

/*void 		analyze_minimize_and_draw(t_qt **qt)
{
	analyze_and_minimize(qt);
	MLV_clear_window(MLV_COLOR_BLACK);
	create_interface(*qt);
}*/

/*void 		test_draw(t_qt *qt)
{
	MLV_clear_window(MLV_COLOR_BLACK);
	draw_quadtree(qt, 0, TAILLE_X, 0, TAILLE_Y);
	MLV_actualise_window();
}*/

/*void 		parent_pointer(t_qt **parent, t_qt **qt, t_qt **new)
{
	if (!*parent)
		return ;
	if ((*parent)->no && (*parent)->no == *qt)
	{
		free(*qt);
		(*parent)->no = *new;
	}
	if ((*parent)->ne && (*parent)->ne == *qt)
	{
		free(*qt);
		(*qt) = *new;
		(*parent)->ne = *new;
	}
	if ((*parent)->se && (*parent)->se == *qt)
	{
		free(*qt);
		(*parent)->se = *new;
	}
	if ((*parent)->so && (*parent)->so == *qt)
	{
		free(*qt);
		(*parent)->so = *new;
	}
}*/

/*void 	delete_inner_tree(t_qt **racine, t_qt **qt)
{
	if (!(*qt) || !(*racine))
		return ;
	if ((*qt)->no)
	{
		free_tree(&(*qt)->no);
	}
	if ((*qt)->ne)
	{
		free_tree(&(*qt)->ne);
	}
	if ((*qt)->se)
	{
		free_tree(&(*qt)->se);
	}
	if ((*qt)->so)
	{
		free_tree(&(*qt)->so);
	}
	*qt = *racine;
}*/

/*void	 	compare_tree(t_ldc **ldc, t_qt **qt, t_qt **cmp, t_qt **parent)
{
	double	dist;
	static int i = 0;

	dist = 0;
	if (!qt && !cmp)
	{
		printf("nb dist = %d\n", i);
		return ;
	}
	if (*qt && *cmp && color_equal((*qt)->color, (*cmp)->color, 50))
	{
		dist = distance_two_inner_tree(qt, cmp);
		if (dist <= 10)
		{
			i++;
			add_order_ld(&(*ldc)->first, &(*ldc)->last, qt, cmp, dist);
			(void)parent;
			return ;
		}
		if ((*cmp) && (*cmp)->no)
 			compare_tree(ldc, qt, &(*cmp)->no, cmp);
		if ((*cmp) && (*cmp)->ne)
			compare_tree(ldc, qt, &(*cmp)->ne, cmp);
		if ((*cmp) && (*cmp)->se)
			compare_tree(ldc, qt, &(*cmp)->se, cmp);
		if ((*cmp) && (*cmp)->so)
			compare_tree(ldc, qt, &(*cmp)->so, cmp);
	}
}*/

/*void 	mini_with_loss(t_ldc **ldc, t_qt **racine, t_qt **qt)
{

	if (!*racine || !(*qt && *racine && color_equal((*racine)->color, (*qt)->color, 90)))
		return ;
	compare_tree(ldc, racine, qt, qt);
	if ((*racine) && (*racine)->no)
		mini_with_loss(ldc, &((*racine)->no), qt);
	if ((*racine) && (*racine)->ne)
		mini_with_loss(ldc, &((*racine)->ne), qt);
	if ((*racine) && (*racine)->se)
		mini_with_loss(ldc, &((*racine)->se), qt);
	if ((*racine) && (*racine)->so)
		mini_with_loss(ldc, &((*racine)->so), qt);
}*/

/*void 	free_and_relink_list(t_ldc **ldc)
{
	t_ld	*tmp;

	if (!*ldc)
		return ;
	tmp = (*ldc)->first;
	while (tmp)
	{
		if (tmp->a && tmp->b)
		{
			printf("ok\n");
			delete_inner_tree(tmp->a, tmp->b);
		}
		tmp = tmp->next;
	}
}*/

/*void 	analyze_and_minimize(t_qt **qt)
{
	t_ldc	*ldc;
	t_ld	*ld;

	ld = NULL;
	ldc = create_list_dist_container(ld);
	printf("Minimisation en cours...\n");
	if (!*qt)
		return ;
	mini_with_loss(&ldc, &(*qt)->no, &(*qt)->ne);
	printf("8%%\n");
	mini_with_loss(&ldc, &(*qt)->no, &(*qt)->se);
	printf("16%%\n");
	mini_with_loss(&ldc, &(*qt)->no, &(*qt)->so);
	printf("25%%\n");
	mini_with_loss(&ldc, &(*qt)->ne, &(*qt)->no);
	printf("33%%\n");
	mini_with_loss(&ldc, &(*qt)->ne, &(*qt)->se);
	printf("42%%\n");
	mini_with_loss(&ldc, &(*qt)->ne, &(*qt)->so);
	printf("50%%\n");
	mini_with_loss(&ldc, &(*qt)->se, &(*qt)->no);
	printf("58%%\n");
	mini_with_loss(&ldc, &(*qt)->se, &(*qt)->ne);
	printf("67%%\n");
	mini_with_loss(&ldc, &(*qt)->se, &(*qt)->so);
	printf("75%%\n");
	mini_with_loss(&ldc, &(*qt)->so, &(*qt)->no);
	printf("83%%\n");
	mini_with_loss(&ldc, &(*qt)->so, &(*qt)->ne);
	printf("92%%\n");
	mini_with_loss(&ldc, &(*qt)->so, &(*qt)->se);
	printf("100%%\n");
	compare_tree(NULL, NULL, NULL, NULL);
}
*/

t_qt		*is_subtree(t_qt *a, t_qt *b)
{
	if (!b)
		return (NULL);
	else if (a == b)
		return (a);
	else
	{
		if (is_subtree(a, b->no))
			return (a);
		if (is_subtree(a, b->ne))
			return (a);
		if (is_subtree(a, b->se))
			return (a);
		if (is_subtree(a, b->so))
			return (a);
		return (NULL);
	}
}

t_qt		*test_search(t_qt *a, t_qt *b)
{
	if (!b)
		return (NULL);
	else if (a == b)
	{
		/*if ((*(a->parent)))
		{
			printf("parent : %d\n", (*(a->parent))->n_node);
			if ((*(a->parent))->no)
				printf("parent->no : %d\n", (*(a->parent))->no->n_node);
			if ((*(a->parent))->ne)
				printf("parent->ne : %d\n", (*(a->parent))->ne->n_node);
			if ((*(a->parent))->se)
				printf("parent->se : %d\n", (*(a->parent))->se->n_node);
			if ((*(a->parent))->so)
				printf("parent->so : %d\n", (*(a->parent))->so->n_node);
		}*/
		if (a->par)
		{
			printf("parent : %d\n", a->par->n_node);
			if (a->par->no)
				printf("parent->no : %d\n", a->par->no->n_node);
			if (a->par->ne)
				printf("parent->ne : %d\n", a->par->ne->n_node);
			if (a->par->se)
				printf("parent->se : %d\n", a->par->se->n_node);
			if (a->par->so)
				printf("parent->so : %d\n", a->par->so->n_node);
		}
		printf("node ; %d\n", b->n_node);
		return (a);
	}
	else
	{
		/*printf("node ; %d\n", b->n_node);*/
		if (test_search(a, b->no))
			return (a);
		if (test_search(a, b->ne))
			return (a);
		if (test_search(a, b->se))
			return (a);
		if (test_search(a, b->so))
			return (a);
		return (NULL);
	}
}

t_qt		*test_search_nb(unsigned int node, t_qt *b)
{
	if (!b)
		return (NULL);
	else if (node == b->n_node)
	{
		if (b->par)
			printf("parent : (%d) => node ; %d\n", b->par->n_node, b->n_node);
		if (b->par->no)
			printf("parent->no : %d\n", b->par->no->n_node);
		if (b->par->ne)
			printf("parent->ne : %d\n", b->par->ne->n_node);
		if (b->par->se)
			printf("parent->se : %d\n", b->par->se->n_node);
		if (b->par->so)
			printf("parent->so : %d\n", b->par->so->n_node);
		return (b);
	}
	else
	{
		if (test_search_nb(node, b->no))
			return (b);
		if (test_search_nb(node, b->ne))
			return (b);
		if (test_search_nb(node, b->se))
			return (b);
		if (test_search_nb(node, b->so))
			return (b);
		return (NULL);
	}
}

int			is_child(t_qt *a, t_qt *b)
{
	if (a && (a->no == b || a->ne ==b || a->se == b || a->so == b))
		return (1);
	return (0);
}

t_cl 		*compare_colorlist(t_cl *a, t_cl **b, t_qt **g_c)
{
	double	dist;
	t_cl	*ret;
	t_qt	*qt;
	int		dir;
	static int test = 0;

	qt = NULL;
	dir = 0;
	ret = NULL;
	if (!a || !*b || a == *b || !(*b)->qt || !(*(*b)->qt)
	|| *(a->qt) == *((*b)->qt) || (*b)->deleted == 1 || (*(*b)->qt)->deleted == 1 || (*(*b)->qt)->n_node == 0)
	{
		return (ret);
	}
	/*printf("%p - %p\n", (void*)*(a->qt), (void*)*(b->qt));*/
	if (a && a->qt && (*(a->qt)) && b && (*b) && (*b)->qt)
	{
		/* 9 et 309*/
		if ((*(*b)->qt)->par != (*(a->qt)) && is_subtree((*(*b)->qt), *(a->qt)))
			return (ret);
		dist = get_dist_final(a->qt, (*b)->qt);
		/*printf("op = %lu\n", op);*/
		if (dist < 15)
		{
			test++;
			qt = (*(*b)->qt)->par;
			if (qt && qt->no == (*(*b)->qt))
				dir = 0;
			else if (qt && qt->ne == (*(*b)->qt))
				dir = 1;
			else if (qt && qt->se == (*(*b)->qt))
				dir = 2;
			else if (qt && qt->so == (*(*b)->qt))
				dir = 3;
			if ((*(*b)->qt)->par == (*(a->qt)))
			{
				if ((*b)->prev)
					ret = (*b)->prev;
				else
					ret = NULL;
				/*delete_tree_and_colorlist(&((*(*b)->qt)->no));
				delete_tree_and_colorlist(&((*(*b)->qt)->ne));
				delete_tree_and_colorlist(&((*(*b)->qt)->se));
				delete_tree_and_colorlist(&((*(*b)->qt)->so));*/
				if ((*(*b)->qt)->no)
					g_c[(*(*b)->qt)->no->n_node] = (*(*b)->qt)->no;
				if ((*(*b)->qt)->ne)
					g_c[(*(*b)->qt)->ne->n_node] = (*(*b)->qt)->ne;
				if ((*(*b)->qt)->se)
					g_c[(*(*b)->qt)->se->n_node] = (*(*b)->qt)->se;
				if ((*(*b)->qt)->so)
					g_c[(*(*b)->qt)->so->n_node] = (*(*b)->qt)->so;
				(*(*b)->qt)->no = NULL;
				(*(*b)->qt)->ne = NULL;
				(*(*b)->qt)->se = NULL;
				(*(*b)->qt)->so = NULL;
				return (ret);
			}

			/*printf("cmp = %p - test = %d\n", (void*)*qt, test);*/
			(*b)->deleted = 1;
			/*if ((*b)->next)
				(*b)->next->prev = (*b)->prev;*/
			if ((*b)->prev)
				ret = (*b)->prev;
			else
				ret = NULL;
			/*delete_tree_and_colorlist((*b)->qt);*/
			g_c[(*(*b)->qt)->n_node] = (*(*b)->qt);
			(*(*b)->qt) = NULL;
			(*b)->qt = NULL;
			*b = NULL;
			if (dir == 0)
				qt->no = *(a->qt);
			if (dir == 1)
				qt->ne = *(a->qt);
			if (dir == 2)
				qt->se = *(a->qt);
			if (dir == 3)
				qt->so = *(a->qt);
			if (qt)
				qt->deleted = 1;
			/*b->qt = a->qt;*/
			/**(b->qt) = *(a->qt);*/
			/*printf("dist = %f\n", dist);*/
			return (ret);
		}
	}
	return (ret);
}

void 		minimize_colorlist(t_clc **c, t_qt **g_c)
{
	t_cl	*cmp;
	t_cl	*last;
	/*int line;*/

	if (!(*c) || !(*c)->last || (*c)->last == (*c)->first)
		return ;
	last = (*c)->last;
	cmp = (*c)->last->prev;
	/*line = count_color_line((*c));*/
	while (last)
	{
		while (cmp && cmp != last)
			cmp = compare_colorlist(last, &cmp, g_c);
		if ((*c) && (*c)->last)
			cmp = (*c)->last->prev;
		last = last->prev;
	}
}

void 		minimize2(t_ci **c, t_qt ***garbage_collector)
{
	t_ci	*tmp;
	int		i;

	i = 0;
	tmp = *c;
	while (i < OP_MINI * 4 + 1)
		(*garbage_collector)[i++] = NULL;
	while (tmp)
	{
		minimize_colorlist(&(tmp->index), *garbage_collector);
		tmp = tmp->next;
	}
	/*test_search_nb(79, test_racine);
	test_search_nb(63, test_racine);*/
}
