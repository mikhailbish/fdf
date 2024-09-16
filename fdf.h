/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutuzov <mbutuzov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 18:39:49 by mbutuzov          #+#    #+#             */
/*   Updated: 2024/09/16 22:23:43 by mbutuzov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include "libft.h"
# include <MLX42/MLX42.h>
# include <fcntl.h>
# include <stdio.h>
//TODO: TEst
# include <errno.h>

typedef struct s_ft_point {
	int x;
	int y;
	int z;
}	t_ft_point;

typedef struct s_dimensions {
	int length;
	int width;
}	t_dimensions;



int	check_name(char *name);
int	count_split(char **texts);
void	free_split(char **args);
t_dimensions validate_file(int fd);
void	delete_content(void *content);
t_list	*get_file_lines(int fd);
t_dimensions validate_lines(t_list *lines);



#endif
