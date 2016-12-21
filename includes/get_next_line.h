/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishafie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/24 16:40:55 by ishafie           #+#    #+#             */
/*   Updated: 2016/04/03 04:36:20 by ishafie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# define BUFF_SIZE 32

int						get_next_line(int const fd, char **line);
void					*ft_memalloc(size_t size);
char					*ft_strdup(const char *s1);

typedef struct			s_struct
{
	char				*b1;
	char				*b2;
	int					fd;
	struct s_struct		*next;
	struct s_struct		*prev;
}						t_struct;

#endif
