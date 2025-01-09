/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processing_extra.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutuzov <mbutuzov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 21:07:13 by mbutuzov          #+#    #+#             */
/*   Updated: 2025/01/09 21:09:56 by mbutuzov         ###   ########.fr       */
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
