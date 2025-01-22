/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutuzov <mbutuzov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 18:06:45 by mbutuzov          #+#    #+#             */
/*   Updated: 2025/01/22 20:48:15 by mbutuzov         ###   ########.fr       */
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
// normal MLX42 problems: 317955 bytes in 3106 blocks
//#define WIDTH 512
//#define HEIGHT 512

//#define WIDTH 1366 
//#define HEIGHT 768 

//TODO: remove movement?
//TODO: make sure int to double conversions are done with some kind of round function
void	ft_controls_hook(void *param)
{
	t_fdf	*fdf;

	fdf = (t_fdf *)param;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_ESCAPE))
	{
		mlx_close_window(fdf->mlx);
		free_fdf_parts(*fdf);
		exit(0);
	}
}

t_2d_point	get_2d_coord(t_map dim, int x, int y)
{
	t_2d_point	*coords;

	coords = (t_2d_point *)dim.coords_display;
	return (coords[y * dim.width + x]);
}

int	put_line_order(t_map dim, mlx_image_t *image, int x, int y)
{
	int			line_count;

	line_count = 0;
	if (x == 0 && y < dim.length - 1)
	{
		put_line(get_2d_coord(dim, x, y),
			get_2d_coord(dim, x, y + 1), image);
		line_count += 1;
	}
	else if ((x < (dim.width - 1)) && (y == (dim.length - 1)))
	{
		put_line(get_2d_coord(dim, x, y),
			get_2d_coord(dim, x + 1, y), image);
		line_count += 1;
	}
	else if (!((x == (dim.width - 1)) && (y == (dim.length - 1))))
	{
		put_line(get_2d_coord(dim, x, y),
			get_2d_coord(dim, x, y + 1), image);
		put_line(get_2d_coord(dim, x - 1, y),
			get_2d_coord(dim, x, y), image);
		line_count += 2;
	}
	return (line_count);
}

int	put_line_order_color(t_map dim, mlx_image_t *image,
		int coord[2], int32_t *color)
{
	int			line_count;

	line_count = 0;
	if (coord[0] == 0 && coord[1] < dim.length - 1)
	{
		put_line_color(get_2d_coord(dim, coord[0], coord[1]),
			get_2d_coord(dim, coord[0], coord[1] + 1), image, color);
		line_count += 1;
	}
	else if ((coord[0] < (dim.width - 1)) && (coord[1] == (dim.length - 1)))
	{
		put_line_color(get_2d_coord(dim, coord[0], coord[1]),
			get_2d_coord(dim, coord[0] + 1, coord[1]), image, color);
		line_count += 1;
	}
	else if (!((coord[0] == (dim.width - 1)) && (coord[1] == (dim.length - 1))))
	{
		put_line_color(get_2d_coord(dim, coord[0], coord[1]),
			get_2d_coord(dim, coord[0], coord[1] + 1), image, color);
		put_line_color(get_2d_coord(dim, coord[0] - 1, coord[1]),
			get_2d_coord(dim, coord[0], coord[1]), image, color);
		line_count += 2;
	}
	return (line_count);
}

void	put_lines(mlx_image_t *image, t_map dim)
{
	int	y;
	int	x;
	int	line_count;

	line_count = 0;
	y = 0;
	while (y < dim.length)
	{
		x = dim.width - 1;
		while (x > -1)
		{
			line_count += put_line_order(dim, image, x, y);
			x--;
		}
		y++;
	}
}

void	put_lines_color(mlx_image_t *image, t_map dim, int32_t *color)
{
	int	coord[2];
	int	line_count;

	line_count = 0;
	coord[1] = 0;
	while (coord[1] < dim.length)
	{
		coord[0] = dim.width - 1;
		while (coord[0] > -1)
		{
			line_count += put_line_order_color(dim, image, coord, color);
			coord[0]--;
		}
		coord[1]++;
	}
}

void	put_42_v2(void *param)
{
	t_fdf		*fdf;

	fdf = (t_fdf *)param;
	if (!fdf->painted && fdf->image)
	{
		process_data(fdf);
		display_data(fdf);
		fdf->painted = 1;
	}
}

void	close_window_cb(void *param)
{
	t_fdf	*fdf;

	fdf = (t_fdf *)param;
	free_fdf_parts(*fdf);
	exit(0);
}

void	mlx_resize_cb(int32_t width, int32_t height, void *param)
{
	t_fdf		*fdf;
	uint32_t	uwidth;
	uint32_t	uheight;
	mlx_image_t	*image;
	int32_t		color;

	uwidth = (uint32_t)width;
	uheight = (uint32_t)height;
	fdf = (t_fdf *)param;
	color = 0;
	put_lines_color(fdf->image, fdf->dim, &color);
	if (fdf->image->width < uwidth || fdf->image->height < uheight)
	{
		image = fdf->image;
		fdf->image = 0;
		mlx_delete_image(fdf->mlx, image);
		fdf->image = mlx_new_image(fdf->mlx, uwidth, uheight);
		mlx_image_to_window(fdf->mlx, fdf->image, 0, 0);
		fdf->painted = 0;
	}
	else
		fdf->painted = 0;
}

int32_t	main(int argc, char **argv)
{
	t_fdf	fdf;

	if (argc != 2)
		return (EXIT_FAILURE);
	fdf = fdf_init(*(argv + 1));
	fdf.fd = validate_and_open(fdf.file_name);
	if (fdf.fd == -1)
		free_fdf_parts_and_exit_error(fdf, "validate and open err\n");
	fdf.dim = get_data_from_fd(fdf.fd, &fdf);
	if (fdf.dim.width == -1)
		free_fdf_parts_and_exit_error(fdf, "get data from fd err\n");
	fdf = fdf_fill(fdf);
	mlx_loop_hook(fdf.mlx, put_42_v2, &fdf);
	mlx_loop_hook(fdf.mlx, ft_controls_hook, &fdf);
	mlx_close_hook(fdf.mlx, close_window_cb, &fdf);
	mlx_resize_hook(fdf.mlx, mlx_resize_cb, &fdf);
	mlx_loop(fdf.mlx);
	mlx_terminate(fdf.mlx);
	return (EXIT_SUCCESS);
}
