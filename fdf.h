/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutuzov <mbutuzov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 18:39:49 by mbutuzov          #+#    #+#             */
/*   Updated: 2024/10/04 20:20:59 by mbutuzov         ###   ########.fr       */
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
# include <string.h>
typedef struct s_ft_point {
	int x;
	int y;
	int z;
}	t_ft_point;

typedef struct s_dimensions {
	t_ft_point	**coords;
	int length;
	int width;
}	t_dimensions;

typedef struct s_name_holder {
	mlx_t	*mlx;
	char	*file_name;
	int	fd;
	mlx_image_t	*image;
	t_dimensions	image_size;
	t_dimensions	dim;
}	t_name_holder;

int	check_name(char *name);
int	count_split(char **texts);
void	free_split(char **args);
t_dimensions validate_file(int fd);
void	delete_content(void *content);
t_list	*get_file_lines(int fd);
t_dimensions validate_lines(t_list *lines);
t_dimensions	parse_lines(t_dimensions dim, t_list *lines);
int	fill_with_data(t_dimensions dim, t_ft_point **coordinates, t_list *lines);
t_ft_point	**alloc_data_space(t_dimensions dim);
double	get_radians(int angle);
void	translate_angles(t_ft_point *point, double factor);
//void	translate_angles(t_ft_point *point);
void	mutate_3d_vector(double vector[3], double matrix[3][3]);
void	extend_lines(t_ft_point *point, int num);
void	make_positive(t_dimensions dim, t_ft_point **coords);
t_dimensions	get_data_from_fd(int fd);
void	process_data(t_dimensions dim);
void	display_data(t_dimensions dim, t_dimensions image_size, mlx_image_t *image);
int32_t ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a);
void put_lines(mlx_image_t *image, t_dimensions dim, t_ft_point **coords);


#endif
