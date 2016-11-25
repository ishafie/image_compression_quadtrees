#ifndef QUADTREE_H
# define QUADTREE_H

# define TAILLE_X 512
# define TAILLE_Y 512
# define PROF 9

# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <MLV/MLV_all.h>

typedef struct			s_color
{
	int					red;
	int					green;
	int					blue;
	int					alpha;
}						t_color;

typedef struct			s_quadtree
{
	struct s_quadtree	*no;
	struct s_quadtree	*ne;
	struct s_quadtree	*se;
	struct s_quadtree	*so;
	int					prof;
}						t_qt;

void		malloc_handling();
MLV_Color	get_average_color_from_image(MLV_Image *img, int x1, int x2, int y1, int y2);
void 		generate_tree(MLV_Image *img, int max_prof, t_qt **qt, int x1, int x2, int y1, int y2);
int			is_leaf(t_qt *qt);
void		draw_quadtree(t_qt *qt, MLV_Image *img, int x1, int x2, int y1, int y2);

#endif
