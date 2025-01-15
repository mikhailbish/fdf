/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutuzov <mbutuzov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 18:07:05 by mbutuzov          #+#    #+#             */
/*   Updated: 2025/01/15 20:14:51 by mbutuzov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

//TODO: add directory opening?
int	check_name(char *name)
{
	size_t	length;
	int		cmp_res;

	cmp_res = 0;
	length = ft_strlen(name);
	if (length < 4)
		return (0);
	cmp_res = ft_strncmp(name + length - 4, ".fdf", 4);
	if (cmp_res == 0)
		return (1);
	return (0);
}

t_list	*free_line_and_clear_list(char *line, t_list **head)
{
	free(line);
	if (*head)
		ft_lstclear(head, free);
	return (0);
}

t_list	*get_file_lines(int fd)
{
	t_list	*head;
	t_list	*tmp;
	char	*line;
	int		count;

	count = 0;
	line = (char *)1;
	head = 0;
	while (line)
	{
		line = get_next_line(fd);
		if (!line && !head)
			return (0);
		if (!line)
			break ;
		tmp = ft_lstnew(line);
		if (!tmp)
			return (free_line_and_clear_list(line, &head));
		if (head)
			ft_lstadd_back(&head, tmp);
		else
			head = tmp;
		count++;
	}
	return (head);
}

// TODO: add to utils
// should check for adr?
t_map	*alloc_map_space(t_map *dim)
{
	t_3d_point	*coords_3d;
	t_2d_point	*coords_display;
	int			max;

	max = dim->length * dim->width;
	coords_3d = ft_calloc(max, sizeof(t_3d_point));
	coords_display = ft_calloc(max, sizeof(t_2d_point));
	if (!coords_3d || !coords_display)
	{
		ft_free((void **)&coords_3d);
		ft_free((void **)&coords_display);
		dim->width = -1;
		return (0);
	}
	dim->coords_3d = coords_3d;
	dim->coords_display = coords_display;
	return (dim);
}

// TODO: test returns
t_3d_point	get_3d_point(char *space_separated_val, int x, int y)
{
	t_3d_point	point;
	char		*endptr;

	point.x = (double)x;
	point.y = (double)y;
	point.z = (double)ft_strtol(space_separated_val, &endptr, 10);
	if (*endptr == ',' && *(endptr + 1) != 0)
	{
		space_separated_val = endptr + 1;
		point.color = ft_strtol(space_separated_val, &endptr, 16);
	}
	else
		point.color = 0xFFFFFF;
	return (point);
}

int	fill_3d_at_y(int y, t_map dim, t_list *lines)
{
	char		**split_res;
	int			x;
	int			offset;
	t_3d_point	*coordinates;

	x = 0;
	offset = y * dim.width;
	coordinates = (t_3d_point *)dim.coords_3d;
	split_res = ft_split((char *)lines->content, ' ');
	if (!split_res)
		return (0);
	while (x < dim.width)
	{
		coordinates[offset + x] = get_3d_point(split_res[x], x, y);
		x++;
	}
	free_split(split_res);
	lines = lines->next;
	return (1);
}

int	fill_with_data(t_map dim, t_list *lines)
{
	t_3d_point	*coordinates;
	int			line_fill;
	int			y;

	coordinates = (t_3d_point *)dim.coords_3d;
	y = 0;
	if (y >= dim.length)
		return (1);
	while (y < dim.length)
	{
		line_fill = fill_3d_at_y(y, dim, lines);
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
	int			i;
	int			max_z;
	int			min_z;

	coords = (t_3d_point *)dim->coords_3d;
	i = 0;
	max_z = coords[i].z;
	min_z = coords[i].z;
	i++;
	while (i < (dim->length * dim->width))
	{
		if (min_z > coords[i].z)
			min_z = coords[i].z;
		if (max_z < coords[i].z)
			max_z = coords[i].z;
		i++;
	}
	dim->max_z = max_z;
	dim->min_z = min_z;
}

int	alloc_map_and_fill_with_data(t_map *dim, t_list *lines)
{
	if (!alloc_map_space(dim))
		return (0);
	if (!fill_with_data(*dim, lines))
		return (0);
	set_max_min_z(dim);
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
