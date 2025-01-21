/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_fdf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutuzov <mbutuzov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 18:07:37 by mbutuzov          #+#    #+#             */
/*   Updated: 2025/01/20 22:24:18 by mbutuzov         ###   ########.fr       */
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
	fdf.aquarium = 0;
	fdf.dim.width = 0;
	fdf.dim.length = 0;
	fdf.dim.coords_3d = 0;
	fdf.dim.coords_display = 0;
	fdf.dim.coords_original = 0;
	fdf.painted = 0;
	fdf.dim.max_z = 0;
	fdf.dim.min_z = 0;
	fdf.dim.colors_specified = 0;
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
	if (fdf.aquarium)
		mlx_delete_image(fdf.mlx, fdf.image);
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
	if (fdf.dim.coords_original)
		free(fdf.dim.coords_original);
}

void	free_fdf_parts_and_exit_error(t_fdf fdf, char *error)
{
	free_fdf_parts(fdf);
	if (error)
		ft_putstr_fd(error, 2);
	exit(1);
}

void	paint_black_square(t_fdf fdf)
{
	unsigned int	i;
	unsigned int	max;
	int32_t			*ptr;

	max = fdf.image->width * fdf.image->height;
	i = 0;
	ptr = (int32_t *)fdf.aquarium->pixels;
	while (i < max)
		ptr[i++] = 0xFF000000;
}

t_fdf	fdf_fill(t_fdf fdf)
{
	int32_t	monitor_width;
	int32_t	monitor_height;

	fdf.mlx = mlx_init(WIDTH, HEIGHT, "FDF", true);
	if (!fdf.mlx)
		free_fdf_parts_and_exit_error(fdf, "mlx init err\n");
	mlx_get_monitor_size(0, &monitor_width, &monitor_height);
	fdf.aquarium = mlx_new_image(fdf.mlx, monitor_width, monitor_height);
	if (mlx_image_to_window(fdf.mlx, fdf.aquarium, 0, 0) == -1)
		free_fdf_parts_and_exit_error(fdf, "image to window err\n");
	if (!fdf.aquarium)
		free_fdf_parts_and_exit_error(fdf, "new image err\n");
	fdf.image = mlx_new_image(fdf.mlx, monitor_width, monitor_height);
	if (!fdf.image)
		free_fdf_parts_and_exit_error(fdf, "new image err\n");
	if (mlx_image_to_window(fdf.mlx, fdf.image, 0, 0) == -1)
		free_fdf_parts_and_exit_error(fdf, "image to window err\n");
	mlx_set_instance_depth(fdf.aquarium->instances, -1);
	paint_black_square(fdf);
	return (fdf);
}
