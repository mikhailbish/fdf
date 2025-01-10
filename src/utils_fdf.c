/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_fdf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutuzov <mbutuzov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 20:56:05 by mbutuzov          #+#    #+#             */
/*   Updated: 2025/01/10 22:31:11 by mbutuzov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
// TODO: what is a last param, why true?

t_fdf fdf_init(char *file_name)
{
	t_fdf fdf;

	fdf.mlx = 0;
	fdf.file_name = file_name;
	fdf.fd = -1;
	fdf.image = 0;
	fdf.dim.width = 0;
	fdf.dim.coords_3d = 0;
	fdf.dim.coords_display = 0;
	return (fdf);
}

int validate_and_open(char *file_name)
{
	if (check_name(file_name))
	{
		//TODO: add directory check
		return (open(file_name, O_RDONLY));
	}
	return (-1);
}

void free_fdf_parts(t_fdf fdf)
{
	if (fdf.mlx)
	{}
	if (fdf.image)
	{}
	if (fdf.dim.coords_3d)
		free(fdf.dim.coords_3d);
	if (fdf.dim.coords_display)
		free(fdf.dim.coords_display);
	//TODO: free all
}
// TODO: finish
// restructuring wip
t_fdf fdf_fill(t_fdf fdf)
{
	fdf.mlx = mlx_init(WIDTH, HEIGHT, "FDF", true);
	if (!fdf.mlx)
	{
		free_fdf_parts(fdf);
		exit(1);
	}
	fdf.image = mlx_new_image(fdf.mlx, WIDTH, HEIGHT);
	if (!fdf.image)
	{
		free_fdf_parts(fdf);
		exit(1);
	}
	if (mlx_image_to_window(fdf.mlx, fdf.image, 0, 0) == -1)
	{
		free_fdf_parts(fdf);
		exit(1);
	}
	fdf.fd = validate_and_open(fdf.file_name);
	if (fdf.fd == -1)
	{
		free_fdf_parts(fdf);
		exit(1);
	}
	fdf.dim = get_data_from_fd(fdf.fd, &fdf);
	if (fdf.dim.width == -1)
	{
		free_fdf_parts(fdf);
		exit(1);
	}
/*
	if (!alloc_map_space(&(fdf.dim)))
	{
		free_fdf_parts(fdf);
		exit(1);
	}*/
	return fdf;
}
