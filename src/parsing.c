/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutuzov <mbutuzov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 20:32:14 by mbutuzov          #+#    #+#             */
/*   Updated: 2025/01/14 19:47:58 by mbutuzov         ###   ########.fr       */
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

//TODO: rename and move
void	delete_content(void *content)
{
	free((char *)content);
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
int	fill_with_data(t_map dim, t_list *lines)
{
	t_3d_point	*coordinates;
	char		**split_res;
	char		**comma_split_res;
	int			x;
	int			y;

	coordinates = (t_3d_point *)dim.coords_3d;
	x = 0;
	y = 0;
	split_res = 0;
	if (y >= dim.length)
		return (1);
	while (y < dim.length)
	{
		split_res = ft_split((char *)lines->content, ' ');
		if (!split_res)
			break ;
		while (x < dim.width)
		{
			if (ft_strchr(split_res[x], ',') && ft_strchr(split_res[x], ',') == ft_strrchr(split_res[x], ','))
			{
				comma_split_res = ft_split(split_res[x], ',');
				if (!comma_split_res)
				{
					free_split(split_res);
					return (0);
				}
				// TODO: handle 0
				coordinates[y * dim.width + x].z = ft_atoi(comma_split_res[0]);
				coordinates[y * dim.width + x].color = (int32_t)ft_strtol(comma_split_res[1], 0, 16);
				free_split(comma_split_res);
			}
			else if (ft_strchr(split_res[x], ','))
			{
				//more than one comma - error?
			}
			else
			{
				coordinates[y * dim.width + x].z = ft_atoi(split_res[x]);
				coordinates[y * dim.width + x].color = 0xFFFFFF;
			}
			coordinates[y * dim.width + x].x = x;
			coordinates[y * dim.width + x].y = y; // dim.length - y - 1;
			x++;
		}
		free_split(split_res);
		x = 0;
		lines = lines->next;
		y++;
	}
	if (!split_res)
		return (0);
	return (1);
}

//TODO: handle no coords?
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

// TODO: check fd outside?
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
	// handle malloc
	// inner stuff from gfl would be already free, prevent further program exec, close fd here??
	//close(fd); // handle outside
	tmp = file_lines;
	fdf->dim = validate_lines(file_lines, fdf->dim);
	if (fdf->dim.width == -1)
	{
		ft_printf("wip in a right place\n");
		ft_lstclear(&file_lines, free);
		return (fdf->dim);
	}
	if (!alloc_map_space(&(fdf->dim)))
	{
		//free lines
		//TODO: handle
		
		ft_lstclear(&tmp, free);
		perror("asd");
		return (fdf->dim);
	}
	if (!fill_with_data(fdf->dim, file_lines))
	{
		ft_lstclear(&tmp, delete_content);
		fdf->dim.width = 0;
		return (fdf->dim);
	}
	ft_lstclear(&tmp, delete_content);
	//TODO: exit?
	set_max_min_z(&(fdf->dim));
	return (fdf->dim);
}
