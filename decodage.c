#include "includes/quadtree.h"

void        convert_to_dec(uint8_t c, unsigned char **buf, int *i)
{
    /*
        TODO
    */
}

void	   start_gen_color(unsigned char *code, int *i)
{
    /*
        TODO
    */
}

void       decode(t_qt **qt, unsigned char *code, int i, int max)
{
    if (i >= max || !code)
        return ;
	if (code[i] == 0)
    {
        *qt = create_tree();
    }
    else
    {
        start_gen_color(code, &i);
    }
    i++;
    decode(&(*qt)->no, code, i, max);
    decode(&(*qt)->ne, code, i, max);
    decode(&(*qt)->se, code, i, max);
    decode(&(*qt)->so, code, i, max);
}
