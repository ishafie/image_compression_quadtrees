#include "includes/quadtree.h"

void 	test_draw(t_qt *qt)
{
	MLV_clear_window(MLV_COLOR_BLACK);
	draw_quadtree(qt, 0, TAILLE_X, 0, TAILLE_Y);
	MLV_actualise_window();
	MLV_wait_mouse(0, 0);
}

void 		parent_pointer(t_qt **parent, t_qt **qt, t_qt **new)
{
	if (!*parent)
		return ;
	if ((*parent)->no && (*parent)->no == *qt)
		(*parent)->no = *new;
	if ((*parent)->ne && (*parent)->ne == *qt)
		(*parent)->ne = *new;
	if ((*parent)->se && (*parent)->se == *qt)
		(*parent)->se = *new;
	if ((*parent)->so && (*parent)->so == *qt)
		(*parent)->so = *new;
}

void 	delete_inner_tree(t_qt **racine, t_qt **qt, t_qt **parent)
{
	if (!(*qt) || !(*racine) || !(*parent))
		return ;
	if ((*qt)->no)
	{
		free_tree(&(*qt)->no);
		(*qt)->no = NULL;
	}
	if ((*qt)->ne)
	{
		free_tree(&(*qt)->ne);
		(*qt)->ne = NULL;
	}
	if ((*qt)->se)
	{
		free_tree(&(*qt)->se);
		(*qt)->se = NULL;
	}
	if ((*qt)->so)
	{
		free_tree(&(*qt)->so);
		(*qt)->so = NULL;
	}
	parent_pointer(parent, qt, racine);
	(*qt) = NULL;
}



void	 	compare_tree(t_qt **qt, t_qt **cmp, t_qt **parent)
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
		if (dist < 10)
		{
			i++;
			/*printf("node %d(%p) vs node %d(%p)\n", (*qt)->n_node, (void*)*qt, (*cmp)->n_node, (void*)*cmp);*/
			/*parcours_test(*cmp);*/
			delete_inner_tree(qt, cmp, parent);
			/*parent_pointer(cmp_parent, qt, dir);*/
			/*printf("now cmp = %d(%p)\n", (*cmp)->n_node, (void*)*cmp);*/
			/*MLV_wait_mouse(0, 0);*/
			return ;
		}
		if ((*cmp) && (*cmp)->no)
 			compare_tree(qt, &(*cmp)->no, cmp);
		if ((*cmp) && (*cmp)->ne)
			compare_tree(qt, &(*cmp)->ne, cmp);
		if ((*cmp) && (*cmp)->se)
			compare_tree(qt, &(*cmp)->se, cmp);
		if ((*cmp) && (*cmp)->so)
			compare_tree(qt, &(*cmp)->so, cmp);
	}
}

void 	mini_with_loss(t_qt **racine, t_qt **qt)
{

	if (!*racine || !(*qt && *racine && color_equal((*racine)->color, (*qt)->color, 50)))
		return ;
	compare_tree(racine, qt, qt);
	if ((*racine) && (*racine)->no)
		mini_with_loss(&((*racine)->no), qt);
	if ((*racine) && (*racine)->ne)
		mini_with_loss(&((*racine)->ne), qt);
	if ((*racine) && (*racine)->se)
		mini_with_loss(&((*racine)->se), qt);
	if ((*racine) && (*racine)->so)
		mini_with_loss(&((*racine)->so), qt);
}

void 	analyze_and_minimize(t_qt **qt)
{
	printf("Minimisation en cours...\n");
	if (!*qt)
		return ;
	mini_with_loss(&(*qt)->no, &(*qt)->ne);
	printf("8%%\n");
	mini_with_loss(&(*qt)->no, &(*qt)->se);
	printf("16%%\n");
	mini_with_loss(&(*qt)->no, &(*qt)->so);
	printf("25%%\n");
	mini_with_loss(&(*qt)->ne, &(*qt)->no);
	printf("33%%\n");
	mini_with_loss(&(*qt)->ne, &(*qt)->se);
	printf("42%%\n");
	mini_with_loss(&(*qt)->ne, &(*qt)->so);
	printf("50%%\n");
	mini_with_loss(&(*qt)->se, &(*qt)->no);
	printf("58%%\n");
	mini_with_loss(&(*qt)->se, &(*qt)->ne);
	printf("67%%\n");
	mini_with_loss(&(*qt)->se, &(*qt)->so);
	printf("75%%\n");
	mini_with_loss(&(*qt)->so, &(*qt)->no);
	printf("83%%\n");
	mini_with_loss(&(*qt)->so, &(*qt)->ne);
	printf("92%%\n");
	mini_with_loss(&(*qt)->so, &(*qt)->se);
	printf("100%%\n");
}
