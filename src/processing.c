/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutuzov <mbutuzov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 20:51:41 by mbutuzov          #+#    #+#             */
/*   Updated: 2025/01/09 21:03:24 by mbutuzov         ###   ########.fr       */
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
	coords = (t_3d_point *)dim->coords_3d;
	max = dim->width * dim->length;
	smallest_x = (double)coords[0].x;
	smallest_y = (double)coords[0].y;
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
static double	get_ext_coef(t_map dim)
{
	double	a;
	double	b;
	double	c;

// screen width, 
// TODO: fix
	a = WIDTH / (((double)dim.width + (double)dim.length) );
	b = HEIGHT / (((double)dim.width + (double)dim.length) );
	if (dim.max_z - dim.min_z != 0)
		c = HEIGHT / (fabs((double)dim.max_z - (double)dim.min_z));
	else
		c = HEIGHT;
//	printf("z val %e\n", 10/((double)dim.max_z - (double)dim.min_z));
// TODO: clean up
/*	double ext_coef = fmin(fmin(a, b), c);
	if (ext_coef == a)
		printf("width based smallest %e\n", ext_coef);
	if (ext_coef == b)
		printf("length based smallest %e\n", ext_coef);
	if (ext_coef == c)
		printf("z based smallest %e\n", ext_coef);
*/
	return (fmin(fmin(a, b), c));
}

void	process_data(t_map *dim)
{
	t_3d_point	*coords;
	int			x;
	double			ext_coef;
	int			max;

	max = dim->length * dim->width;
	x = 0;
	ext_coef = get_ext_coef(*dim);
//	ext_coef = 3;
	coords = (t_3d_point *)dim->coords_3d;
	while (x < max)
	{
		extend_lines(&coords[x], ext_coef);
		translate_angles(&coords[x]);
		x++;
	}
	make_positive(dim);
}
