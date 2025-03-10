/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutuzov <mbutuzov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 18:06:34 by mbutuzov          #+#    #+#             */
/*   Updated: 2025/01/23 16:49:19 by mbutuzov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int32_t	get_red(uint32_t color)
{
	return ((int32_t)((color >> 16) & 0xFF));
}

int32_t	get_green(uint32_t color)
{
	return ((int32_t)((color >> 8) & 0xFF));
}

int32_t	get_blue(uint32_t color)
{
	return ((int32_t)((color) & 0xFF));
}

uint32_t	get_color(
	uint32_t start_color,
	uint32_t end_color,
	int32_t i,
	int32_t length
)
{
	t_color	change;
	t_color	final;

	if (i == 0 || (start_color == end_color))
		return (start_color);
	if (i == length)
		return (end_color);
	change.red = get_red(end_color) - get_red(start_color);
	change.green = get_green(end_color) - get_green(start_color);
	change.blue = get_blue(end_color) - get_blue(start_color);
	final.red = get_red(start_color) + (i * (change.red)) / length;
	final.green = get_green(start_color) + (i * (change.green)) / length;
	final.blue = get_blue(start_color) + (i * (change.blue)) / length;
	return (((uint32_t)final.red) << 16
		| ((uint32_t)final.green) << 8
		| (uint32_t)final.blue);
}
