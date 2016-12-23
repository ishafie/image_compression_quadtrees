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
		case 1:
		fprintf(stderr, "Impossible de creer ou de modifier le fichier.\n");
		case 2:
		fprintf(stderr, "Image inaccessible\n");
		break;
	}
	exit(EXIT_FAILURE);
}
