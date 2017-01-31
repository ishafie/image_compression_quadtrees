/*! \file quadtree.h
    \brief Header file for quadtree related functions

*/
/*! \fn char *ft_strdup(const char *s1);
    \brief Duplicate a string.
    \param s1 The string to duplicate.
    \return The pointer on the duplicated string.
*/
/*! \fn double dist(t_color px, t_color moy)
    \brief Calculate the distance between px and moy.
    \param px The color of the sum of pixel
	\param moy The average color of the zone
	\return The distance between px and moy.
*/
/*! \fn t_qt *create_tree(int reset)
    \brief return a pointer on a allocated quadtree node.
	A static variable allows us to increment the number of the node each
	time we enter the function.
    \param reset is used to set the number of nodes to 0.
	\return A pointer on an allocated quadtree node.
*/
/*! \fn void MLV_Color_to_color(MLV_Color x, t_color *x_c)
    \brief Converts MLV_Color to t_color
    \param x, the color to convert to t_color
    \param x_c, the container of the new converted color.
*/
/*! \fn int	count_node(t_qt *qt);
    \brief Count the number of nodes of a quadtree.
    \param qt a quadtree.
	\return The number of nodes of qt.
*/
/*! \fn double max(double a, double b);
    \brief Get the max between a and b
    \param a a double
    \param b a double
	\return the greater between a and b
*/
/*! \fn void quadtree_maker2(t_lc **l, MLV_Image *img, t_qt **qt, int operations)
    \brief Create a quadtree based on img.
	Calculates the distance between the average color of the actual zone and each of the pixels
	composing the image at that specific zone.
	Keeps every distance in a sorted double linked list contained in a list_container l.
	The first node of the list is the one we have to divide in 4.
    \param l list container with a pointer on the first element of a list used to get the worst distance.
    \param img the image used to create the quadtree.
	\param qt the quadtree created.
	\param operations the number of operations (the lower, the lesser the quality of the image)
*/
/*! \fn void delete_tree(t_qt **qt)
    \brief Delete every node of the quadtree qt
    \param qt, the quadtree to delete
*/
/*! \fn t_color	get_average_rgba_from_image(MLV_Image *img, int x1, int x2, int y1, int y2)
    \brief Return the average color of the zone of an image based on the pixels from x1 to x2 and y1 to y2.
    \param img the image
    \param x1 is the x coordinate of the top left corner of the zone
	\param x2 is the x coordinate of the bottom right corner of the zone
	\param y1 is the y coordinate of the top left corner of the zone
	\param y2 is the y coordinate of the bottom left corner of the zone
	\return the average color of the zone as a t_color struct.
*/
/*! \fn MLV_Color get_average_color_from_image(MLV_Image *img, int x1, int x2, int y1, int y2)
    \brief Return the average color of the zone of an image based on the pixels from x1 to x2 and y1 to y2.
    \param img the image
    \param x1 is the x coordinate of the top left corner of the zone
	\param x2 is the x coordinate of the bottom right corner of the zone
	\param y1 is the y coordinate of the top left corner of the zone
	\param y2 is the y coordinate of the bottom left corner of the zone
	\return the average color of the zone as a MLV_Color.
*/
/*! \fn void draw_quadtree(t_qt *qt, int x1, int x2, int y1, int y2)
    \brief Draw the quadtree on the window using the leaves of the quadtree.
	To draw the whole image, qt should be the root, x1 should be 0, x2 should be the width of the window
	y1 should be 0 and y2 should be the height of the screen.
    \param img the image
    \param x1 is the x coordinate of the top left corner of the zone
	\param x2 is the x coordinate of the bottom right corner of the zone
	\param y1 is the y coordinate of the top left corner of the zone
	\param y2 is the y coordinate of the bottom left corner of the zone
*/
/*! \fn int	color_equal(MLV_Color x, MLV_Color y, int perte)
    \brief Compare two colors with a tolerance threshold.
    \param x the first color to compare
    \param y the second color to compare
	\param perte the threshold
	\return 1 if x is similar to y based on perte difference or 0 if they're not similar enough.
*/
/*! \fn int	color_diff(MLV_Color x, MLV_Color y)
    \brief Return the difference of two colors
    \param x the first color to compare
    \param y the second color to compare
	\return the difference between the rgba values of x and y
*/
/*! \fn double get_dist_final(t_qt **a, t_qt **b)
    \brief Return the distance between quadtrees a and b
    \param a the first quadtree to compare
    \param b the second quadtree to compare
	\return the distance between the two quadtrees
*/
/*! \fn int	is_leaf(t_qt *a)
    \brief Check if a is a leaf
	\param a the quadtree to check
	\return 1 if a is leaf else 0.
*/
/*! \fn void encode_bin(t_qt *qt, const char *filename, int color)
	\brief Opens FILE, creates filename with extension and launches binary encoding.
    \param qt the quadtree containing the image
    \param filename the name of the file to be created without extension.
	\param color either COLOR or NOCOLOR, specifies if we shall encode with colors or in black and white.
*/
/*! \fn char *add_ext_to_filename(const char *file, const char *ext)
    \brief Add an extension to a file's name.
    \param file the complete name of a file with an extension to replace by ext.
    \param ext the wanted extension
	\return the new correct filename allocated.
*/
/*! \fn void hub_encode_graph(t_qt *qt, const char *name, int color)
    \brief Opens FILE, creates filename with extension and launches graph encoding.
    \param qt the quadtree containing the image
    \param name the name of the file without extension that will contain the encoded quadtree
	\param color specifies if the quadtree should be encoded with color or not.
*/
/*! \fn void encode_graph(t_qt *qt, FILE *f)
    \brief Encode with graph method in f based on qt. A node is translated in hexadecimal by his number n_node previously defined in the struct.
	Then, his children would also be represented by hexadecimal values corresponding to their number n_node.
	Leaves start by '=' and every 2 char represent a value of rgba.
    \param qt the quadtree containing the image
    \param f is the pointer on the actual position of the file.
*/
/*! \fn void hub_decode_graph(const char *filename, t_qt **qt, int color)
    \brief Opens file named filename and decodes its content in qt. In black and white if color is NOCOLOR or in color if color equals COLOR.
    \param filename name of the file to open and decode.
	\param qt the quadtree to fill
    \param color COLOR or NOCOLOR for a decoding in color or in black and white.
*/
/*! \fn void decode_bin_nocolor(t_qt **qt, FILE *fp)
    \brief Decode with no color the file fp and keeps it in qt.
    \param qt quadtree container of the decoding.
	\param fp is the pointer on the actual position of the file.
*/
/*! \fn void decode_graph(t_qt **qt, int fd, t_qt **tab)
    \brief Decode with color the file fp and keeps it in qt.
	Uses tab to decode the file. (Adding in tab, searching in tab)
    \param qt quadtree container of the decoding.
	\param fp is the pointer on the actual position of the file.
*/
/*! \fn void decode_graph_nocolor(t_qt **qt, int fd, t_qt **tab)
    \brief Decode with color the file fp and keeps it in qt.
	Uses tab to decode the file.(Adding in tab, searching in tab)
    \param qt quadtree container of the decoding.
	\param fp is the pointer on the actual position of the file.
*/
/*! \fn void encode(t_qt *qt, FILE *fp)
    \brief Opens FILE, creates filename with extension and launches binary encoding.
    \param qt quadtree container of the decoding.
	\param fp is the pointer on the actual position of the file.
*/
/*! \fn void encode_graph_nocolor(t_qt *qt, FILE *fp)
	\brief Encode with graph method in f based on qt. A node is translated in hexadecimal by his number n_node previously defined in the struct.
	Then, his children would also be represented by hexadecimal values corresponding to their number n_node.
	Leaves start by '=' and are equal to 0 or 1 if the color of the leaf is black or white.
	\param qt the quadtree containing the image
	\param f is the pointer on the actual position of the file.
*/
/*! \fn void decode_bin(t_qt **qt, FILE *fp)
	\brief Encode with graph method in f based on qt. A node is translated in hexadecimal by his number n_node previously defined in the struct.
	Then, his children would also be represented by hexadecimal values corresponding to their number n_node.
	Leaves start by '=' and are equal to 0 or 1 if the color of the leaf is black or white.
	\param qt the quadtree containing the image
	\param f is the pointer on the actual position of the file.
*/



