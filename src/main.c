/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutuzov <mbutuzov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 18:24:15 by mbutuzov          #+#    #+#             */
/*   Updated: 2025/01/09 21:35:13 by mbutuzov         ###   ########.fr       */
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

//TODO: free up everything used
void	ft_hook(void *param)
{
	t_fdf	*fdf;

	fdf = (t_fdf *)param;
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
	process_data(&dim);
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
	//TODO: restructure
	//display_data(dim, image);
	ft_printf("before image to window\n");
	if (mlx_image_to_window(mlx, image, 0, 0) == -1)
	{
		mlx_close_window(mlx);
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	//ft_bzero(image->pixels, image->height * image->width);
	//TODO: make it black
	//ft_memset(image->pixels, 0, image->height * image->width * sizeof(int32_t));

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
