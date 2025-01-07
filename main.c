/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutuzov <mbutuzov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 18:24:15 by mbutuzov          #+#    #+#             */
/*   Updated: 2025/01/07 20:16:47 by mbutuzov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// -----------------------------------------------------------------------------
// Codam Coding College, Amsterdam @ 2022-2023 by W2Wizard.
// See README in the root project for more information.
// -----------------------------------------------------------------------------
/*
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
*/
#include "fdf.h"
// normal minilibx problems: 317955 bytes in 3106 blocks
//#define WIDTH 512
//#define HEIGHT 512

//#define WIDTH 1366 
//#define HEIGHT 768 


int32_t	ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

void	ft_hook(void* param)
{
//	mlx_t* mlx = param;
	t_fdf	*fdf = (t_fdf *)param;
//TODO: free up everything used
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(fdf->mlx);
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_UP))
		fdf->image->instances[0].y -= 5;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_DOWN))
		fdf->image->instances[0].y += 5;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_LEFT))
		fdf->image->instances[0].x -= 5;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_RIGHT))
		fdf->image->instances[0].x += 5;
}

// -----------------------------------------------------------------------------

int	ft_abs(int num)
{
	if (num < 0)
		return (-num);
	return (num);
}

int32_t	get_red(int32_t color)
{
	return ((color >> 16) & 0xFF);
}

int32_t	get_green(int32_t color)
{
	return ((color >> 8) & 0xFF);
}

int32_t	get_blue(int32_t color)
{
	return ((color) & 0xFF);
}


int	get_color(int start_color, int end_color, int i, int length)
{
	int	red_change;
	int	green_change;
	int	blue_change;
	int	final_red;
	int	final_green;
	int	final_blue;

	if (i == 0 || (start_color == end_color))
		return (start_color);
	if (i == length)
		return (end_color);
	red_change = get_red(end_color) - get_red(start_color);
	green_change = get_green(end_color) - get_green(start_color);
	blue_change = get_blue(end_color) - get_blue(start_color);
	final_red = get_red(start_color) + (i * (red_change)) / length;
	final_green = get_green(start_color) + (i * (green_change)) / length;
	final_blue = get_blue(start_color) + (i * (blue_change)) / length;
	return (final_red << 16 | final_green << 8 | final_blue);
}
/*
int	get_color(int start_color, int end_color, int i, int length)
{
	double	red_change;
	double	green_change;
	double	blue_change;
	int		final_red;
	int		final_green;
	int		final_blue;

	if (i == 0 || (start_color == end_color))
		return (start_color);
	if (i == length)
		return (end_color);
	red_change = ((double)get_red(end_color)  - (double)get_red(start_color))/(double)length;
	green_change = ((double)get_green(end_color)  - (double)get_green(start_color))/(double)length;;
	blue_change = ((double)get_blue(end_color) - (double)get_blue(start_color))/(double)length;
	// TODO: redo datatypes
	final_red = round((double)get_red(start_color) + ((double)i * (red_change)));
	final_green =round((double)get_green(start_color) + ((double)i * (green_change)));
	final_blue = round((double)get_blue(start_color) + ((double)i * (blue_change)));
	if (final_red < 0 || final_blue < 0 || final_green < 0)
		ft_printf("weird colors\n");
	return (final_red << 16 | final_green << 8 | final_blue);
}
*/
void	put_line_low(t_2d_point start, t_2d_point end, mlx_image_t *image)
{
	int	dx;
	int	dy;
	int	step_y;
	int	d;
	int	color;

	dx = end.x - start.x;
	dy = end.y - start.y;
	step_y = 1;
	if (dy < 0)
	{
		step_y = -1;
		dy = -dy;
	}
	d = (2 * dy) - dx;
	while (start.x <= end.x)
	{
		// TODO: modify color handling here
		color = get_color(start.color, end.color, start.x - (end.x - dx), dx);
//		color = 0xFFFFFF;
		mlx_put_pixel(image, start.x, start.y, (color << 8) + 0xFF);
		if (d > 0)	
		{
			start.y += step_y;
			d += 2 * (dy - dx);
		}
		else
			d += 2 * dy;
		start.x++;
	}
}

void	put_line_high(t_2d_point start, t_2d_point end, mlx_image_t *image)
{
	int	dx;
	int	dy;
	int	d;
	int	step_x;
	int	color;

	dx = end.x - start.x;
	dy = end.y - start.y;
	step_x = 1;
	if (dx < 0)
	{
		step_x = -1;
		dx = -dx;
	}
	d = (2 * dx) - dy;
	while (start.y <= end.y)
	{
		// TODO: modify color handling here
		color = get_color(start.color, end.color, start.y - (end.y - dy), dy);
//		color = 0xFFFFFF;
		mlx_put_pixel(image, start.x, start.y, (color << 8) + 0xFF);
		if (d > 0)	
		{
			start.x += step_x;
			d += 2 * (dx - dy);
		}
		else
			d += 2 * dx;
		start.y++;
	}
}

