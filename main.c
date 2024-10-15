// -----------------------------------------------------------------------------
// Codam Coding College, Amsterdam @ 2022-2023 by W2Wizard.
// See README in the root project for more information.
// -----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "fdf.h"
// normal minilibx problems: 317955 bytes in 3106 blocks
//#define WIDTH 512
//#define HEIGHT 512

#define WIDTH 1024 
#define HEIGHT 1024 


int32_t ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}
/*
void ft_hook(void* param)
{
	mlx_t* mlx = param;

	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
	if (mlx_is_key_down(mlx, MLX_KEY_UP))
		image->instances[0].y -= 5;
	if (mlx_is_key_down(mlx, MLX_KEY_DOWN))
		image->instances[0].y += 5;
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
		image->instances[0].x -= 5;
	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
		image->instances[0].x += 5;
}*/

// -----------------------------------------------------------------------------
/*
	starting point 
	y = kx + b

	could be imagined as y = (m/n) * x + b

*/
int get_straight_line_y(int x, int m, int n, int b)
{
	if (m == 0 || n == 0)
		return (b);
	return (((x * m) / n) + b);
}

int get_straight_line_x(int y, int m, int n, int b)
{
	if (m == 0 || n == 0)
		return (0);
	return (((y - b) * n) / m);
}

int determine_m(t_ft_point a, t_ft_point b)
{
	return (b.y - a.y);
}

