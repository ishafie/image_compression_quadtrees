#include "includes/quadtree.h"

void 		encodage(t_qt *qt, const char *name)
{
	FILE 			*fp;
    char 			*filename;
    unsigned int    i;
    unsigned int   	filelen;

    filelen = strlen(name) + 5;
    i = 0;
    filename = (char*)malloc(sizeof(char) * filelen);
    if (!filename)
        malloc_handling();
    while (i < filelen)
    {
        filename[i] = 0;
        i++;
    }
    strcpy(filename, name);
    strcat(filename, ".tgc");
    fp = fopen(filename, "w");
    if (!fp)
        err_what(FILE_ISSUE);
	encode_graph(qt, fp);
}

void 		print_delimiter_if_necessary(FILE *fp, t_qt *a, t_qt *b, t_qt *c)
{
	if (a || b || c)
		fprintf(fp, "-");
}

void 		encode_graph(t_qt *qt, FILE *fp)
{
	t_color color;

	if (!qt)
		return ;
	fprintf(fp, "%x", qt->n_node);
	if (is_leaf(qt))
	{
		MLV_Color_to_color(qt->color, &color);
		fprintf(fp, "=%02x%02x%02x%02x", color.red, color.green, color.blue, color.alpha);
	}
	else
	{
		fprintf(fp, ":");
		if (qt->no)
		{
			fprintf(fp, "a%x", qt->no->n_node);
			print_delimiter_if_necessary(fp, qt->ne, qt->se, qt->so);
		}
		if (qt->ne)
		{
			fprintf(fp, "b%x", qt->ne->n_node);
			print_delimiter_if_necessary(fp, NULL, qt->se, qt->so);
		}
		if (qt->se)
		{
			fprintf(fp, "c%x", qt->se->n_node);
			print_delimiter_if_necessary(fp, NULL, NULL, qt->so);
		}
		if (qt->so)
			fprintf(fp, "d%x", qt->so->n_node);
	}
	fprintf(fp, "\n");
	encode_graph(qt->no, fp);
	encode_graph(qt->ne, fp);
	encode_graph(qt->se, fp);
	encode_graph(qt->so, fp);
}
