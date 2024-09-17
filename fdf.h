/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutuzov <mbutuzov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 18:39:49 by mbutuzov          #+#    #+#             */
/*   Updated: 2024/09/17 20:41:54 by mbutuzov         ###   ########.fr       */
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
# include <math.h>

typedef struct s_ft_point {
	int x;
	int y;
	int z;
}	t_ft_point;

typedef struct s_dimensions {
	int	**plane;
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
t_dimensions	parse_lines(t_dimensions dim, t_list *lines);
void	fill_with_data(t_dimensions dim, t_ft_point **coordinates, t_list *lines);
t_ft_point	**alloc_data_space(t_dimensions dim);
double get_radians(int angle);
void translate_angles(t_ft_point *point);



#endif
