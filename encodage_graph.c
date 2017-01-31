#include "includes/quadtree.h"
#include "includes/err.h"

void 		hub_encode_graph(t_qt *qt, const char *name, int color)
{
	FILE 			*fp;
    char 			*filename;

	printf("Encodage en graph ");
	if (color == COLOR)
	{
		filename = add_ext_to_filename(name, ".gmc");
		printf("en couleur...\n");
	}
	else
	{
		filename = add_ext_to_filename(name, ".gmn");
		printf("en noir et blanc...\n");
	}
    fp = fopen(filename, "w");
    if (!fp)
        err_what(FILE_ISSUE);
	if (color == COLOR)
		encode_graph(qt, fp);
	else
		encode_graph_nocolor(qt, fp);
	free(filename);
	fclose(fp);
	printf("Encodage terminé\n");
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

void 		encode_graph_nocolor(t_qt *qt, FILE *fp)
{
	if (!qt)
		return ;
	fprintf(fp, "%x", qt->n_node);
	if (is_leaf(qt))
	{
		if (color_equal(MLV_COLOR_BLACK, qt->color, 50))
			fprintf(fp, "=0");
		else
			fprintf(fp, "=1");
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
	encode_graph_nocolor(qt->no, fp);
	encode_graph_nocolor(qt->ne, fp);
	encode_graph_nocolor(qt->se, fp);
	encode_graph_nocolor(qt->so, fp);
}
