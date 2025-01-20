/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_line_color.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutuzov <mbutuzov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 18:07:26 by mbutuzov          #+#    #+#             */
/*   Updated: 2025/01/20 22:47:08 by mbutuzov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	put_line_low_color(t_2d_point start, t_2d_point end, mlx_image_t *image, int32_t *color)
{
	t_line	line;

	line.dx = end.x - start.x;
	line.dy = end.y - start.y;
	line.step = 1;
	if (line.dy < 0)
	{
		line.step = -1;
		line.dy = -line.dy;
	}
	line.d = (2 * line.dy) - line.dx;
	while (start.x <= end.x)
	{
		if (!color)
			line.color = get_color(start.color, end.color,
					start.x - (end.x - line.dx), line.dx);
		else
			line.color = *color;
		mlx_put_pixel(image, start.x, start.y, (line.color << 8) + 0xFF);
		if (line.d > 0)
		{
			start.y += line.step;
			line.d += 2 * (line.dy - line.dx);
		}
		else
			line.d += 2 * line.dy;
		start.x++;
	}
}

static void	put_line_high_color(t_2d_point start, t_2d_point end, mlx_image_t *image, int32_t *color)
{
	t_line	line;

	line.dx = end.x - start.x;
	line.dy = end.y - start.y;
	line.step = 1;
	if (line.dx < 0)
	{
		line.step = -1;
		line.dx = -line.dx;
	}
	line.d = (2 * line.dx) - line.dy;
	while (start.y <= end.y)
	{
		if (!color)
			line.color = get_color(start.color, end.color,
					start.y - (end.y - line.dy), line.dy);
		else
			line.color = *color;
		mlx_put_pixel(image, start.x, start.y, (line.color << 8) + 0xFF);
		if (line.d > 0)
		{
			start.x += line.step;
			line.d += 2 * (line.dx - line.dy);
		}
		else
			line.d += 2 * line.dx;
		start.y++;
	}
}

void	put_line_color(t_2d_point start, t_2d_point end, mlx_image_t *image, int32_t *color)
{
	if (ft_abs(end.y - start.y) < ft_abs(end.x - start.x))
	{
		if (start.x > end.x)
			put_line_low_color(end, start, image, color);
		else
			put_line_low_color(start, end, image, color);
	}
	else
	{
		if (start.y > end.y)
			put_line_high_color(end, start, image, color);
		else
			put_line_high_color(start, end, image, color);
	}
}
