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

//wip
void extend_lines(t_ft_point *point, int num)
{
	double	vector[3];
	double	matrix[3][3];

	vector[0] = (double)point->x;
	vector[1] = (double)point->y;
	vector[2] = (double)point->z;
	matrix[0][0] = num;
	matrix[0][1] = 0;
	matrix[0][2] = 0;
	matrix[1][0] = 0;
	matrix[1][1] = num;
	matrix[1][2] = 0;
	matrix[2][0] = 0;
	matrix[2][1] = 0;
	matrix[2][2] = num;
//	point->x = (int)ceil(cos(get_radians(150)) * original_x - sin(get_radians(150)) * original_y);
//	point->y = (int)ceil(sin(get_radians(120)) * original_x + cos(get_radians(120)) * original_y);
	mutate_3d_vector(vector, matrix);
	point->x = round(vector[0]);
	point->y = round(vector[1]);
	point->z = round(vector[2]);
}
/*
void translate_angles(t_ft_point *point)
{
	double	vector[3];
	double	matrix[3][3];

	vector[0] = (double)point->x;
	vector[1] = (double)point->y;
	vector[2] = (double)point->z;
	matrix[0][0] = cos(120);
	matrix[0][1] = -sin(120);
	matrix[0][2] = 0;
	matrix[1][0] = sin(120);
	matrix[1][1] = cos(120);
	matrix[1][2] = 0;
	matrix[2][0] = 0;
	matrix[2][1] = 0;
	matrix[2][2] = 1;
//	point->x = (int)ceil(cos(get_radians(150)) * original_x - sin(get_radians(150)) * original_y);
//	point->y = (int)ceil(sin(get_radians(120)) * original_x + cos(get_radians(120)) * original_y);
	mutate_3d_vector(vector, matrix);
	point->x = ceil(vector[0]);
	point->y = ceil(vector[1]);
	point->z = ceil(vector[2]);
}
*/

void translate_angles(t_ft_point *point)
{
	int	original_x;
	int	original_y;

	original_x = point->x;
	original_y = point->y;
	point->x = round((-cos(get_radians(30))) * (double)original_x + cos(get_radians(30) * (double)original_y));
// wrong coefficient at z
	point->y = round(((double)point->z - (sin(get_radians(30)) * (double)original_x) - (sin(get_radians(30)) * (double)original_y)));
}

//wip
void shift_x(t_dimensions dim, t_ft_point **coords, double offset)
{
	int x;
	int y;

	x = 0;
	y = 0;
	while (y < dim.length)
	{
		x = 0;
		while(x < dim.width)
		{
			coords[y][x].x += offset;
			x++;	
		}
		y++;
	}
}

void shift_y(t_dimensions dim, t_ft_point **coords, double offset)
{
	int x;
	int y;

	x = 0;
	y = 0;
	while (y < dim.length)
	{
		x = 0;
		while(x < dim.width)
		{
			coords[y][x].y += offset;
			x++;	
		}
		y++;
	}
}

void shift_z(t_dimensions dim, t_ft_point **coords, double offset)
{
	int x;
	int y;

	x = 0;
	y = 0;
	while (y < dim.length)
	{
		x = 0;
		while(x < dim.width)
		{
			coords[y][x].z += offset;
			x++;	
		}
		y++;
	}
}
void make_positive(t_dimensions dim, t_ft_point **coords)
{
	// go through all coordinates
	// find smallest x y and z
	// shift all coordinates by the abs of negative
	int x;
	int y;
	double smallest_x;
	double smallest_y;
	double smallest_z;
	

//	x = 0;
	y = 0;
	smallest_x = coords[0][0].x;
	smallest_y = coords[0][0].y;
	smallest_z = coords[0][0].z;
	while (y < dim.length)
	{
		x = 0;
		while(x < dim.width)
		{
			if (smallest_x > coords[y][x].x)
				smallest_x = coords[y][x].x;
			if (smallest_y > coords[y][x].y)
				smallest_y = coords[y][x].y;
			if (smallest_z > coords[y][x].z)
				smallest_z = coords[y][x].z;
			x++;	
		}
		y++;
	}
	if (smallest_x < 0)
	{
		shift_x(dim, coords, -smallest_x);
	//	shift xs
	}
	if (smallest_y < 0)
	{
		shift_y(dim, coords, -smallest_y);
	//	shift ys
	}
/*	if (smallest_z < 0)
	{
		ft_printf("neg z?");
		shift_z(dim, coords, -smallest_z);
	//	shift zs
	}
*/
}

/*
universalize?
void shift_some(t_dimensions dim, t_ft_point **coords, double offset )
{
	int x;
	int y;

	while (y < dim.length)
	{
		x = 0;
		while(x < dim.width)
		{
			coords[y][x].x += offset;
			x++;	
		}
		y++;
	}
}
*/


/*
void translate_angles(t_ft_point *point)
{
	int	original_x;
	int	original_y;


	original_x = point->x;
	original_y = point->y;

	point->x = (int)ceil(cos(get_radians(150)) * original_x - sin(get_radians(150)) * original_y);
	point->y = (int)ceil(sin(get_radians(120)) * original_x + cos(get_radians(120)) * original_y);

}
*/


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
//	y = dim.length - 1;
//	while (y > -1)
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
//		y--;
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

