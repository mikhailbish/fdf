/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutuzov <mbutuzov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 18:07:14 by mbutuzov          #+#    #+#             */
/*   Updated: 2025/01/20 21:02:54 by mbutuzov         ###   ########.fr       */
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
	double	c;

// screen width, 
// TODO: fix
//	a = WIDTH / (((double)dim.width + (double)dim.length));
//	b = HEIGHT / (((double)dim.width + (double)dim.length));
	a = window_width / (((double)dim.width + (double)dim.length));
	b = window_height / (((double)dim.width + (double)dim.length));
//TODO: fabs unnecessary ?
	if (dim.max_z - dim.min_z != 0)
		c = window_height / (fabs((double)dim.max_z - (double)dim.min_z));
	else
		c = window_height;
	return (fmin(fmin(a, b), c));
}

//void	process_data(t_map *dim)
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
	ext_coef = get_ext_coef(*dim, (double)fdf->mlx->width, (double)fdf->mlx->height);
//	ft_putstr_fd("before translate\n", 1);
	while (x < max)
	{
		extend_lines(&coords[x], ext_coef);
		translate_angles(&coords[x]);
		x++;
	}
//	ft_putstr_fd("after translate\n", 1);
	make_positive(dim);
}
