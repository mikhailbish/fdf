/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutuzov <mbutuzov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 18:07:14 by mbutuzov          #+#    #+#             */
/*   Updated: 2025/01/21 18:19:21 by mbutuzov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	shift_x(t_map dim, t_3d_point *coords, double offset)
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

static void	shift_y(t_map dim, t_3d_point *coords, double offset)
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

static void	make_positive(t_map *dim)
{
	t_3d_point	*coords;
	double		smallest_x;
	double		smallest_y;
	int			i;
	int			max;

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

//TODO: work on ext coef
double	get_ext_coef(t_map dim, double window_width, double window_height)
{
	double	a;
	double	b;
	t_3d_point	edge_points[2];
	int i = 0;
	int max  = dim.width * dim.length;
	int max_y = dim.coords_3d[0].y;
	int min_y = dim.coords_3d[0].y;

	edge_points[0] = dim.coords_original[0];  //leftmost
	edge_points[1] = dim.coords_original[dim.width * dim.length - 1]; // rightmost
	translate_angles(&edge_points[0]);
	translate_angles(&edge_points[1]);
	while (i < max)
	{
		if (max_y < dim.coords_3d[i].y)
			max_y = dim.coords_3d[i].y;
		if (min_y > dim.coords_3d[i].y)
			min_y = dim.coords_3d[i].y;
		i++;
	}
	a = window_width / (edge_points[1].x - edge_points[0].x) / 2;
	if (max_y - min_y)
		b = window_height / (max_y - min_y)/2;
	else
		b = window_height;
	return (fmin(a, b));
}

void	process_data(t_fdf *fdf)
{
	t_3d_point	*coords;
	double		ext_coef;
	int			x;
	int			max;
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
