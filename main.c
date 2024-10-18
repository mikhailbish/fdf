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

#define WIDTH 2048 
#define HEIGHT 600 


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

/*
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
//	int rem_i;
	int i;
	int step_counter;
	uint32_t color = ft_pixel(0xFF, 0xFF, 0xFF, 0xFF);

	step_counter = 0;
	dx = end.x - start.x;
	dy = end.y - start.y;
	d = ft_abs(ft_abs(dx) - ft_abs(dy));
	x_step = -1 * (dx < 0) + (dx > 0);
	y_step = -1 * (dy < 0) + (dy > 0);
	
	min = (d / dy) * (ft_abs(dx) > ft_abs(dy));
	min += (d / dx) * (ft_abs(dx) < ft_abs(dy));
	rem = (d % dy) * (ft_abs(dx) > ft_abs(dy));
	rem += (d % dx) * (ft_abs(dx) < ft_abs(dy));
	x = start.x;
	y = start.y;
//	rem_i = 0;
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
	// dy 7, rem 4
	// 7/4
	// 1 3/4
	// 1 3 5 6
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
*/

//needs testing
int32_t get_red(int32_t color)
{
	return ((color >> 16) & 0xFF);
}

int32_t get_green(int32_t color)
{
	return ((color >> 8) & 0xFF);
}

int32_t get_blue(int32_t color)
{
	return ((color) & 0xFF);
}

int get_color(int start_color, int end_color, int i, int a, int b)
{
	int red_change;
	int green_change;
	int blue_change;
	int final_red;
	int final_green;
	int final_blue;

	red_change = get_red(end_color) - get_red(start_color);
	green_change = get_green(end_color) - get_green(start_color);
	blue_change = get_blue(end_color) - get_blue(start_color);

	//total_cchange = ft_abs(start_color - end_color);
	if (i == 0 || (start_color == end_color))
	{
//		ft_printf("color case 1\n");
		return (start_color);
	}
	if (a + i == b)
	{
//		ft_printf("color case 2\n");
		return (end_color);
	}
//	ft_printf("color case 3\n");
	final_red = round((double)get_red(start_color) + (double)((double)(i * (red_change)) / (double)(b - a)));
	final_green = round((double)get_green(start_color) + (double)((double)(i * (green_change)) / (double)(b - a)));
	final_blue = round((double)get_blue(start_color) + (double)((double)(i * (blue_change)) / (double)(b - a)));
//	if (final_red > 0xFF || final_blue > 0xFF || final_green > 0xFF)
//		ft_printf("color change issue");
	return (final_red << 16 | final_green << 8 | final_blue);
	//else
	//	return
	
}

// WIP
void put_line_low(t_ft_point start, t_ft_point end, mlx_image_t *image)
{
	int dx;
	int dy;
	int step_y;
	int d;
	int color;

	dx = end.x - start.x;
	dy = end.y - start.y;
	step_y = 1;
	if (dy < 0)
	{
		step_y = -1;
		dy = -dy;
	}
	d = (2 * dy) - dx;
	while (start.x <= end.x)
	{
		// TODO: modify color handling here
		color = get_color(start.color, end.color, start.x, end.x - dx, end.x);
//		color = 0xFFFFFF;
		mlx_put_pixel(image, start.x, image->height - (start.y), (color << 8) + 0xFF);
		if (d > 0)	
		{
			start.y += step_y;
			d += 2 * (dy - dx);
		}
		else
			d += 2 * dy;
		start.x++;
	}
}

void put_line_high(t_ft_point start, t_ft_point end, mlx_image_t *image)
{
	int dx;
	int dy;
	int d;
	int step_x;
	int color;

	dx = end.x - start.x;
	dy = end.y - start.y;
	step_x = 1;
	if (dx < 0)
	{
		step_x = -1;
		dx = -dx;
	}
	d = (2 * dx) - dy;
	while (start.y <= end.y)
	{
		// TODO: modify color handling here
		color = get_color(start.color, end.color, start.y, ( -end.y + dy), image->height - end.y);
//		color = 0xFFFFFF;
		mlx_put_pixel(image, start.x, image->height - (start.y), (color << 8) + 0xFF);
		if (d > 0)	
		{
			start.x += step_x;
			d += 2 * (dx - dy);
		}
		else
			d += 2 * dx;
		start.y++;
	}
}

void put_line(t_ft_point start, t_ft_point end, mlx_image_t *image)
{
	if (ft_abs(end.y - start.y) < ft_abs(end.x - start.x))
	{
		if (start.x > end.x)
			put_line_low(end, start, image);
		else
			put_line_low(start, end, image);
	}
	else
	{
		if (start.y > end.y)
			put_line_high(end, start, image);
		else
			put_line_high(start, end, image);
	}
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
//				ft_printf("pls case 1 x: %d, y: %d\n", x, y);
	//			ft_printf("y, x: %d, %d\n", y, x);
//				ft_printf("x1: %d, y1 %d\nx2: %d, y2: %d\n", coords[y][x].x, coords[y][x].y, coords[y + 1][x].x, coords[y + 1][x].y);
				put_line(coords[y][x], coords[y + 1][x], image);
				line_count +=1;
			}
			else if ((x < (dim.width - 1)) && (y == (dim.length - 1)))
			{
//				ft_printf("pls case 2 x: %d, y: %d\n", x, y);
				put_line(coords[y][x], coords[y][x + 1], image);
//				ft_printf("x1: %d, y1 %d\nx2: %d, y2: %d\n", coords[y][x].x, coords[y][x].y, coords[y][x + 1].x, coords[y][x + 1].y);
				line_count +=1;
			}
			else if ((x == (dim.width - 1)) && (y == (dim.length - 1)))
			{
			}
			else {
//				ft_printf("pls case 3 x: %d, y: %d\n", x, y);
				put_line(coords[y][x], coords[y + 1][x], image);
//				ft_printf("x1: %d, y1 %d\nx2: %d, y2: %d\n", coords[y][x].x, coords[y][x].y, coords[y + 1][x].x, coords[y + 1][x].y);
				put_line(coords[y][x - 1], coords[y][x], image);
//				ft_printf("x1: %d, y1 %d\nx2: %d, y2: %d\n", coords[y][x - 1].x, coords[y][x - 1].y, coords[y][x].x, coords[y][x].y);
				line_count +=2;
			}
			x--;
		}
		y++;
	}
//	ft_printf("line_count = %d\n", line_count);
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
			//ft_printf("x: %d, y: %d, z: %d, color: %x\n", coords[i][j].x, coords[i][j].y, coords[i][j].z, coords[i][j].color);
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
	ft_printf("done parsing\n");
//	display_coords_testing(dim);

	//TODO: close in the middle if error
	close(fd);
	process_data(dim);
	ft_printf("done processing\n");
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
