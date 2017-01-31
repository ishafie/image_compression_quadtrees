#include "includes/quadtree.h"
#include "includes/get_next_line.h"
#include "includes/err.h"

void 		hub_decode_graph(const char *filename, t_qt **qt, int color)
{
	int				fd;
	t_qt			**tab;
	int				i;

	i = 0;
	tab = (t_qt**)malloc(sizeof(t_qt*) * (OP * 4 + 1));
	if (!tab)
		malloc_handling();
	while (i < (OP * 4 + 1))
		tab[i++] = NULL;
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		err_what(FILE_ISSUE);
	if (color == COLOR)
	{
		printf("Decodage en couleur...\n");
		decode_graph(qt, fd, tab);
		/*decode_graph(qt, fd, &l);*/
	}
	else
	{
		printf("Decodage en noir et blanc...\n");
		decode_graph_nocolor(qt, fd, tab);
	}
	printf("Decodage terminé.\n");
	free(tab);
	close(fd);
}

static int 		get_node(const char *line, char n_node[16], int *i, char *pos)
{
	int		index;

	index = 0;
	while (line[*i] && line[*i] != ':' && line[*i] != '-')
	{
		n_node[index] = line[*i];
		index++;
		*i += 1;
	}
	n_node[index] = 0;
	if (!line[*i])
		return (1);
	*i += 1;
	*pos = line[*i];
	*i += 1;
	return (0);
}

static int 		get_leaf(const char *line, char color[16], int *i)
{
	int		index;

	index = 0;
	while (line[*i] && line[*i] != '=' && line[*i] != '-' && index < 16)
	{
		color[index] = line[*i];
		*i += 1;
		index++;
	}
	color[index] = 0;
	if (!line[*i])
		return (1);
	*i += 1;
	return (0);
}

static int 		get_color(const char *line, char color[16], int *i)
{
	int		index;

	index = 0;
	while (line[*i] && line[*i] != '=' && line[*i] != '-' && index < 2)
	{
		color[index] = line[*i];
		*i += 1;
		index++;
	}
	color[index] = 0;
	if (!line[*i])
		return (1);
	return (0);
}

static void 		create_leaf_from_line_nocolor(t_qt **qt, const char *line, t_qt **tab)
{
	unsigned int	n;
	int				i;
	char			color[16];

	i = 0;
	get_leaf(line, color, &i);
	n = (unsigned int)strtol(color, NULL, 16);
	if (tab[n])
		*qt = tab[n];
	else
	{
		*qt = create_tree(1);
		(*qt)->n_node = n;
		tab[n] = *qt;
	}
	(*qt)->n_node = n;
	if (line[i] == '0')
		(*qt)->color = MLV_COLOR_BLACK;
	else
		(*qt)->color = MLV_COLOR_WHITE;
}

static void 		search_or_create(t_qt **tree, const char n_node[16], t_qt **tab, char pos)
{

	unsigned int		n;
	t_qt				**qt;

	if (pos == 0)
		qt = tree;
	else if (pos == 'a')
		qt = &(*tree)->no;
	else if (pos == 'b')
		qt = &(*tree)->ne;
	else if (pos == 'c')
		qt = &(*tree)->se;
	else if (pos == 'd')
		qt = &(*tree)->so;
	n = (unsigned int)strtol(n_node, NULL, 16);
	if (tab[n])
		*qt = tab[n];
	else
	{
		*qt = create_tree(1);
		(*qt)->n_node = n;
		tab[n] = *qt;
	}
}

static void 		create_leaf_from_line(t_qt **qt, const char *line, t_qt **tab)
{
	unsigned int	n;
	int				i;
	char			color[16];
	t_color			c;

	i = 0;
	get_leaf(line, color, &i);
	n = (unsigned int)strtol(color, NULL, 16);
	if (tab[n])
		*qt = tab[n];
	else
	{
		*qt = create_tree(1);
		(*qt)->n_node = n;
		tab[n] = *qt;
	}
	(*qt)->n_node = n;
	get_color(line, color, &i);
	n = (int)strtol(color, NULL, 16);
	c.red = n;
	get_color(line, color, &i);
	n = (int)strtol(color, NULL, 16);
	c.green = n;
	get_color(line, color, &i);
	n = (int)strtol(color, NULL, 16);
	c.blue = n;
	get_color(line, color, &i);
	n = (int)strtol(color, NULL, 16);
	c.alpha = n;
	(*qt)->color = MLV_convert_rgba_to_color(c.red, c.green, c.blue, c.alpha);
}

static void 		create_node_from_line(t_qt **qt, const char *line, t_qt **tab)
{

	int					i;
	int					ret;
	char				n_node[16];
	char				pos;
	char				save;

	pos = 0;
	i = 0;
	ret = get_node(line, n_node, &i, &save);
	pos = save;
	search_or_create(qt, n_node, tab, 0);
	if (ret)
		return ;
	ret = get_node(line, n_node, &i, &save);
	search_or_create(qt, n_node, tab, pos);
	if (ret)
		return ;
	pos = save;
	ret = get_node(line, n_node, &i, &save);
	search_or_create(qt, n_node, tab, pos);
	if (ret)
		return ;
	pos = save;
	ret = get_node(line, n_node, &i, &save);
	search_or_create(qt, n_node, tab, pos);
	if (ret)
		return ;
	pos = save;
	get_node(line, n_node, &i, &save);
	search_or_create(qt, n_node, tab, pos);
}

void 		decode_graph(t_qt **qt, int fd, t_qt **tab)
{
	char	*line;

	line = NULL;
	if (get_next_line(fd, &line) <= 0)
		return ;
	if (strchr(line, ':'))
		create_node_from_line(qt, line, tab);
	else
		create_leaf_from_line(qt, line, tab);
	free(line);
	if ((*qt)->no)
		decode_graph(&(*qt)->no, fd, tab);
	if ((*qt)->ne)
		decode_graph(&(*qt)->ne, fd, tab);
	if ((*qt)->se)
		decode_graph(&(*qt)->se, fd, tab);
	if ((*qt)->so)
		decode_graph(&(*qt)->so, fd, tab);
}

void 		decode_graph_nocolor(t_qt **qt, int fd, t_qt **tab)
{
	char	*line;

	line = NULL;
	if (get_next_line(fd, &line) <= 0)
		return ;
	if (strchr(line, ':'))
		create_node_from_line(qt, line, tab);
	else
		create_leaf_from_line_nocolor(qt, line, tab);
	free(line);
	if ((*qt)->no)
		decode_graph_nocolor(&(*qt)->no, fd, tab);
	if ((*qt)->ne)
		decode_graph_nocolor(&(*qt)->ne, fd, tab);
	if ((*qt)->se)
		decode_graph_nocolor(&(*qt)->se, fd, tab);
	if ((*qt)->so)
		decode_graph_nocolor(&(*qt)->so, fd, tab);
}
