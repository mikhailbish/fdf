/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processing_extra.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutuzov <mbutuzov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 18:07:20 by mbutuzov          #+#    #+#             */
/*   Updated: 2025/01/17 22:48:09 by mbutuzov         ###   ########.fr       */
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

//TODO: ceanup comment
// assuming that the correct math has already been performed
void	convert_3dto2d(t_map *dim)
{
	t_3d_point	*coords;
	t_2d_point	*new_coords;
	int			i;
	int			max;

	max = dim->width * dim->length;
	i = 0;
	coords = (t_3d_point *)dim->coords_3d;
	new_coords = dim->coords_display;
	while (i < max)
	{
		new_coords[i] = point_3dto2d(coords[i]);
		i++;
	}
	dim->coords_display = (void *)new_coords;
}

void	display_data(t_map dim, mlx_image_t *image)
{
	convert_3dto2d(&dim);
	put_lines(image, dim);
}


//TODO: consider different colors, consider black bg color
//TODO: make color_highest, lowest macros
//0xf23607
//0x4c9106
void set_basic_colors(t_map *dim)
{
//	int32_t color_lowest = 0xDD3333;
//	int32_t color_highest = 0xDDDDFF;
//	int32_t color_lowest = 0xCCCCFF;
//	int32_t color_highest = 0xFF6666;
//	int32_t color_lowest = 0x034F1B;
//	int32_t color_highest = 0xBA7402;
//	int32_t color_lowest = 0xBA7402;
//	int32_t color_highest = 0x034F1B;
	int32_t color_lowest = 0x4c9106;
	int32_t color_highest = 0xf23607;
	t_3d_point *coords;
	int z_diff;
	int max;
	int i;

	i = 0;
	max = dim->length * dim->width;
	z_diff = dim->max_z - dim->min_z;
	coords = (t_3d_point *)dim->coords_3d;
	while(i < max)
	{
		coords[i].color = get_color(color_lowest, color_highest,
			round(coords[i].z) - dim->min_z, z_diff);
		i++;
	}
}
