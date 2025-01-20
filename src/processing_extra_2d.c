/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processing_extra_2d.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutuzov <mbutuzov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 21:56:44 by mbutuzov          #+#    #+#             */
/*   Updated: 2025/01/20 20:01:45 by mbutuzov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	get_max_min_x_display(t_map *dim)
{
	t_2d_point	*coords;
	int32_t		max_x;
	int32_t		min_x;
	int			i;
	int			max;

	max = dim->width * dim->length;
	i = 0;
	coords = (t_2d_point *)dim->coords_display;
	max_x = coords[0].x;
	min_x = coords[0].x;
	while (i < max)
	{
		if (max_x < coords[i].x)
			max_x = coords[i].x;
		if (min_x > coords[i].x)
			min_x = coords[i].x;
		i++;
	}
	dim->max_x = max_x;
	dim->min_x = min_x;
}

void	get_max_min_y_display(t_map *dim)
{
	t_2d_point	*coords;
	int32_t		max_y;
	int32_t		min_y;
	int			i;
	int			max;

	max = dim->width * dim->length;
	i = 0;
	coords = (t_2d_point *)dim->coords_display;
	max_y = coords[0].y;
	min_y = coords[0].y;
	while (i < max)
	{
		if (max_y < coords[i].y)
			max_y = coords[i].y;
		if (min_y > coords[i].y)
			min_y = coords[i].y;
		i++;
	}
	dim->max_y = max_y;
	dim->min_y = min_y;
}

static void	shift_x_2d(t_map dim, t_2d_point *coords, int32_t offset)
{
	int	i;
	int	max;

	i = 0;
	max = dim.width * dim.length;
	while (i < max)
	{
		coords[i].x += offset;
		i++;
	}
}

static void	shift_y_2d(t_map dim, t_2d_point *coords, int32_t offset)
{
	int	i;
	int	max;

	i = 0;
	max = dim.width * dim.length;
	while (i < max)
	{
		coords[i].y += offset;
		i++;
	}
}

void	display_data(t_fdf *fdf)//, t_map dim, mlx_image_t *image)
{
	int32_t	offset_x;
	int32_t	offset_y;
// TODO; convert bg to black here?

	paint_black_square(*fdf);
	convert_3dto2d(&(fdf->dim));
	get_max_min_x_display(&(fdf->dim));
	get_max_min_y_display(&(fdf->dim));
	offset_x = fdf->mlx->width / 2 - fdf->dim.max_x / 2;
	offset_y = fdf->mlx->height / 2 - fdf->dim.max_y / 2;
	shift_x_2d(fdf->dim, fdf->dim.coords_display, offset_x);
	shift_y_2d(fdf->dim, fdf->dim.coords_display, offset_y);
	put_lines(fdf->image, fdf->dim);
}
