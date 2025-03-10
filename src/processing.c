/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutuzov <mbutuzov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 18:07:14 by mbutuzov          #+#    #+#             */
/*   Updated: 2025/01/24 18:49:48 by mbutuzov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	shift_x(t_map dim, t_3d_point *coords, double offset)
{
	int32_t	i;
	int32_t	max;

	i = 0;
	max = dim.width * dim.length;
	while (i < max)
	{
		coords[i].x += offset;
		i++;
	}
}

static void	shift_y(t_map dim, t_3d_point *coords, double offset)
{
	int32_t	i;
	int32_t	max;

	i = 0;
	max = dim.width * dim.length;
	while (i < max)
	{
		coords[i].y += offset;
		i++;
	}
}

static void	make_positive(t_map *dim)
{
	t_3d_point	*coords;
	double		smallest_x;
	double		smallest_y;
	int32_t		i;
	int32_t		max;

	i = 0;
	coords = dim->coords_3d;
	max = dim->width * dim->length;
	smallest_x = coords[0].x;
	smallest_y = coords[0].y;
	while (i < max)
	{
		if (smallest_x > coords[i].x)
			smallest_x = coords[i].x;
		if (smallest_y > coords[i].y)
			smallest_y = coords[i].y;
		i++;
	}
	if (smallest_x < 0)
		shift_x(*dim, coords, -smallest_x);
	if (smallest_y < 0)
		shift_y(*dim, coords, -smallest_y);
}

double	get_ext_coef(t_map dim, double window_width, double window_height)
{
	t_3d_point	edge_points[2];
	double		a;
	double		b;
	int32_t		max_y;
	int32_t		min_y;

	edge_points[0] = dim.coords_original[0];
	edge_points[1] = dim.coords_original[dim.width * dim.length - 1];
	set_max_min_y_3d(&max_y, &min_y, dim);
	a = window_width / (edge_points[1].x - edge_points[0].x) / 2;
	if (max_y - min_y)
		b = window_height / (max_y - min_y) / 2;
	else
		b = window_height;
	return (fmin(a, b));
}

void	process_data(t_fdf *fdf)
{
	t_3d_point	*coords;
	double		ext_coef;
	int32_t		x;
	int32_t		max;
	t_map		*dim;

	dim = &(fdf->dim);
	max = dim->length * dim->width;
	coords = dim->coords_3d;
	ft_memcpy(coords, dim->coords_original, max * sizeof (t_3d_point));
	x = 0;
	while (x < max)
	{
		translate_angles(&coords[x]);
		x++;
	}
	make_positive(dim);
	ext_coef = get_ext_coef(*dim, fdf->mlx->width, fdf->mlx->height);
	x = 0;
	while (x < max)
	{
		extend_lines(&coords[x], ext_coef);
		x++;
	}
}
