/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutuzov <mbutuzov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 18:39:57 by mbutuzov          #+#    #+#             */
/*   Updated: 2024/10/21 21:53:09 by mbutuzov         ###   ########.fr       */
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

void extend_lines(t_3d_point *point, int num)
{
	double	vector[3];
	double	matrix[3][3];

	vector[0] = point->x;
	vector[1] = point->y;
	vector[2] = point->z;
	matrix[0][0] = (double)num;
	matrix[0][1] = 0;
	matrix[0][2] = 0;
	matrix[1][0] = 0;
	matrix[1][1] = (double)num;
	matrix[1][2] = 0;
	matrix[2][0] = 0;
	matrix[2][1] = 0;
	matrix[2][2] = (double)num;
	mutate_3d_vector(vector, matrix);
	point->x = round(vector[0]);
	point->y = round(vector[1]);
	point->z = round(vector[2]);
}



/*
void translate_angles(t_3d_point *point)
{
	double	vector[3];
	double	matrix[3][3];
	vector[0] = (double)point->x;
	vector[1] = (double)point->y;
	vector[2] = (double)point->z;
	matrix[0][0] = cos(get_radians(30));
	matrix[0][1] = -cos(get_radians(30));
	matrix[0][2] = 0;
	matrix[1][0] = sin(get_radians(30));
	matrix[1][1] = sin(get_radians(30));
	matrix[1][2] = 1;
	matrix[2][0] = 0;
	matrix[2][1] = 0;
	matrix[2][2] = 1;
	mutate_3d_vector(vector, matrix);
	point->x = round(vector[0]);
	point->y = round(vector[1]);
	point->z = round(vector[2]);
}*/
// TODO: REDO
void translate_angles(t_3d_point *point)
{
	double	vector[3];
	double	matrix[3][3];
	vector[0] = (double)point->x;
	vector[1] = (double)point->y;
	vector[2] = (double)point->z;
	matrix[0][0] = cos(get_radians(30)) * cos(get_radians(30));
	matrix[0][1] = cos(get_radians(30)) * cos(get_radians(30));
	matrix[0][2] = 0;
	matrix[1][0] = -sin(get_radians(30));
	matrix[1][1] = sin(get_radians(30)) * sin(get_radians(30));
	matrix[1][2] = -1;
	matrix[2][0] = 0;
	matrix[2][1] = 0;
	matrix[2][2] = 1;
	mutate_3d_vector(vector, matrix);
	point->x = round(vector[0]);
	point->y = round(vector[1]);
	point->z = round(vector[2]);
}
/*
void rotate_x(t_3d_point poi)
{}
*/
/*
void translate_angles(t_point *point)
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
void translate_angles(t_point *point)
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
void translate_angles(t_point *point)
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
void shift_x(t_map dim, t_3d_point *coords, double offset)
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
			coords[y * dim.width + x].x += offset;
			x++;	
		}
		y++;
	}
}

void shift_y(t_map dim, t_3d_point *coords, double offset)
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
			coords[y * dim.width + x].y += offset;
			x++;	
		}
		y++;
	}
}

void shift_z(t_map dim, t_3d_point *coords, double offset)
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
			coords[y * dim.width + x].z += offset;
			x++;	
		}
		y++;
	}
}

void make_positive(t_map dim)//, t_point **coords)
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
	t_3d_point *coords;

	coords = (t_3d_point *)dim.coords;
//	x = 0;
	y = 0;
//	ft_printf("a\n");
	//display_coords_testing(dim);
	smallest_x = (double)coords[0].x;
	smallest_y = (double)coords[0].y;
	smallest_z = (double)coords[0].z;
//	ft_printf("b\n");
	while (y < dim.length)
	{
		x = 0;
		while(x < dim.width)
		{
			if (smallest_x > coords[y * dim.width + x].x)
				smallest_x = coords[y * dim.width + x].x;
			if (smallest_y > coords[y * dim.width + x].y)
				smallest_y = coords[y * dim.width + x].y;
			if (smallest_z > coords[y * dim.width + x].z)
				smallest_z = coords[y * dim.width + x].z;
			x++;	
		}
		if (y > 0 && y % 100 == 0)
			ft_printf("100 rows analyzed for smallest\n");
		y++;
	}
	ft_printf("found smallest\n");
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
	ft_printf("adjusted smallest\n");

}

/*
universalize?
void shift_some(t_dimensions dim, t_point **coords, double offset )
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
void translate_angles(t_point *point)
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
	int count = 0;
	
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
			ft_printf("gnl error at %d attempt\n", count);
			exit(1);
			return (0);	
		} else if (!line)
			break ;
		tmp = ft_lstnew(line);
		if (!tmp)
		{
			// error in lst new
			ft_printf("lstnew error at %d attempt\n", count);
			exit(1);
			return (0);
		}
		ft_lstadd_back(&head, tmp);
		count++;
	}
	return (head);
}

t_3d_point	*alloc_data_space(t_map dim)
{
	t_3d_point	*coordinates;
	//int		i;

//	i = 0;
	// TODO: Malloc at once
//	coordinates = (t_3d_point **)ft_calloc(dim.length, sizeof(t_3d_point *));
	coordinates = (t_3d_point *)ft_calloc(dim.length * dim.width, sizeof(t_3d_point));
	if (!coordinates)
	{
		//error handling
		perror("ptp calloc fail");
		exit(1);
		return (0);
	}
	return (coordinates);
}
/*
void	fill_with_data(t_dimensions dim, t_point **coordinates, t_list *lines)
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
int	fill_with_data(t_map dim, t_list *lines)
{
	char **split_res;
	int x;
	int y;
	char **comma_split_res;
	t_3d_point *coordinates;

	coordinates = (t_3d_point *)dim.coords;
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
				coordinates[y * dim.width + x].z = ft_atoi(comma_split_res[0]);
				coordinates[y * dim.width + x].color = (int32_t)ft_strtol(comma_split_res[1], 0, 16);
	//			coordinates[y][x].color = coordinates[y][x].color << 8;
	//			coordinates[y][x].color += 0xFF; 
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

void set_max_min_z(t_map *dim)
{
	int i;
	int max_z;
	int min_z;
	t_3d_point *coords;

//TODO: handle no coords?

	coords = (t_3d_point *)dim->coords;
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

t_map get_data_from_fd(int fd)
{
	t_map dim;
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
	dim.coords = (void *)alloc_data_space(dim);
	if (!dim.coords)
	{
		//TODO: handle
		perror(strerror(errno));
		exit(1);
	}
	fill_with_data(dim, file_lines);
	set_max_min_z(&dim);
	ft_lstclear(&tmp, delete_content);
	return (dim);
	//ft_printf("%d %d\n", asd.width, asd.length);
	
}
int get_ext_coef(t_map dim)
{
	//check overflow?
/*
	sqrt(dim.width * dim.width + dim.height * dim.height)
	(0,0) - leftmost
	leftmost.x = 
	(max, max) - rightmost
	(0, max) xy - bottommost (not considering z)
	(max, 0) xy - top most (not considering z)
*/
	
	t_3d_point *coords = (t_3d_point *)dim.coords;

	t_3d_point left = coords[0];
	t_3d_point right = coords[(dim.length - 1) * dim.width + dim.width - 1];
	t_3d_point top = coords[dim.width - 1];
	t_3d_point bottom = coords[(dim.length - 1) * dim.width];

	translate_angles(&left);
	translate_angles(&right);
	translate_angles(&top);
	translate_angles(&bottom);
