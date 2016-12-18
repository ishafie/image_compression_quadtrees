#include "includes/quadtree.h"

void	malloc_handling(void)
{
	fprintf(stderr, "Erreur dans l'allocation\n");
	exit(EXIT_FAILURE);
}

void	err_what(int err)
{
	switch (err)
	{
		case 0:
		fprintf(stderr, "How did you even ... ?\n");
		break;
	}
	exit(EXIT_FAILURE);
}
