/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutuzov <mbutuzov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 18:39:57 by mbutuzov          #+#    #+#             */
/*   Updated: 2024/10/18 18:07:56 by mbutuzov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	return (((double)angle * M_PI) / 180);
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
	mutate_3d_vector(vector, matrix);
	point->x = round(vector[0]);
	point->y = round(vector[1]);
	point->z = round(vector[2]);
}


void translate_angles(t_ft_point *point, double factor)
{
	double	vector[3];
	double	matrix[3][3];
// TODO: find out why some angles crash
	vector[0] = (double)point->x;
	vector[1] = (double)point->y;
	vector[2] = (double)point->z;
	matrix[0][0] = cos(get_radians(30)) * factor;
	matrix[0][1] = -cos(get_radians(30)) * factor;
	matrix[0][2] = 0;
	matrix[1][0] = sin(get_radians(30)) * factor;
	matrix[1][1] = sin(get_radians(30)) * factor;
	matrix[1][2] = 1 * factor;
	matrix[2][0] = 0;
	matrix[2][1] = 0;
	matrix[2][2] = 1 * factor;
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
	int	original_x;
	int	original_y;

	original_x = point->x;
	original_y = point->y;
	point->x = round((-cos(get_radians(30))) * (double)original_x + cos(get_radians(30) * (double)original_y));
// wrong coefficient at z
	point->y = round(((double)point->z - (sin(get_radians(30)) * (double)original_x) - (sin(get_radians(30)) * (double)original_y)));
}
*/
/*
void translate_angles(t_ft_point *point)
{
	int	original_x;
	int	original_y;

	original_x = point->x;
	original_y = point->y;
//	printf("radians: %a\n", get_radians(30));

//TODO: rewrite with matrices
	point->x = round((cos(get_radians(30))) * (double)original_x - cos(get_radians(30)) * (double)original_y);
// wrong coefficient at z
	point->y = round(((double)point->z + (sin(get_radians(30)) * (double)original_x) + (sin(get_radians(30)) * (double)original_y)));
}
*/
/*
void translate_angles(t_ft_point *point)
{
	int	original_x;
	int	original_y;

	original_x = point->x;
	original_y = point->y;
	point->x = round((cos(get_radians(30))) * (double)original_x + cos(get_radians(30) * (double)original_y));
// wrong coefficient at z
	point->y = round(((double)point->z + (sin(get_radians(30)) * (double)original_x) + (-sin(get_radians(30)) * (double)original_y)));
}
*/
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
// wip some corner points showing poorly and lines not connected
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
	if (smallest_x < 1)
	{
		shift_x(dim, coords, -smallest_x);
	//	shift xs
	}
	if (smallest_y < 1)
	{
		shift_y(dim, coords, -smallest_y);
	//	shift ys
	}
	if (smallest_z < 0)
	{
	//	ft_printf("neg z?");
		shift_z(dim, coords, -smallest_z);
	//	shift zs
	}

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
		//TODO: handle
		//error in gnl
		//malloc or read
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
/*
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
*/
// TODO: test returns
// wip some corner points showing poorly and lines not connected
int	fill_with_data(t_dimensions dim, t_ft_point **coordinates, t_list *lines)
{
	char **split_res;
	int x;
	int y;
	char **comma_split_res;

	x = 0;
	y = 0;
	split_res = 0;
	if (y >= dim.length)
		return 1;
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
				// TODO: handle 0
				coordinates[y][x].z = ft_atoi(comma_split_res[0]);
				coordinates[y][x].color = (int32_t)ft_strtol(comma_split_res[1], 0, 16);
	//			coordinates[y][x].color = coordinates[y][x].color << 8;
	//			coordinates[y][x].color += 0xFF; 
			}
			else if (ft_strchr(split_res[x], ','))
			{
				//more than one comma - error?
			}
			else
			{
				coordinates[y][x].z = ft_atoi(split_res[x]);
				coordinates[y][x].color = 0xFFFFFF;
			}
			coordinates[y][x].x = x;
			coordinates[y][x].y = dim.length - y - 1;
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

t_dimensions get_data_from_fd(int fd)
{
	t_dimensions dim;
	t_list *file_lines;
	t_list *tmp;

	if (fd < 0)
	{
		perror("Cannot find file");
//		TODO: handle
//		return (1);
	}
	
	file_lines = get_file_lines(fd);
	//close(fd); // handle outside
	tmp = file_lines;
	dim = validate_lines(file_lines);
	dim.coords = alloc_data_space(dim);
	if (!dim.coords)
	{
		//TODO: handle
	}
	fill_with_data(dim, dim.coords, file_lines);
	ft_lstclear(&tmp, delete_content);
	return (dim);
	//ft_printf("%d %d\n", asd.width, asd.length);
	
}

void	process_data(t_dimensions dim)
{
	int x;
	int y;
	int ext_coef;
	t_ft_point **coords;

	x = 0;
	y = 0;
	ext_coef = 40;
	coords = dim.coords;
	while(y < dim.length)
	{
		while (x < dim.width)
		{
			extend_lines(&coords[y][x], ext_coef);
			translate_angles(&coords[y][x], 1);
//			translate_angles(&coords[y][x]);
			x++;
		}
		x = 0;
		y++;
	}
	x = 0;
	y = 0;

	make_positive(dim, coords);
}

void display_data(t_dimensions dim, t_dimensions image_size, mlx_image_t *image)
{
	int x;
	int y;
	t_ft_point **coords;
	coords = dim.coords;
	
	y = 0;
	while(y < dim.length)
	{
		x = 0;
		while (x < dim.width)
		{
			if (coords[y][x].x < image_size.width && coords[y][x].y < image_size.length )
			{
				if (((y == (dim.length - 1)) || (y == 0) ) && x == 0 )
				{
					uint32_t color = ft_pixel(0xFF, 0xFF, 0xFF, 0xFF);
					mlx_put_pixel(image, (uint32_t)coords[y][x].x, (uint32_t)image_size.length - (uint32_t)coords[y][x].y , color);
				}
			}
			else
			{	// TODO: should not be thing, work on ext_coef at parsing
				perror("image too small");
				exit(1);
			}
			x++;
		}
		y++;
	}
	put_lines(image, dim, coords);
}
