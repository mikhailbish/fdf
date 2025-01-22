/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processing_extra.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutuzov <mbutuzov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 18:07:20 by mbutuzov          #+#    #+#             */
/*   Updated: 2025/01/22 20:30:37 by mbutuzov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static t_2d_point	point_3dto2d(t_3d_point point_3d )
{
	t_2d_point	point_2d;

	point_2d.x = round(point_3d.x);
	point_2d.y = round(point_3d.y);
	point_2d.color = point_3d.color;
	return (point_2d);
}

void	convert_3dto2d(t_map *dim)
{
	t_3d_point	*coords;
	t_2d_point	*new_coords;
	int			i;
	int			max;

	max = dim->width * dim->length;
	i = 0;
	coords = dim->coords_3d;
	new_coords = dim->coords_display;
	while (i < max)
	{
		new_coords[i] = point_3dto2d(coords[i]);
		i++;
	}
	dim->coords_display = (void *)new_coords;
}

void	set_basic_colors(t_map *dim)
{
	t_3d_point	*coords;
	int			z_diff;
	int			max;
	int			i;

	i = 0;
	max = dim->length * dim->width;
	z_diff = dim->max_z - dim->min_z;
	coords = dim->coords_original;
	while (i < max)
	{
		coords[i].color = get_color(COLOR_LOW, COLOR_HIGH,
				round(coords[i].z) - dim->min_z, z_diff);
		i++;
	}
}

void	set_max_min_y_3d(int *max_y_ptr, int *min_y_ptr, t_map dim)
{
	int	max_y;
	int	min_y;
	int	max;
	int	i;

	max_y = round(dim.coords_3d[0].y);
	min_y = round(dim.coords_3d[0].y);
	i = 0;
	max = dim.width * dim.length;
	while (i < max)
	{
		if (max_y < dim.coords_3d[i].y)
			max_y = ceil(dim.coords_3d[i].y);
		if (min_y > dim.coords_3d[i].y)
			min_y = floor(dim.coords_3d[i].y);
		i++;
	}
	*max_y_ptr = max_y;
	*min_y_ptr = min_y;
}
