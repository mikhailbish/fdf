/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutuzov <mbutuzov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 18:07:05 by mbutuzov          #+#    #+#             */
/*   Updated: 2025/01/30 18:15:02 by mbutuzov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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

	line = (char *)1;
	head = 0;
	while (line)
	{
		line = get_next_line(fd);
		if (!line && !head)
			return (0);
		if (!line)
			break ;
		remove_new_line(line);
		tmp = ft_lstnew(line);
		if (!tmp)
			return (free_line_and_clear_list(line, &head));
		if (head)
			ft_lstadd_back(&head, tmp);
		else
			head = tmp;
	}
	return (head);
}

t_map	*alloc_map_space(t_map *dim)
{
	t_3d_point	*coords_3d;
	t_3d_point	*coords_original;
	t_2d_point	*coords_display;
	int32_t		max;

	max = dim->length * dim->width;
	coords_original = ft_calloc(max, sizeof(t_3d_point));
	coords_3d = ft_calloc(max, sizeof(t_3d_point));
	coords_display = ft_calloc(max, sizeof(t_2d_point));
	if (!coords_3d || !coords_display || !coords_original)
	{
		ft_free((void **)&coords_3d);
		ft_free((void **)&coords_display);
		ft_free((void **)&coords_original);
		dim->width = -1;
		return (0);
	}
	dim->coords_3d = coords_3d;
	dim->coords_display = coords_display;
	dim->coords_original = coords_original;
	return (dim);
}

t_3d_point	get_3d_point(char *space_separated_val, int x,
	int y, int *color_spec)
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
		*color_spec = 1;
	}
	else
		point.color = 0xFFFFFF;
	return (point);
}
