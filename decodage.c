#include "includes/quadtree.h"

uint8_t     convert_to_dec(FILE *fp)
{
    char        bin[8];
    char        *binPtr;
    int         i;
    int         total;

    total = 0;
	i = 0;
    while (i < 8)
    {
		fread(&bin[i], 1, 1, fp);
		/*printf("%d", bin[i]);*/
        i++;
    }
    i = 0;
    binPtr = &bin[0];
    while (i < 8)
    {
        total *= 2;
        if (*binPtr++ == 1)
            total += 1;
        i++;
    }
    return ((uint8_t)total);
}

t_color	   start_gen_color(FILE *fp)
{
    t_color color;

    color.red = convert_to_dec(fp);
    /*printf("][");*/
    color.green = convert_to_dec(fp);
    /*printf("][");*/
    color.blue = convert_to_dec(fp);
    /*printf("][");*/
    color.alpha = convert_to_dec(fp);
    return (color);
}

void       decode_bin(t_qt **qt, FILE *fp)
{
    t_color color;
	char	c;

    if (feof(fp))
        return ;
	fread(&c, 1, 1, fp);
    *qt = create_tree();
	if (c == 0)
    {
        /*printf("0");*/
        decode_bin(&(*qt)->no, fp);
        decode_bin(&(*qt)->ne, fp);
        decode_bin(&(*qt)->se, fp);
        decode_bin(&(*qt)->so, fp);
    }
    else
    {
        color = start_gen_color(fp);
        (*qt)->color = MLV_convert_rgba_to_color(color.red, color.green, color.blue, color.alpha);
		/*printf("]\n");*/
        return ;
    }
}

MLV_Color	gen_black_or_white(FILE *fp)
{
	char	c;

	fread(&c, 1, 1, fp);
	if (c == 0)
		return (MLV_COLOR_BLACK);
	return (MLV_COLOR_WHITE);
}

void       	decode_bin_nocolor(t_qt **qt, FILE *fp)
{
	char	c;

    if (feof(fp))
        return ;
	fread(&c, 1, 1, fp);
    *qt = create_tree();
	if (c == 0)
    {
        decode_bin_nocolor(&(*qt)->no, fp);
        decode_bin_nocolor(&(*qt)->ne, fp);
        decode_bin_nocolor(&(*qt)->se, fp);
        decode_bin_nocolor(&(*qt)->so, fp);
    }
    else
    {
        (*qt)->color = gen_black_or_white(fp);
        return ;
    }
}