int determine_n(t_ft_point a, t_ft_point b)
{
	return (b.x - a.x);
}
/* fails when a.x == b.x */
int determine_b(t_ft_point a, t_ft_point b)
{
	if (a.x - b.x)
		return ((a.x * b.y - a.y * b.x)/(a.x - b.x));
	return (0);
}
/*
void put_line(t_ft_point start, t_ft_point end, mlx_image_t *image)
{
	int m;
	int n;
	int b;
	uint32_t color = ft_pixel(0xFF, 0xFF, 0xFF, 0xFF);
	m = determine_m(start, end);
	n = determine_n(start, end);
	b = determine_b(start, end);
	uint32_t min_x;
	uint32_t min_y;
	uint32_t max_x;
	uint32_t max_y;
	min_x = (start.x > end.x) ? end.x : start.x;
	min_y = (start.y > end.y) ? end.y : start.y;
	max_x = (start.x > end.x) ? start.x : end.x;
	max_y = (start.y > end.y) ? start.y : end.y;
	uint32_t x = min_x;
	uint32_t y = min_y;
	//TODO: don't cast image height to int?
//	ft_printf("in put_line\n");
	if (m == 0 || (m > -1 && n > -1 && m < n) || (m < 0 && n < 0 && n < m))
	{
//		ft_printf("case 1\n");
//		ft_printf("x: %d, y: %d, m: %d, n: %d\n", x, y, m, n);
		while((x <= max_x + 2) && (y <= max_y + 2) && (x >= min_x - 2) && (y >= min_y - 2))
		{
			
			y = get_straight_line_y(x, m, n, b);
			mlx_put_pixel(image, x, image->height - y, color);
			x++;
		}
	}
	else
	{
//		ft_printf("case 2\n");
//		ft_printf("x: %d, y: %d, m: %d, n: %d\n", x, y, m, n);
		while((x <= max_x + 2) && (y <= max_y + 2) && (x >= min_x - 2) && (y >= min_y - 2))
		{
			x = get_straight_line_x(y, m, n, b);
			mlx_put_pixel(image, x, image->height - y, color);
			y++;
		}
	}
}
*/
int ft_abs(int num)
{
	if (num < 0)
		return (-num);
	return (num);
}
/*
void put_line(t_ft_point start, t_ft_point end, mlx_image_t *image)
{
	int dx;
	int dy;
	int x;
	int y;
	int d;
	uint32_t color = ft_pixel(0xFF, 0xFF, 0xFF, 0xFF);
	int i = 0; //x
	int j = 0; //y
	//(1, 4)
	//(4, 6)
	// dx -3
	// dy -2
	// d -1

	dx = start.x - end.x;
	dy = start.y - end.y;
	d = ft_abs(ft_abs(dx) - ft_abs(dy));
	
//	ft_printf("dx: %d dy: %d d: %d\n", dx, dy, d);

	if (ft_abs(dx) > ft_abs(dy)) // 
	{
		if (dx > 0)
		{
			while (i < dx)
			{
				mlx_put_pixel(image, start.x + i, image->height - (start.y + j), color);
				while ()
				{
					mlx_put_pixel(image, start.x + i, image->height - (start.y + j), color);
				}
				i++;
				j++;
			}
		}
	}
	x = start.x;
	y = start.y;
	mlx_put_pixel(image, x, image->height - y, color);
	x = end.x;
	y = end.y;
	mlx_put_pixel(image, x, image->height - y, color);

}
*/
void put_line(t_ft_point start, t_ft_point end, mlx_image_t *image)
{
	int dx;
	int dy;
	int d;
	int x_step;
	int y_step;
	int x;
	int y;
	int min;	
	int rem;
	int i;
	int step_counter;
	uint32_t color = ft_pixel(0xFF, 0xFF, 0xFF, 0xFF);

	step_counter = 0;
	dx = end.x - start.x;
	dy = end.y - start.y;
	d = ft_abs(ft_abs(dx) - ft_abs(dy));
	x_step = -1 * (dx < 0) + (dx > 0);
	y_step = -1 * (dy < 0) + (dy > 0);
	
//	ft_printf("put pixel in ")
	if (ft_abs(dx) > ft_abs(dy))
	{
		min = d / dy;
		rem = d % dy;
	} else if (ft_abs(dx) < ft_abs(dy))
	{
		min = d / dx;
		rem = d % dx;
	}
	else
	{
		min = 0;
		rem = 0;
	}
	x = start.x;
	y = start.y;
//	ft_printf("bp 1\nrem: %d\nmin: %d\n");

	while ((x != end.x && y != end.y) && (step_counter < (ft_abs(dx) + ft_abs(dy))) )
	{
	// reconsider order of operations (move along "larger" axis and then move diagonally)
		x += x_step;
		y += y_step;
		mlx_put_pixel(image, x, image->height - (y), color);
		step_counter++;
		i = 0;
		if (ft_abs(dx) > ft_abs(dy))
		{
			while (i < min)
			{			
				x += x_step;
				mlx_put_pixel(image, x, image->height - (y), color);
				step_counter++;
				i++;
			}
	// how to spread rem evenly
			if (rem)
			{
				x += x_step;
				mlx_put_pixel(image, x, image->height - (y), color);
				rem--;
				step_counter++;
			}

		} else if (ft_abs(dx) < ft_abs(dy))
		{
			while (i < min)
			{			
				y += y_step;
				mlx_put_pixel(image, x, image->height - (y), color);
				step_counter++;
				i++;
			}
			if (rem)
			{
				y += y_step;
				mlx_put_pixel(image, x, image->height - (y), color);
				rem--;
				step_counter++;
			}
		}
	}
	ft_printf("x: %d end.x: %d\ny: %d end.y: %d\n", x, end.x, y, end.y);
}


