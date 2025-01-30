/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutuzov <mbutuzov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 18:06:45 by mbutuzov          #+#    #+#             */
/*   Updated: 2025/01/30 18:28:06 by mbutuzov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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

void	process_and_display(void *param)
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
	uint32_t	color;

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
		if (!fdf->image)
			free_fdf_parts_and_exit_error(*fdf, "Can't realoc new image\n");
		if (mlx_image_to_window(fdf->mlx, fdf->image, 0, 0) == -1)
			free_fdf_parts_and_exit_error(*fdf, "Image to window fail\n");
		reset_background_image(uwidth, uheight, fdf);
	}
	fdf->painted = 0;
}

int32_t	main(int argc, char **argv)
{
	t_fdf	fdf;

	if (argc != 2)
	{
		ft_putstr_fd("Usage: ./fdf <path_to_.fdf_file>", 2);
		return (EXIT_FAILURE);
	}
	fdf = fdf_init(*(argv + 1));
	fdf.fd = validate_and_open(fdf.file_name);
	if (fdf.fd == -1)
		free_fdf_parts_and_exit_error(fdf, "Can't open .fdf file\n");
	fdf.dim = get_data_from_fd(fdf.fd, &fdf);
	if (fdf.dim.width == -1)
		free_fdf_parts_and_exit_error(fdf,
			"Can't get meaningful data from file\n");
	fdf = fdf_fill(fdf);
	if (!(mlx_loop_hook(fdf.mlx, process_and_display, &fdf)
			&& mlx_loop_hook(fdf.mlx, ft_controls_hook, &fdf)))
		free_fdf_parts_and_exit_error(fdf, "MLX hook set up fail\n");
	mlx_close_hook(fdf.mlx, close_window_cb, &fdf);
	mlx_resize_hook(fdf.mlx, mlx_resize_cb, &fdf);
	mlx_loop(fdf.mlx);
	mlx_terminate(fdf.mlx);
	return (EXIT_SUCCESS);
}
