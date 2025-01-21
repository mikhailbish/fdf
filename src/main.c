/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutuzov <mbutuzov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 18:06:45 by mbutuzov          #+#    #+#             */
/*   Updated: 2025/01/21 17:00:16 by mbutuzov         ###   ########.fr       */
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
		ft_printf("before free fdf parts\n");
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

int	put_line_order_color(t_map dim, mlx_image_t *image, int x, int y, int32_t *color)
{
	int			line_count;

	line_count = 0;
	if (x == 0 && y < dim.length - 1)
	{
		put_line_color(get_2d_coord(dim, x, y),
			get_2d_coord(dim, x, y + 1), image, color);
		line_count += 1;
	}
	else if ((x < (dim.width - 1)) && (y == (dim.length - 1)))
	{
		put_line_color(get_2d_coord(dim, x, y),
			get_2d_coord(dim, x + 1, y), image, color);
		line_count += 1;
	}
	else if (!((x == (dim.width - 1)) && (y == (dim.length - 1))))
	{
		put_line_color(get_2d_coord(dim, x, y),
			get_2d_coord(dim, x, y + 1), image, color);
		put_line_color(get_2d_coord(dim, x - 1, y),
			get_2d_coord(dim, x, y), image, color);
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
			line_count += put_line_order_color(dim, image, x, y, color);
			x--;
		}
		y++;
	}
}

//TODO: remove
void	fdf_print_status(t_fdf fdf)
{
	ft_printf("mlx pointer: %p\n", fdf.mlx);
	ft_printf("file name: %s\n", fdf.file_name);
	ft_printf("fd: %d\n", fdf.fd);
	ft_printf("image pointer: %p\n", fdf.image);
	ft_printf("image painted: %d\n", fdf.painted);
	ft_printf("dim length: %d\n", fdf.dim.length);
	ft_printf("dim width: %d\n", fdf.dim.width);
	ft_printf("dim coords3d: %p\n", fdf.dim.coords_3d);
	ft_printf("dim coords display: %p\n", fdf.dim.coords_display);
	ft_printf("dim max z: %d\n", fdf.dim.max_z);
	ft_printf("dim min z: %d\n", fdf.dim.min_z);
}

void	put_42_v2(void *param)
{
	t_fdf		*fdf;
//	mlx_image_t	*image;

	fdf = (t_fdf *)param;
//	image = fdf->image;
	if (!fdf->painted && fdf->image)
	{
		//process_data(&(fdf->dim));
		process_data(fdf);
		printf("--------------------------------fdf status after pd\n");
		fdf_print_status(*fdf);
		display_data(fdf);//, image);
		printf("--------------------------------fdf status after dd\n");
		fdf_print_status(*fdf);
		fdf->painted = 1;
	}
}

//TODO: remove before finish
void	display_coords_testing(t_map dim)
{
	int	i = 0;
	int	max = dim.length * dim.width;
	t_3d_point *coords;
	coords = dim.coords_3d;
	ft_printf("display coords testing:\n");
	while (i < max)
	{
		ft_printf("x: %F, y: %F, z: %F, color: %dx\n", coords[i].x, coords[i].y, coords[i].z, coords[i].color);
		i++;
	}
}

void	close_window_cb(void *param)
{
	t_fdf	*fdf;

	fdf = (t_fdf *)param;
	free_fdf_parts(*fdf);
	exit(0);
}

//TODO: add on resize logic (resize image, rerender coords)
// TODO: think thought why size params are not unsigned
// TODO: can i do it on "resize end"?
void mlx_resize_cb(int32_t width, int32_t height, void *param)
{
	t_fdf	*fdf;
	uint32_t	uwidth;
	uint32_t	uheight;
	mlx_image_t	*image;
	int32_t	color;

	uwidth = (uint32_t)width;
	uheight = (uint32_t)height;
	fdf = (t_fdf *)param;
	color = 0;
	put_lines_color(fdf->image, fdf->dim, &color);
	
	if (fdf->image->width < uwidth || fdf->image->height < uheight)
	{
		// clear image
//error checks
		image = fdf->image;
		fdf->image = 0;
		mlx_delete_image(fdf->mlx, image);
		fdf->image = mlx_new_image(fdf->mlx, uwidth, uheight);
		mlx_image_to_window(fdf->mlx, fdf->image, 0, 0);
//		mlx_resize_image(fdf->image, uwidth, uheight);
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
	fdf = fdf_fill(fdf);
	fdf.fd = validate_and_open(fdf.file_name);
	if (fdf.fd == -1)
		free_fdf_parts_and_exit_error(fdf, "validate and open err\n");
	fdf.dim = get_data_from_fd(fdf.fd, &fdf);
	printf("--------------------------------fdf status after get_data from fd\n");
	if (fdf.dim.width == -1)
		free_fdf_parts_and_exit_error(fdf, "get data from fd err\n");
	fdf_print_status(fdf);
	mlx_loop_hook(fdf.mlx, put_42_v2, &fdf);
	mlx_loop_hook(fdf.mlx, ft_controls_hook, &fdf);
	mlx_close_hook(fdf.mlx, close_window_cb, &fdf);
	mlx_resize_hook(fdf.mlx, mlx_resize_cb, &fdf);
	mlx_loop(fdf.mlx);
	mlx_terminate(fdf.mlx);
	return (EXIT_SUCCESS);
}
