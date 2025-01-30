/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   connect_all_points.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutuzov <mbutuzov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 15:02:07 by mbutuzov          #+#    #+#             */
/*   Updated: 2025/01/30 17:26:50 by mbutuzov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "fdf.h"

t_2d_point	get_2d_coord(t_map dim, int x, int y)
{
	t_2d_point	*coords;

	coords = (t_2d_point *)dim.coords_display;
	return (coords[y * dim.width + x]);
}

int	put_line_order(t_map dim, mlx_image_t *image, int x, int y)
{
	int			line_count;

	line_count = 0;
	if (x == 0 && y < dim.length - 1)
	{
		put_line(get_2d_coord(dim, x, y),
			get_2d_coord(dim, x, y + 1), image);
		line_count += 1;
	}
	else if ((x < (dim.width - 1)) && (y == (dim.length - 1)))
	{
		put_line(get_2d_coord(dim, x, y),
			get_2d_coord(dim, x + 1, y), image);
		line_count += 1;
	}
	else if (!((x == (dim.width - 1)) && (y == (dim.length - 1))))
	{
		put_line(get_2d_coord(dim, x, y),
			get_2d_coord(dim, x, y + 1), image);
		put_line(get_2d_coord(dim, x - 1, y),
			get_2d_coord(dim, x, y), image);
		line_count += 2;
	}
	return (line_count);
}

int	put_line_order_color(t_map dim, mlx_image_t *image,
		int coord[2], uint32_t *color)
{
	int			line_count;

	line_count = 0;
	if (coord[0] == 0 && coord[1] < dim.length - 1)
	{
		put_line_color(get_2d_coord(dim, coord[0], coord[1]),
			get_2d_coord(dim, coord[0], coord[1] + 1), image, color);
		line_count += 1;
	}
	else if ((coord[0] < (dim.width - 1)) && (coord[1] == (dim.length - 1)))
	{
		put_line_color(get_2d_coord(dim, coord[0], coord[1]),
			get_2d_coord(dim, coord[0] + 1, coord[1]), image, color);
		line_count += 1;
	}
	else if (!((coord[0] == (dim.width - 1)) && (coord[1] == (dim.length - 1))))
	{
		put_line_color(get_2d_coord(dim, coord[0], coord[1]),
			get_2d_coord(dim, coord[0], coord[1] + 1), image, color);
		put_line_color(get_2d_coord(dim, coord[0] - 1, coord[1]),
			get_2d_coord(dim, coord[0], coord[1]), image, color);
		line_count += 2;
	}
	return (line_count);
}

void	put_lines(mlx_image_t *image, t_map dim)
{
	int32_t	y;
	int32_t	x;
	int		line_count;

	line_count = 0;
	y = 0;
	while (y < dim.length)
	{
		x = dim.width - 1;
		while (x > -1)
		{
			line_count += put_line_order(dim, image, x, y);
			x--;
		}
		y++;
	}
}

void	put_lines_color(mlx_image_t *image, t_map dim, uint32_t *color)
{
	int32_t	coord[2];
	int		line_count;

	line_count = 0;
	coord[1] = 0;
	while (coord[1] < dim.length)
	{
		coord[0] = dim.width - 1;
		while (coord[0] > -1)
		{
			line_count += put_line_order_color(dim, image, coord, color);
			coord[0]--;
		}
		coord[1]++;
	}
}
