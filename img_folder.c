#include "includes/quadtree.h"
#include "includes/get_next_line.h"
#include "includes/err.h"

static char		*get_path(const char *str)
{
	char	*path;

	if (!str)
		return (ft_strdup("lion.png")); /* image par defaut */
	path = (char*)malloc(sizeof(char) * (strlen(str) + 5));
	if (!path)
		malloc_handling();
	strcpy(path, "img/");
	strcat(path, str);
	return (path);
}

static char		**alloc_path()
{
	DIR *folder;
	int		nb_img;
	char	**ret;
	struct dirent *file;

	folder = opendir("img/");
	if (!folder)
		err_what(IMG_NOT_FOUND);
	nb_img = 0;
	while ((file = readdir(folder)))
		nb_img++;
	ret = (char**)malloc(sizeof(char*) * nb_img);
	if (!ret)
		malloc_handling();
	closedir(folder);
	return (ret);
}

static char		**check_folder(int *nb_img)
{
	char **path;
	DIR	*folder;
	struct dirent* file;
	int i;

	i = 0;
	file = NULL;
	path = alloc_path();
	folder = opendir("img/");
	if (!folder)
		err_what(IMG_NOT_FOUND);
	while ((file = readdir(folder)))
	{
		if (file->d_name && file->d_name[0]
			&& strcmp(file->d_name, "..") != 0
			&& !(file->d_name[0] == '.') && is_img(file->d_name))
		{
			path[i] = get_path(file->d_name);
			i++;
		}
	}
	path[i] = NULL;
	*nb_img = i;
	closedir(folder);
	return (path);
}

static void		display_img_selection(char **path, int nb_img)
{
 	MLV_Image *img;
 	int i;

 	i = 0;
 	while (i < nb_img)
 	{
		img = MLV_load_image(path[i]);
		MLV_resize_image(img, 128, 128);
		MLV_draw_image(img, (i % 4) * 128, (i / 4) * 128);
		MLV_free_image(img);
		i++;
	}
	MLV_actualise_window();
}

char		*start_screen(void)
{
	char	**path;
	int		nb_img;
	int		i;
	int		x;
	int		y;

	x = 0;
	y = 0;
	i = 0;
	nb_img = 0;
	path = check_folder(&nb_img);
	display_img_selection(path, nb_img);
	MLV_wait_mouse(&x, &y);
	i = (x / 128) + (y / 128) * 4;
	if (i > nb_img)
		i = 0;
	MLV_clear_window(MLV_COLOR_BLACK);
	return (path[i]);
}
