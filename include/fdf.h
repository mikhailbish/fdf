/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutuzov <mbutuzov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 18:39:49 by mbutuzov          #+#    #+#             */
/*   Updated: 2025/01/09 21:08:59 by mbutuzov         ###   ########.fr       */
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
//#define WIDTH 3840 
//#define HEIGHT 2160 
// TODO: REthink
#define WIDTH 1366 
#define HEIGHT 768 
//#define WIDTH 2732 
//#define HEIGHT 1536 
/*TODO: Create struct inits*/
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
	void	*coords_3d;
	void	*coords_display;
	int length;
	int width;
	int max_z;
	int min_z;
}	t_map;

typedef struct s_fdf {
	mlx_t	*mlx;
	char	*file_name;
	int	fd;
	int	painted;
	mlx_image_t	*image;
	t_map	dim;
}	t_fdf;

/* local structs*/
typedef struct s_color {
	int32_t red;
	int32_t green;
	int32_t blue;
}	t_color;

typedef struct s_line {
	int32_t dx;
	int32_t dy;
	int32_t d;
	int32_t step;
	int32_t color;
}	t_line;


/*		VALIDATION		*/
t_map		validate_file(int fd);
t_map		validate_lines(t_list *lines);
/*		PARSING			*/
int		check_name(char *name);
t_map		get_data_from_fd(int fd);
t_list		*get_file_lines(int fd);
t_map		*alloc_data_space(t_map *dim);
t_map		parse_lines(t_map dim, t_list *lines);
int		fill_with_data(t_map dim, t_list *lines);

/*		PROCESSING		*/
void		process_data(t_map *dim);
void		translate_angles(t_3d_point *point);
void		extend_lines(t_3d_point *point, double num);
void		convert_3dto2d(t_map *dim);

/*		DISPLAY			*/
void		display_data(t_map dim, mlx_image_t *image);
void 		put_lines(mlx_image_t *image, t_map dim);
void 		display_coords_testing(t_map dim);
void		put_line(t_2d_point start, t_2d_point end, mlx_image_t *image);

/*		UTILS_MATH			*/
void		mutate_3d_vector(double vector[3], double matrix[3][3]);
double		get_radians(double angle);
/*		UTILS			*/
int		count_split(char **texts);
void		free_split(char **args);
void		delete_content(void *content);
int32_t 	ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a);
int		ft_abs(int num);
void		ft_free(void **adr);
/*int32_t		get_red(int32_t color);
int32_t		get_green(int32_t color);
int32_t		get_blue(int32_t color);*/
int32_t		get_color(int32_t start_color, int32_t end_color, int32_t i, int32_t length);

#endif
