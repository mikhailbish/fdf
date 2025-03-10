/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_extra.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutuzov <mbutuzov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 20:12:18 by mbutuzov          #+#    #+#             */
/*   Updated: 2025/01/24 19:29:28 by mbutuzov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	fill_3d_at_y(int32_t y, t_map *dim, t_list *lines)
{
	char		**split_res;
	int32_t		x;
	int32_t		offset;
	t_3d_point	*coordinates;

	x = 0;
	offset = y * dim->width;
	coordinates = dim->coords_original;
	split_res = ft_split((char *)lines->content, ' ');
	if (!split_res)
		return (0);
	while (x < dim->width)
	{
		coordinates[offset + x] = get_3d_point(split_res[x], x,
				y, &(dim->colors_specified));
		x++;
	}
	free_split(split_res);
	lines = lines->next;
	return (1);
}

int	fill_with_data(t_map *dim, t_list *lines)
{
	int32_t	y;

	y = 0;
	if (y >= dim->length)
		return (1);
	while (y < dim->length)
	{
		if (!fill_3d_at_y(y, dim, lines))
			break ;
		lines = lines->next;
		y++;
	}
	return (1);
}

void	set_max_min_z(t_map *dim)
{
	t_3d_point	*coords;
	int32_t		i;
	int32_t		max_z;
	int32_t		min_z;
	int32_t		max;

	max = dim->length * dim->width;
	coords = dim->coords_original;
	i = 0;
	max_z = coords[i].z;
	min_z = coords[i].z;
	i++;
	while (i < max)
	{
		if (min_z > floor(coords[i].z))
			min_z = floor(coords[i].z);
		if (max_z < ceil(coords[i].z))
			max_z = ceil(coords[i].z);
		i++;
	}
	dim->max_z = max_z;
	dim->min_z = min_z;
}

int	alloc_map_and_fill_with_data(t_map *dim, t_list *lines)
{
	if (!alloc_map_space(dim))
		return (0);
	if (!fill_with_data(dim, lines))
		return (0);
	set_max_min_z(dim);
	if (!dim->colors_specified)
		set_basic_colors(dim);
	return (1);
}

t_map	get_data_from_fd(int fd, t_fdf *fdf)
{
	t_list	*file_lines;
	t_list	*tmp;

	file_lines = get_file_lines(fd);
	if (!file_lines)
	{
		fdf->dim.width = -1;
		return (fdf->dim);
	}
	tmp = file_lines;
	fdf->dim = validate_lines(file_lines, fdf->dim);
	if (fdf->dim.width == -1)
	{
		ft_lstclear(&file_lines, free);
		return (fdf->dim);
	}
	if (!alloc_map_and_fill_with_data(&(fdf->dim), file_lines))
		fdf->dim.width = -1;
	ft_lstclear(&tmp, free);
	return (fdf->dim);
}