//	TODO: adjust for the border
	double a = WIDTH/(right.x - left.x)/2;
	double b = HEIGHT/(bottom.y - top.y)/2;
	double c = HEIGHT/(dim.max_z - dim.min_z);
	return round(((a < b) && (a < c)) * a + ((b < a) && (b < c)) * b + (c < a && c < b) * c);
}

void	process_data(t_map dim)
{
	int x;
	int y;
	int ext_coef;
	t_3d_point *coords;

	x = 0;
	y = 0;
	//ext_coef = 20;
	ext_coef = get_ext_coef(dim);
	printf("ext_coef: %d\n", ext_coef);
	coords = (t_3d_point *)dim.coords;
	while(y < dim.length)
	{
		while (x < dim.width)
		{
			extend_lines(&coords[y * dim.width + x], ext_coef);
			translate_angles(&coords[y * dim.width + x]);
//			translate_angles(&coords[y][x]);
			x++;
		}
		if (y > 0 && y % 100 == 0)
			ft_printf("100 rows processed\n");
		x = 0;
		y++;
	}
	ft_printf("all rows processed\n");
	x = 0;
	y = 0;
	
	//is this necessary?
	make_positive(dim);//, coords);
}

// assuming that the correct math has already been performed
void convert_3dto2d(t_map *dim)
{
	int	i;
	int	j;
	t_3d_point *coords;
	t_2d_point *newcoords;

	i = 0;
	j = 0;
	coords = (t_3d_point *)dim->coords;

//	TODO: write a function that allocates 2ddata at once, given length, width and size of one
//	TODO: handle malloc failes
	newcoords = calloc(sizeof(t_2d_point), dim->width * dim->length);
//	ft_printf("in convert, length: %d, width: %d\n", dim->length, dim->width);
	while (j < dim->length)
	{
		i = 0;
		while (i < dim->width)
		{
//			ft_printf("in convert j:%d, i:%d\n",j,i);
			newcoords[j * dim->width + i].x = round(coords[j * dim->width + i].x);
			newcoords[j * dim->width + i].y = round(coords[j * dim->width + i].y);
			newcoords[j * dim->width + i].color = coords[j * dim->width + i].color;
			i++;
		}
		j++;
	}
	dim->coords = (void *)newcoords;
}

void display_data(t_map dim, mlx_image_t *image)
{
//	int x;
//	int y;
//	t_point **coords;
//	coords = dim.coords;
	/*
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
	}*/
//	ft_printf("before convert");
	convert_3dto2d(&dim);
//	ft_printf("after convert");
	put_lines(image, dim);
}
