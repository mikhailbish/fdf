/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_line.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutuzov <mbutuzov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 18:07:26 by mbutuzov          #+#    #+#             */
/*   Updated: 2025/01/21 16:58:52 by mbutuzov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	put_line_low(t_2d_point start, t_2d_point end, mlx_image_t *image)
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
		line.color = get_color(start.color, end.color,
				start.x - (end.x - line.dx), line.dx);
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

static void	put_line_high(t_2d_point start, t_2d_point end, mlx_image_t *image)
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
		line.color = get_color(start.color, end.color,
				start.y - (end.y - line.dy), line.dy);
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

void	put_line(t_2d_point start, t_2d_point end, mlx_image_t *image)
{
	if (ft_abs(end.y - start.y) < ft_abs(end.x - start.x))
	{
		if (start.x > end.x)
			put_line_low(end, start, image);
		else
			put_line_low(start, end, image);
	}
	else
	{
		if (start.y > end.y)
			put_line_high(end, start, image);
		else
			put_line_high(start, end, image);
	}
}
