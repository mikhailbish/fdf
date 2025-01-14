/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_fdf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutuzov <mbutuzov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 20:56:05 by mbutuzov          #+#    #+#             */
/*   Updated: 2025/01/14 20:17:49 by mbutuzov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_fdf	fdf_init(char *file_name)
{
	t_fdf	fdf;

	fdf.mlx = 0;
	fdf.file_name = file_name;
	fdf.fd = -1;
	fdf.image = 0;
	fdf.dim.width = 0;
	fdf.dim.length = 0;
	fdf.dim.coords_3d = 0;
	fdf.dim.coords_display = 0;
	fdf.painted = 0;
	return (fdf);
}

int	validate_and_open(char *file_name)
{
	if (check_name(file_name))
		return (open(file_name, O_RDONLY));
	return (-1);
}

void	free_fdf_parts(t_fdf fdf)
{
	ft_printf("before close fd\n");
	if (fdf.fd != -1)
		close(fdf.fd);
	ft_printf("before free image\n");
	if (fdf.image)
		mlx_delete_image(fdf.mlx, fdf.image);
	ft_printf("before free mlx\n");
	if (fdf.mlx)
		mlx_terminate(fdf.mlx);
	ft_printf("before free coords3d\n");
	if (fdf.dim.coords_3d)
		free(fdf.dim.coords_3d);
	ft_printf("before free coords_display\n");
	if (fdf.dim.coords_display)
		free(fdf.dim.coords_display);
}

void	free_fdf_parts_and_exit_error(t_fdf fdf, char *error)
{
	free_fdf_parts(fdf);
	if (error)
		ft_putstr_fd(error, 2);
	exit(1);
}

t_fdf	fdf_fill(t_fdf fdf)
{
	fdf.mlx = mlx_init(WIDTH, HEIGHT, "FDF", true);
	if (!fdf.mlx)
		free_fdf_parts_and_exit_error(fdf, "mlx init err\n");
	fdf.image = mlx_new_image(fdf.mlx, WIDTH, HEIGHT);
	if (!fdf.image)
		free_fdf_parts_and_exit_error(fdf, "new image err\n");;
	if (mlx_image_to_window(fdf.mlx, fdf.image, 0, 0) == -1)
		free_fdf_parts_and_exit_error(fdf, "image to window err\n");
	return (fdf);
}