// not all lines shown?
// TODO: include every possible line
void put_lines(mlx_image_t *image, t_dimensions dim, t_ft_point **coords)
{
	int y;
	int x;

	y = 0;
	int line_count = 0;
	while(y < dim.length)
	{
		x = dim.width - 1;
		while(x > - 1)
		{
	//		ft_printf("y, x: %d, %d\n", y, x);
	//		ft_printf("y, x: %d, %d\n", coords[y][x].y, coords[y][x].x);
			if (x == 0 && y < dim.length - 1)
			{
				ft_printf("pls case 1 x: %d, y: %d\n", x, y);
	//			ft_printf("y, x: %d, %d\n", y, x);
				ft_printf("x1: %d, y1 %d\nx2: %d, y2: %d\n", coords[y][x].x, coords[y][x].y, coords[y + 1][x].x, coords[y + 1][x].y);
				put_line(coords[y][x], coords[y + 1][x], image);
				line_count +=1;
			}
			else if ((x < (dim.width - 1)) && (y == (dim.length - 1)))
			{
				ft_printf("pls case 2 x: %d, y: %d\n", x, y);
				put_line(coords[y][x], coords[y][x + 1], image);
				ft_printf("x1: %d, y1 %d\nx2: %d, y2: %d\n", coords[y][x].x, coords[y][x].y, coords[y][x + 1].x, coords[y][x + 1].y);
				line_count +=1;
			}
			else if ((x == (dim.width - 1)) && (y == (dim.length - 1)))
			{
			}
			else {
				ft_printf("pls case 3 x: %d, y: %d\n", x, y);
				put_line(coords[y][x], coords[y + 1][x], image);
				ft_printf("x1: %d, y1 %d\nx2: %d, y2: %d\n", coords[y][x].x, coords[y][x].y, coords[y + 1][x].x, coords[y + 1][x].y);
				put_line(coords[y][x - 1], coords[y][x], image);
				ft_printf("x1: %d, y1 %d\nx2: %d, y2: %d\n", coords[y][x - 1].x, coords[y][x - 1].y, coords[y][x].x, coords[y][x].y);
				line_count +=2;
			}
			x--;
		}
		y++;
	}
	ft_printf("line_count = %d\n", line_count);
}

void put_42_v2(void *param)
{
	t_dimensions dim;
	t_dimensions image_size;
	mlx_image_t	*image;
	int painted;
	painted = ((t_name_holder *)param)->painted;
	if (!painted)
	{
		dim = ((t_name_holder *)param)->dim;
		image_size = ((t_name_holder *)param)->image_size;
		image = ((t_name_holder *)param)->image;
		display_data(dim, image_size, image);
		((t_name_holder *)param)->painted = 1;
	}
}

//TODO: remove
void display_coords_testing(t_dimensions dim)
{
	int i = 0;
	int j = 0;
	t_ft_point **coords;
	coords = dim.coords;
	while (i < dim.length)
	{
		while (j < dim.width)
		{
			ft_printf("x: %d, y: %d, z: %d\n", coords[i][j].x, coords[i][j].y, coords[i][j].z);
			j++;
		}
		j = 0;
		i++;
	}
}

int32_t main(int argc, char **argv)
{
	int fd;
	mlx_image_t* image;
	t_dimensions dim;
	if (argc != 2)
		return (EXIT_SUCCESS);
//		return (EXIT_FAILURE);
	mlx_t* mlx;
	t_name_holder some;
	fd = open(*(++argv), O_RDONLY);
	dim = get_data_from_fd(fd);
	//TODO: close in the middle if error
	close(fd);
	process_data(dim);
	// Gotta error check this stuff
	if (!(mlx = mlx_init(WIDTH, HEIGHT, "MLX42", true)))
	{
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
//	if (!(image = mlx_new_image(mlx, 1024, 1024)))
	if (!(image = mlx_new_image(mlx, WIDTH, HEIGHT)))
	{
		mlx_close_window(mlx);
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	if (mlx_image_to_window(mlx, image, 0, 0) == -1)
	{
		mlx_close_window(mlx);
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	some.mlx = mlx;
	some.image = image;
	//TODO: remove file name here and in the header
	some.file_name = *(++argv);
	some.image_size = (t_dimensions){0, HEIGHT, WIDTH};
	some.image = image;
	some.dim = dim;
	some.painted = 0;
//	mlx_loop_hook(mlx, ft_randomize, mlx);
//	mlx_loop_hook(mlx, put_line, mlx)
	mlx_loop_hook(mlx, put_42_v2, &some);
//	mlx_loop_hook(mlx, ft_hook, mlx);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}
