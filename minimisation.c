#include "includes/quadtree.h"

void 	test_draw(t_qt *qt)
{
	MLV_clear_window(MLV_COLOR_BLACK);
	draw_quadtree(qt, 0, TAILLE_X, 0, TAILLE_Y);
	MLV_actualise_window();
	MLV_wait_mouse(0, 0);
}

void 	delete_inner_tree(t_qt **racine, t_qt **qt)
{
	free_tree(&(*qt)->no);
	free_tree(&(*qt)->ne);
	free_tree(&(*qt)->se);
	free_tree(&(*qt)->so);
	qt = racine;
	*qt = *racine;
}

void 	compare_tree(t_qt **qt, t_qt **cmp)
{
	double	dist;
	static int i = 0;

	dist = 0;
	if (*qt && *cmp && color_equal((*qt)->color, (*cmp)->color, 50))
	{
		dist = distance_two_inner_tree(qt, cmp);
		if (dist < 10)
		{
			i++;
			delete_inner_tree(qt, cmp);
			return ;
		}
		compare_tree(qt, &(*cmp)->no);
		compare_tree(qt, &(*cmp)->ne);
		compare_tree(qt, &(*cmp)->se);
		compare_tree(qt, &(*cmp)->so);
	}

}

void 	mini_with_loss(t_qt **racine, t_qt **qt)
{
	if (!*racine)
		return ;
	compare_tree(racine, qt);
	mini_with_loss(&((*racine)->no), qt);
	mini_with_loss(&((*racine)->ne), qt);
	mini_with_loss(&((*racine)->se), qt);
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
