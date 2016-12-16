#include "generique.h"

int		first_file(void *file)
{
	char	buf[256];
	size_t	nbchar;
	
	getline(&buf, &nbchar, (FILE*)file);
	return (1);
}

int		next_file(void *previous)
{
	char	buf[256];
	size_t	nbchar;
	
	if (!feof((FILE*)previous))
	{
		getline(&buf, &nbchar, (FILE*)previous);
		return (1);
	}
	return (0);
}

void	print_file(void *file)
{
	char	c;
	
	while (!feof((FILE*)file))
	{
		c = fgetc((FILE*)file);
		write(1, &c, 1); 
	}
}
