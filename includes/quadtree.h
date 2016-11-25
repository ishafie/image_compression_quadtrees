#ifndef QUADTREE_H
# define QUADTREE_H

# define TAILLE_X 512
# define TAILLE_Y 512
# define PROF 2

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
	double				dist;
	MLV_Color			color;
}						t_qt;

void		malloc_handling();
void		err_what(int err);

void		quadtree_maker(MLV_Image *img, t_qt **qt, int operations);

void		generate_tree_test(MLV_Image *img, int max_prof, t_qt **qt, int x1, int x2, int y1, int y2);
double		find_worst(t_qt *qt, double worst);
double		get_error_dist(MLV_Image *img, int x1, int x2, int y1, int y2, t_qt **qt);
MLV_Color	get_average_color_from_image(MLV_Image *img, int x1, int x2, int y1, int y2);
t_color		get_average_rgba_from_image(MLV_Image *img, int x1, int x2, int y1, int y2);
int			generate_tree(MLV_Image *img, int max_prof, t_qt **qt, int x1, int x2, int y1, int y2);
int			is_leaf(t_qt *qt);
void		draw_quadtree(t_qt *qt, MLV_Image *img, int x1, int x2, int y1, int y2);


#endif
