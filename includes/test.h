#ifndef TEST_H
# define TEST_H

#include "quadtree_struct.h"
#include "colorlist.h"

void	test_color(void);
void 	test_decode(void);
void 	test_encode(t_qt *qt);
void	test_lstorder(t_list *l_dist, t_list *last);
void 	parcours_test(t_qt *qt);
void 	test_decode_encode_graph(const char *filename);
void 	test_colorlist(t_ci *ci);

#endif
