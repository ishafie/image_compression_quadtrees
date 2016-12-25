#include "includes/quadtree.h"

void 		analyze_minimize_and_draw(t_qt **qt)
{
	analyze_and_minimize(qt);
	MLV_clear_window(MLV_COLOR_BLACK);
	create_interface(*qt);
}

void 		test_draw(t_qt *qt)
{
	MLV_clear_window(MLV_COLOR_BLACK);
	draw_quadtree(qt, 0, TAILLE_X, 0, TAILLE_Y);
	MLV_actualise_window();
}

void 		parent_pointer(t_qt **parent, t_qt **qt, t_qt **new)
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
}

void 	delete_inner_tree(t_qt **racine, t_qt **qt)
{
	if (!(*qt) || !(*racine))
		return ;
	/*test_draw(*parent);
	MLV_wait_mouse(0, 0);*/
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
	/*parent_pointer(parent, qt, racine);*/
	/*test_draw(*parent);
	MLV_wait_mouse(0, 0);*/
}

void	 	compare_tree(t_ldc **ldc, t_qt **qt, t_qt **cmp, t_qt **parent)
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
			/*delete_inner_tree(qt, cmp, parent);*/
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
}

void 	mini_with_loss(t_ldc **ldc, t_qt **racine, t_qt **qt)
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
}

void 	free_and_relink_list(t_ldc **ldc)
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
}

void 	analyze_and_minimize(t_qt **qt)
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
	/*display_list_dist(ldc->first);*/
	/*free_and_relink_list(&ldc);*/
}