void	put_line(t_2d_point start, t_2d_point end, mlx_image_t *image)
{
	if (ft_abs(end.y - start.y) < ft_abs(end.x - start.x))
	{
		if (start.x > end.x)
			put_line_low(end, start, image);
		else
			put_line_low(start, end, image);
	}
	else
	{
		if (start.y > end.y)
			put_line_high(end, start, image);
		else
			put_line_high(start, end, image);
	}
}

void	put_lines(mlx_image_t *image, t_map dim)
{
	int		y;
	int		x;
	t_2d_point	*coords;

	coords = (t_2d_point *)dim.coords_display;
	y = 0;
	int	line_count = 0;
	while(y < dim.length )
	{
		x = dim.width - 1;
		while(x > - 1)
		{
			if (x == 0 && y < dim.length - 1)
			{
	//			ft_printf("case 1\n");
				put_line(coords[y * dim.width + x], coords[(y + 1) * dim.width + x], image);
				line_count +=1;
	//			ft_printf("case 1 ended\n");
			}
			else if ((x < (dim.width - 1)) && (y == (dim.length - 1)))
			{
	//			ft_printf("case 2\n");
				put_line(coords[y * dim.width + x], coords[y * dim.width + x + 1], image);
				line_count +=1;
	//			ft_printf("case 2 ended\n");
			}
			else if ((x == (dim.width - 1)) && (y == (dim.length - 1)))
			{
	//			ft_printf("case 3 ended\n");
			}
			else {
	//			ft_printf("case 4\n");
	//			if ((y + 1) < (dim.length - 1))
					put_line(coords[y * dim.width + x], coords[(y + 1) * dim.width + x], image);
	//			if (x > 0)
					put_line(coords[y * dim.width + x - 1], coords[y * dim.width + x], image);
				line_count +=2;
	//			ft_printf("case 4 ended\n");
			}
			x--;
		}
		y++;
	}
}
void	put_42_v2(void *param)
{
	t_map	dim;
	//t_map image_size;
	mlx_image_t	*image;
	int	painted;

	painted = ((t_fdf *)param)->painted;
	if (!painted)
	{
		dim = ((t_fdf *)param)->dim;
	//	image_size = ((t_fdf *)param)->image_size;
		image = ((t_fdf *)param)->image;
		ft_printf("before display data");
		//display_coords_testing(dim);
		display_data(dim, image);
		((t_fdf *)param)->painted = 1;
	}
}

//TODO: remove

void	display_coords_testing(t_map dim)
{
	int	i = 0;
	int	max = dim.length * dim.width;
//	t_2d_point **coords;
	t_3d_point *coords;
	coords = (t_3d_point *)dim.coords_3d;
	printf("display coords testing:\n");
	while (i < max)
	{
		printf("x: %F, y: %F, z: %F, color: %dx\n", coords[i].x, coords[i].y, coords[i].z, coords[i].color);
		i++;
	}
}

#include <stdio.h>
#include <sys/time.h>
float timedifference_msec(struct timeval t0, struct timeval t1)
{
    return (t1.tv_sec - t0.tv_sec) * 1000.0f + (t1.tv_usec - t0.tv_usec) / 1000.0f;
}
int32_t	main(int argc, char **argv)
{
	int		fd;
	mlx_image_t*	image;
	t_map	dim;
	if (argc != 2)
		return (EXIT_FAILURE);
	mlx_t*	mlx;
	t_fdf	some;
	fd = open(*(++argv), O_RDONLY);
	if (fd < 0)
	{
		ft_printf("File name doesn't exist\n");
		return(0);
	}
	dim = get_data_from_fd(fd);
	///display_coords_testing(dim);

	ft_printf("done parsing\n");

	//TODO: close in the middle if error
	close(fd);
	struct timeval t0;
	struct timeval t1;
	float elapsed;
	gettimeofday(&t0, 0);
	process_data(&dim);
	gettimeofday(&t1, 0);
	elapsed = timedifference_msec(t0,t1);
	printf("p d seconds %f\n", elapsed);
	ft_printf("done processing, width: %d, length: %d\n", dim.width, dim.length);
	ft_printf("before mlx init\n");
	// Gotta error check this stuff
	if (!(mlx = mlx_init(WIDTH, HEIGHT, "MLX42", true)))
	{
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	ft_printf("before new image\n");
	if (!(image = mlx_new_image(mlx, WIDTH, HEIGHT)))
	{
		mlx_close_window(mlx);
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	ft_printf("before image to window\n");
	if (mlx_image_to_window(mlx, image, 0, 0) == -1)
	{
		mlx_close_window(mlx);
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	//ft_bzero(image->pixels, image->height * image->width);
	
	ft_memset(image->pixels, 0, image->height * image->width * sizeof(int32_t));
	some.mlx = mlx;
	some.image = image;
	//TODO: remove file name here and in the header
	some.file_name = *(argv);
	some.image = image;
	some.dim = dim;
	some.painted = 0;
	ft_printf("before hook");
	mlx_loop_hook(mlx, put_42_v2, &some);
	mlx_loop_hook(mlx, ft_hook, &some);
	mlx_loop(mlx);
	mlx_terminate(mlx);

	return (EXIT_SUCCESS);
}
