/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutuzov <mbutuzov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 18:24:15 by mbutuzov          #+#    #+#             */
/*   Updated: 2025/01/14 18:25:45 by mbutuzov         ###   ########.fr       */
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

//TODO: free up everything used
void	ft_hook(void *param)
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
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_UP))
		fdf->image->instances[0].y -= 5;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_DOWN))
		fdf->image->instances[0].y += 5;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_LEFT))
		fdf->image->instances[0].x -= 5;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_RIGHT))
		fdf->image->instances[0].x += 5;
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
				put_line(coords[y * dim.width + x], coords[(y + 1) * dim.width + x], image);
				line_count +=1;
			}
			else if ((x < (dim.width - 1)) && (y == (dim.length - 1)))
			{
				put_line(coords[y * dim.width + x], coords[y * dim.width + x + 1], image);
				line_count +=1;
			}
			else if (!((x == (dim.width - 1)) && (y == (dim.length - 1))))
			{
				put_line(coords[y * dim.width + x], coords[(y + 1) * dim.width + x], image);
				put_line(coords[y * dim.width + x - 1], coords[y * dim.width + x], image);
				line_count +=2;
			}
			x--;
		}
		y++;
	}
}

void	put_42_v2(void *param)
{
	t_fdf *fdf = (t_fdf *)param;
	t_map	dim;
	//t_map image_size;
	mlx_image_t	*image;
	image = fdf->image;
	dim = fdf->dim;

	if (!fdf->painted)
	{
		process_data(&(fdf->dim));
		display_data(dim, image);
		fdf->painted = 1;
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
	ft_printf("display coords testing:\n");
	while (i < max)
	{
		ft_printf("x: %F, y: %F, z: %F, color: %dx\n", coords[i].x, coords[i].y, coords[i].z, coords[i].color);
		i++;
	}
}

int32_t	main(int argc, char **argv)
{
	t_fdf	fdf;
	if (argc != 2)
		return (EXIT_FAILURE);

	fdf = fdf_init(*(argv + 1));
	fdf = fdf_fill(fdf);
	mlx_loop_hook(fdf.mlx, put_42_v2, &fdf);
	mlx_loop_hook(fdf.mlx, ft_hook, &fdf);
	mlx_loop(fdf.mlx);
	mlx_terminate(fdf.mlx);

	return (EXIT_SUCCESS);
}
