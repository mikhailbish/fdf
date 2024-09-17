#include "fdf.h"

int check_name(char *name)
{
	size_t	length;
	int	cmp_res;

	cmp_res = 0;
	length = ft_strlen(name);
	if (length < 4)
		return (0);
	cmp_res = ft_strncmp(name + length - 4, ".fdf", 4);
	if (cmp_res == 0)
		return (1);
	return (0);
}

void	delete_content(void *content)
{
	free((char *)content);	
}

double get_radians(int angle)
{
	return ((double)angle * M_PI / 180);
}

void translate_angles(t_ft_point *point)
{
	int	original_x;
	int	original_y;

	original_x = point->x;
	original_y = point->y;
	point->x = (int)ceil(cos(get_radians(150)) * original_x - sin(get_radians(150)) * original_y);
	point->y = (int)ceil(sin(get_radians(120)) * original_x + cos(get_radians(120)) * original_y);
}

t_list	*get_file_lines(int fd)
{
	char	*line;
	t_list	*head;
	t_list	*tmp;
	
	line = get_next_line(fd);
	if (!line)
	{
		//error in gnl
		return (0);
	}
	head = ft_lstnew((void *)line);
	if (!head)
	{
		// error in lst new
		return (0);
	}
	while (line)
	{
		line = get_next_line(fd);
		if (!line && errno == ENOMEM)
		{
			//error in gnl
			return (0);	
		} else if (!line)
			break ;
		tmp = ft_lstnew(line);
		if (!tmp)
		{
			// error in lst new
			return (0);
		}
		ft_lstadd_back(&head, tmp);
	}
	return (head);
}

t_ft_point	**alloc_data_space(t_dimensions dim)
{
	t_ft_point	**coordinates;
	int		i;

	i = 0;
	coordinates = (t_ft_point **)ft_calloc(dim.length, sizeof(t_ft_point *));
	if (!coordinates)
	{
		//error handling
		return (0);
	}
	while (i < dim.length)
	{
		coordinates[i] = (t_ft_point *)ft_calloc(dim.width, sizeof(t_ft_point));
		if (!coordinates[i])
		{
			//error handling, empty previous values filling
			return (0);
		}
		i++;
	}
	return (coordinates);
}

void	fill_with_data(t_dimensions dim, t_ft_point **coordinates, t_list *lines)
{
	char **split_res;
	int x;
	int y;

	x = 0;
	y = 0;
	while (y < dim.length)
	{
		split_res = ft_split((char *)lines->content, ' ');
		while (x < dim.width)
		{
			coordinates[y][x].x = x;
			coordinates[y][x].y = y;
			coordinates[y][x].z = ft_atoi(split_res[x]);
			x++;
			
		}
		free_split(split_res);
		x = 0;
		lines = lines->next;
		y++;
	}
}
/*
t_dimensions	parse_lines(t_dimensions dim, t_list *lines)
{
	int		column_count;
	int		line_count;

	while(lines)
	{
		column_count = validate_lines(lines->content);
		if (column_count == -1)
		{
//			alloc fail in validate line
//			or illegal values
		}
		if (dim.width != column_count)
		{
//			wrong number of columns in a line
		}
		lines = lines->next;
	}
	dim.length = line_count;
	return (dim);	
}
*/	
/*
	char	*line;
	t_list	*head;
	t_list	*tmp;

	line = (char *)-1;

	while (line)
	{
		line = get_next_line(fd);
		if (!line)
			break;
		tmp = ft_lstnew((void *)line);
		if (!tmp)
			break;
			//malloc list error
			//free list?
			//break??
			//no errno check
			// adjust errno?
		ft_lstadd_back(&head, tmp);
	}
	// gnl till the end
	if (!tmp)
		while(line)
		{
			free(line);
			line = get_next_line(fd)
		}
	if (errno == ENOMEM)
	{
		//error in gnl
	}
*/
/*
	line = get_next_line(fd);
	if (line)
		head->content = (void *)line;
	tmp = head;
	while(line)
	{
		tmp->next = *ft_lstnew(line);
		if (!tmp->next)
			ft_lstclear(head, delete_content);
		tmp = tmp->next;
		line = get_next_line(fd);
	}
	if (errno == ENOMEM)
	{
		//error in gnl
	}
*/	

/*
t_dimensions get_map_dimensions()
{

}
*/

