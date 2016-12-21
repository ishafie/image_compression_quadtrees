#ifndef QUADTREE_H
# define QUADTREE_H

# define PERTE 6
# define TAILLE_X 512
# define TAILLE_Y 512
# define OP 5000 /* 65536 - 45sec */
# define DISPLAY 0
# define TRUE 1

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <string.h>
# include <math.h>
# include <MLV/MLV_all.h>
# include <pthread.h>

enum {WHAT, FILE_ISSUE};

typedef struct			s_zone
{
	int					x1;
	int					x2;
	int					y1;
	int					y2;
}						t_zone;

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
	unsigned int		n_node;
	double				dist;
	MLV_Color			color;
}						t_qt;

typedef struct			s_list
{
	struct s_list		*next;
	struct s_list		*prev;
	struct s_quadtree	*ptr;
	double				dist;
	struct s_zone		zone;
}						t_list;

typedef struct			s_list_container
{
	struct s_list		*first;
	struct s_list		*last;
}						t_lc;

typedef struct					s_list_encoding
{
	struct s_list_encoding		*next;
	struct s_quadtree			*ptr;
	unsigned int				n_node;
}								t_le;

typedef struct			s_thread
{
	t_qt				**qt;
	t_lc				**l;
	MLV_Image			*img;
	int					x1;
	int					x2;
	int					y1;
	int					y2;
}						t_thread;

t_qt		*g_test;
int			g_nb_op_creation;
int			g_nb_op_parcours;

void		malloc_handling();
void		err_what(int err);

int			cmp_tree(t_qt **qt, t_qt **paire);

double		dist(t_color px, t_color moy);
t_qt		*create_tree(void);
void		MLV_Color_to_color(MLV_Color x, t_color *x_c);
int			count_node(t_qt *qt);
double		max(double a, double b);
int			get_prof(t_qt *qt, int prof);
void		minimise_prof(t_qt **qt, int nb_color, int max_prof);

void		quadtree_maker2(t_lc **l, MLV_Image *img, t_qt **qt, int operations);

void		quadtree_maker(MLV_Image *img, t_qt **qt, int operations);
void		print_every_color_equal(t_qt **qt, t_qt **tmp, MLV_Color, int *nb_color);
void		check_every_color_doublon(t_qt **qt, t_qt **tmp, int *nb_color);
void		print_color(MLV_Color x);

void		generate_tree_test(MLV_Image *img, int max_prof, t_qt **qt, int x1, int x2, int y1, int y2);
double		find_worst(t_qt *qt, double worst);
double		get_error_dist(MLV_Image *img, int x1, int x2, int y1, int y2, t_qt **qt);
MLV_Color	get_average_color_from_image(MLV_Image *img, int x1, int x2, int y1, int y2);
t_color		get_average_rgba_from_image(MLV_Image *img, int x1, int x2, int y1, int y2);
int			generate_tree(MLV_Image *img, int max_prof, t_qt **qt, int x1, int x2, int y1, int y2);
int			is_leaf(t_qt *qt);
void		draw_quadtree(t_qt *qt, int x1, int x2, int y1, int y2);
int			color_equal(MLV_Color x, MLV_Color y, int perte);
int			color_diff(MLV_Color x, MLV_Color y);

void		find_tree_min_dist(MLV_Image *img, t_qt **qt, t_qt **paire);
void		minimise_perte(MLV_Image *img, t_qt **racine, t_qt **qt);
void		minimise_perte_hub(MLV_Image *img, t_qt **racine, t_qt **qt);

double		get_dist_final(t_qt **a, t_qt **b);
int			is_no_leaf(t_qt *a);
void		free_tree(t_qt **qt);
int			is_part_of(t_qt *a, t_qt *b);


void 		encodage(t_qt *qt, const char *name);
void 		encode_graph(t_qt *qt, FILE *f);

void 		decodage(const char *filename, t_qt **qt);
void 		decode_graph(t_qt **qt, int fd, t_le **l);

int			add_node_to_le(unsigned int n, t_le **l, t_qt *ptr);
t_qt		*search_node(unsigned int n, t_le **l);

void		encode(t_qt *qt, unsigned char **buf, int *i);
void		decode(t_qt **qt, unsigned char *code, int *i, int max);
void		write_in_file(const char *name, const unsigned char *buf, int len);

void		display_list(t_list *l, t_list *last);
int 		add_order(t_list **l, t_list **last, t_qt *ptr, double dist, t_zone zone);

void		fill_zone(t_zone *zone, int x1, int x2, int y1, int y2);
void		print_zone(t_zone z);



void	free_tree(t_qt **qt);
void 	analyze_and_minimize(t_qt **qt);
double	distance_two_inner_tree(t_qt **a, t_qt **b);

#endif
