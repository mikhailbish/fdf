/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 18:39:57 by mbutuzov          #+#    #+#             */
/*   Updated: 2024/10/25 19:08:55 by mbutuzov         ###   ########.fr       */
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

void	delete_content(void *content)
{
	free((char *)content);
}

double	get_radians(double angle)
{
	return ((angle * M_PI) / 180);
}

void	extend_lines(t_3d_point *point, double num)
{
	double	vector[3];
	double	matrix[3][3];

	vector[0] = point->x;
	vector[1] = point->y;
	vector[2] = point->z;
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

void	rotate_x(t_3d_point *point, double angle)
{
	double	vector[3];
	double	matrix[3][3];

	vector[0] = (double)point->x;
	vector[1] = (double)point->y;
	vector[2] = (double)point->z;
	matrix[0][0] = 1;
	matrix[0][1] = 0;
	matrix[0][2] = 0;
	matrix[1][0] = 0;
	matrix[1][1] = cos(get_radians(angle));
	matrix[1][2] = sin(get_radians(angle));
	matrix[2][0] = 0;
	matrix[2][1] = -sin(get_radians(angle));
	matrix[2][2] = cos(get_radians(angle));
	mutate_3d_vector(vector, matrix);
	point->x = vector[0];
	point->y = vector[1];
	point->z = vector[2];
}

void	rotate_y(t_3d_point *point, double angle)
{
	double	vector[3];
	double	matrix[3][3];

	vector[0] = (double)point->x;
	vector[1] = (double)point->y;
	vector[2] = (double)point->z;
	matrix[0][0] = cos(get_radians(angle));
	matrix[0][1] = 0;
	matrix[0][2] = -sin(get_radians(angle));
	matrix[1][0] = 0;
	matrix[1][1] = 1;
	matrix[1][2] = 0;
	matrix[2][0] = -sin(get_radians(angle));
	matrix[2][1] = 0;
	matrix[2][2] = cos(get_radians(angle));
	mutate_3d_vector(vector, matrix);
	point->x = vector[0];
	point->y = vector[1];
	point->z = vector[2];
}

void	rotate_z(t_3d_point *point, double angle)
{
	double	vector[3];
	double	matrix[3][3];

	vector[0] = (double)point->x;
	vector[1] = (double)point->y;
	vector[2] = (double)point->z;
	matrix[0][0] = cos(get_radians(angle));
	matrix[0][1] = -sin(get_radians(angle));
	matrix[0][2] = 0;
	matrix[1][0] = sin(get_radians(angle));
	matrix[1][1] = cos(get_radians(angle));
	matrix[1][2] = 0;
	matrix[2][0] = 0;
	matrix[2][1] = 0;
	matrix[2][2] = 1;
	mutate_3d_vector(vector, matrix);
	point->x = vector[0];
	point->y = vector[1];
	point->z = vector[2];
}

void	translate_angles(t_3d_point *point)
{
	rotate_z(point, -45.264);
	rotate_x(point, -35);
}

void	shift_x(t_map dim, t_3d_point *coords, double offset)
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

void	shift_y(t_map dim, t_3d_point *coords, double offset)
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

void	make_positive(t_map *dim)
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

t_list	*get_file_lines(int fd)
{
	char	*line;
	t_list	*head;
	t_list	*tmp;
	int		count;

	count = 0;
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
//			free lines
		// error in lst new
		free(line);
		return (0);
	}
	while (line)
	{
		line = get_next_line(fd);
// TODO: replace errno - no global variables
// if gnl == 0 assume there is nothing more to read
// may be don't use gnl
		if (!line && errno == ENOMEM)
		{
//			free lines
//			free list
			//error in gnl
			ft_printf("gnl error at %d attempt\n", count);
			exit(1);
			return (0);
		}
		else if (!line)
			break ;
		tmp = ft_lstnew(line);
		if (!tmp)
		{
//			free lines
//			free list
			// error in lst new
			free(line);
			ft_lstclear(&head, free);
			ft_printf("lstnew error at %d attempt\n", count);
			exit(1);
			return (0);
		}
		ft_lstadd_back(&head, tmp);
		count++;
	}
	return (head);
}

// TODO: add to utils
// should check for adr?
void ft_free(void **adr)
{
	if (*adr)
	{
		free(*adr);
		*adr = 0;
	}
}
t_map	*alloc_data_space(t_map *dim)
{
	t_3d_point	*coords_3d;
	t_2d_point	*coords_display;
	int	max;

	max = dim->length * dim->width;
	coords_3d = ft_calloc(max, sizeof(t_3d_point));
	coords_display = ft_calloc(max, sizeof(t_2d_point));
	if (!coords_3d || !coords_display)
	{
		ft_free((void **)&coords_3d);
		ft_free((void **)&coords_display);
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
t_map	get_data_from_fd(int fd)
{
	t_map	dim;
	t_list	*file_lines;
	t_list	*tmp;

	file_lines = get_file_lines(fd);
	// handle malloc
	// inner stuff from gfl would be already free, prevent further program exec, close fd here??
	//close(fd); // handle outside
	tmp = file_lines;
	dim = validate_lines(file_lines);
	if (dim.width == -1)
	{
		//TODO: free file lines, leave
	}
	
	// handle malloc
	if (!alloc_data_space(&dim))
	{
		//free lines
		//TODO: handle
		ft_lstclear(&tmp, delete_content);
		perror(strerror(errno));
		exit(1);
	}
	fill_with_data(dim, file_lines);
//	display_coords_testing(dim);
	set_max_min_z(&dim);
	ft_lstclear(&tmp, delete_content);
	return (dim);
}

//TODO: work on ext coef

double	get_ext_coef(t_map dim)
{
	double	a;
	double	b;
	double	c;

// screen width, 
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

t_2d_point	point_3dto2d(t_3d_point point_3d )
{
	t_2d_point point_2d;

	point_2d.x = round(point_3d.x);
	point_2d.y = round(point_3d.y);
	point_2d.color = point_3d.color;
	return (point_2d);
}
// assuming that the correct math has already been performed
void	convert_3dto2d(t_map *dim)
{
	t_3d_point	*coords;
	t_2d_point	*new_coords;
	int			i;
	int			max;

	max = dim->width * dim->length;
	i = 0;
	coords = (t_3d_point *)dim->coords_3d;
	new_coords = dim->coords_display;
	while (i < max)
	{
		new_coords[i] = point_3dto2d(coords[i]);
		i++;
	}
	
	dim->coords_display = (void *)new_coords;
}

void	display_data(t_map dim, mlx_image_t *image)
{
	ft_printf("before convert\n");
	convert_3dto2d(&dim);
	ft_printf("after convert\n");
	put_lines(image, dim);
	ft_printf("after put lines\n");
}
