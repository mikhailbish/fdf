/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutuzov <mbutuzov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 18:39:49 by mbutuzov          #+#    #+#             */
/*   Updated: 2025/01/23 17:01:18 by mbutuzov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include "libft.h"
# include "MLX42.h"
# include <fcntl.h>
# include <stdio.h>
//TODO: TEst
# include <errno.h>
# include <math.h>
# include <string.h>
# ifndef WIDTH
#  define WIDTH 2732 
# endif
# ifndef HEIGHT
#  define HEIGHT 1536
# endif
# ifndef COLOR_LOW
#  define COLOR_LOW 0x4c9106
# endif
# ifndef COLOR_HIGH
#  define COLOR_HIGH 0xf23607
# endif

typedef struct s_2d_point {
	int32_t	x;
	int32_t	y;
	uint32_t	color;
}	t_2d_point;

typedef struct s_3d_point {
	double	x;
	double	y;
	double	z;
	uint32_t	color;
}	t_3d_point;

typedef struct s_map {
	t_3d_point	*coords_original;
	t_3d_point	*coords_3d;
	t_2d_point	*coords_display;
//TODO: replace with int32_t ?
	int			length;
	int			width;
	int32_t			max_z;
	int32_t			min_z;
	int32_t		max_x;
	int32_t		min_x;
	int32_t		max_y;
	int32_t		min_y;
	int			colors_specified;
}	t_map;

typedef struct s_fdf {
	mlx_t		*mlx;
	char		*file_name;
	int			fd;
	mlx_image_t	*aquarium;
	mlx_image_t	*image;
	int			painted;
	t_map		dim;
}	t_fdf;

/* local structs*/
typedef struct s_color {
	int32_t	red;
	int32_t	green;
	int32_t	blue;
}	t_color;

typedef struct s_line {
	int32_t	dx;
	int32_t	dy;
	int32_t	d;
	int32_t	step;
	uint32_t	color;
}	t_line;

/*		VALIDATION		*/
t_map		validate_file(int fd);
t_map		validate_lines(t_list *lines, t_map dim);
int			validate_and_open(char *file_name);

/*		PARSING			*/
int			check_name(char *name);
t_map		get_data_from_fd(int fd, t_fdf *ptr);
t_list		*get_file_lines(int fd);
t_map		*alloc_map_space(t_map *dim);
t_map		parse_lines(t_map dim, t_list *lines);
int			fill_with_data(t_map *dim, t_list *lines);
t_3d_point	get_3d_point(char *space_separated_val, int x,
				int y, int *color_spec);

/*		PROCESSING		*/
void		process_data(t_fdf *fdf);
void		translate_angles(t_3d_point *point);
void		extend_lines(t_3d_point *point, double num);
void		convert_3dto2d(t_map *dim);
void		set_basic_colors(t_map *dim);
void		set_max_min_y_3d(int *max_y_ptr, int *min_y_ptr, t_map dim);

/*		DISPLAY			*/
void		display_data(t_fdf *fdf);
void		put_lines(mlx_image_t *image, t_map dim);
void		put_lines_color(mlx_image_t *image, t_map dim, int32_t *color);
void		put_line_color(t_2d_point start, t_2d_point end,
				mlx_image_t *image, int32_t *color);
void		put_line(t_2d_point start, t_2d_point end, mlx_image_t *image);
void		paint_black_square(t_fdf fdf);

/*		UTILS_MATH			*/
void		mutate_3d_vector(double vector[3], double matrix[3][3]);
double		get_radians(double angle);

/*		UTILS			*/
int			count_split(char **texts);
void		free_split(char **args);
int32_t		ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a);
int			ft_abs(int num);
void		ft_free(void **adr);

/*		UTILS FDF			*/
void		free_fdf_parts(t_fdf fdf);
void		free_fdf_parts_and_exit_error(t_fdf fdf, char *error);

uint32_t		get_color(uint32_t start_color, uint32_t end_color,
				int32_t i, int32_t length);
t_fdf		fdf_init(char *file_name);
t_fdf		fdf_fill(t_fdf fdf);

#endif