#ifndef QUADTREE_H
# define QUADTREE_H

# define OP 65536 /* 65536 - 45sec */
# define OP_MINI 10000
# define DISPLAY 0
# define TRUE 1

# include "libinclude.h"
# include "quadtree_struct.h"

enum {WHAT, FILE_ISSUE, IMG_NOT_FOUND, COLOR, NOCOLOR};

typedef struct					s_color
{
	int							red;
	int							green;
	int							blue;
	int							alpha;
}								t_color;

char		*ft_strdup(const char *s1);

double		dist(t_color px, t_color moy);
t_qt		*create_tree(int reset);
void		MLV_Color_to_color(MLV_Color x, t_color *x_c);
int			count_node(t_qt *qt);

void		quadtree_maker2(t_lc **l, MLV_Image *img, t_qt **qt, int operations);
void 		delete_tree(t_qt **qt);

MLV_Color	get_average_color_from_image(MLV_Image *img, int x1, int x2, int y1, int y2);
t_color		get_average_rgba_from_image(MLV_Image *img, int x1, int x2, int y1, int y2);

void		draw_quadtree(t_qt *qt, int x1, int x2, int y1, int y2);
int			color_equal(MLV_Color x, MLV_Color y, int perte);
int			color_diff(MLV_Color x, MLV_Color y);

double		get_dist_final(t_qt **a, t_qt **b);
int			is_leaf(t_qt *qt);

void 		encode_bin(t_qt *qt, const char *filename, int color);
char		*add_ext_to_filename(const char *file, const char *ext);
void 		hub_encode_graph(t_qt *qt, const char *name, int color);
void 		encode_graph(t_qt *qt, FILE *f);

void 		hub_decode_graph(const char *filename, t_qt **qt, int color);
void       	decode_bin_nocolor(t_qt **qt, FILE *fp);
void 		decode_graph(t_qt **qt, int fd, t_qt **tab);
void 		decode_graph_nocolor(t_qt **qt, int fd, t_qt **tab);

void		encode(t_qt *qt, FILE *fp);
void 		encode_graph_nocolor(t_qt *qt, FILE *fp);
void		decode_bin(t_qt **qt, FILE *fp);
void		write_in_file(const char *name, const unsigned char *buf, int len);

void		display_list(t_list *l, t_list *last);
int 		add_order(t_list **l, t_list **last, t_qt *ptr, double dist, t_zone zone);
t_lc		*create_list_container(t_list *l_dist);

void		fill_zone(t_zone *zone, int x1, int x2, int y1, int y2);
void		print_zone(t_zone z);


char		*start_screen(void);
void 		create_interface(t_qt *qt);
void 		draw_interface(MLV_Font *font);
void 		click_interface(t_qt **qt, char *filename, MLV_Image *img);
void 		open_img(t_qt **qt, char **filename, int *mini, MLV_Image **img);

int			is_qtn(const char *str);
int			is_qtc(const char *str);
int			is_img(char *str);
int			is_gmc(const char *str);
int			is_gmn(const char *str);

#endif
