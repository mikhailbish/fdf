/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutuzov <mbutuzov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 18:39:49 by mbutuzov          #+#    #+#             */
/*   Updated: 2024/10/20 22:53:08 by mbutuzov         ###   ########.fr       */
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
typedef struct s_2d_point {
	int x;
	int y;
	int32_t color;
}	t_2d_point;

typedef struct s_3d_point {
	double x;
	double y;
	double z;
	int32_t color;
}	t_3d_point;

typedef struct s_map {
	void	**coords;
	int length;
	int width;
}	t_map;

typedef struct s_fdf {
	mlx_t	*mlx;
	char	*file_name;
	int	fd;
	int	painted;
	mlx_image_t	*image;
	t_map	image_size;
	t_map	dim;
}	t_fdf;
/*
typedef struct s_matrix {
	size_t length;
	size_t width;
	double **matrix;
} t_matrix;
*/

/*		VALIDATION		*/
t_map		validate_file(int fd);
t_map		validate_lines(t_list *lines);
/*		PARSING			*/
int		check_name(char *name);
t_map		get_data_from_fd(int fd);
t_list		*get_file_lines(int fd);
t_3d_point	**alloc_data_space(t_map dim);
t_map		parse_lines(t_map dim, t_list *lines);
int		fill_with_data(t_map dim, t_list *lines);

/*		PROCESSING		*/
void		process_data(t_map dim);
void		translate_angles(t_3d_point *point);
void		make_positive(t_map dim);//, t_point **coords);
void		extend_lines(t_3d_point *point, int num);

/*		DISPLAY			*/
void		display_data(t_map dim, mlx_image_t *image);
void 		put_lines(mlx_image_t *image, t_map dim);
//void 		display_coords_testing(t_map dim);
void		put_line_low(t_2d_point start, t_2d_point end, mlx_image_t *image);
void		put_line_high(t_2d_point start, t_2d_point end, mlx_image_t *image);
void		put_line(t_2d_point start, t_2d_point end, mlx_image_t *image);

/*		UTILS			*/
void		mutate_3d_vector(double vector[3], double matrix[3][3]);
double		get_radians(int angle);
int		count_split(char **texts);
void		free_split(char **args);
void		delete_content(void *content);
int32_t 	ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a);
int32_t		get_red(int32_t color);
int32_t		get_green(int32_t color);
int32_t		get_blue(int32_t color);
int		get_color(int start_color, int end_color, int i, int a, int b);

#endif
