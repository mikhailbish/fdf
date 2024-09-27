// -----------------------------------------------------------------------------
// Codam Coding College, Amsterdam @ 2022-2023 by W2Wizard.
// See README in the root project for more information.
// -----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "fdf.h"

//#define WIDTH 512
//#define HEIGHT 512

#define WIDTH 1024 
#define HEIGHT 1024 

static mlx_image_t* image;
//static int someA;
//static int someB;
//static int someC;

// -----------------------------------------------------------------------------

int32_t ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

void ft_randomize(void* param)
{
	(void)param;
	for (uint32_t i = 0; i < image->width; ++i)
	{
		for (uint32_t y = 0; y < image->height; ++y)
		{
			uint32_t color = ft_pixel(
				rand() % 0xFF, // R
				rand() % 0xFF, // G
				rand() % 0xFF, // B
				rand() % 0xFF  // A
			);
			mlx_put_pixel(image, i, y, color);
		}
	}
}

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
}

// -----------------------------------------------------------------------------
/*
t_point get_k_b_from_points(t_point a, t_point b)
{

}
*/
/*
int get_straight_line_y(int x, double k, int b)
{
	return (x * k + b);
}
*/


// y = kx + b
// x = y-b   / k
/*
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

int determine_b(t_ft_point a, t_ft_point b)
{
	return ((a.x * b.y - a.y * b.x)/(a.x - b.x));
}
/*
void put_line()
{
	int x = 0;
	int y = 0;
	int m = someA;
	int n = someB;
	int b = someC;
	uint32_t color = ft_pixel(0xFF, 0xFF, 0xFF, 0xFF);
	if (m == 0 || (m > -1 && n > -1 && m < n) || (m < 0 && n < 0 && n < m))
	{
		while((x <  (int)image->width) && (y < (int)image->height))
		{
			y = get_straight_line_y(x, m, n, b);
		//	ft_printf("if x %d, y %d, m: %d, n: %d, b: %d\n", x, y, m , n, b);
	//		ft_printf("if %u %u\n", y, x);
			if (y < (int)image->height && y > -1 && x < (int)image->width && x > -1 )
				mlx_put_pixel(image, x, (int)image->height - y, color);
			x++;
		}
	}
	else
	{
		while((x < (int)image->width) && (y < (int)image->height))
		{
			x = get_straight_line_x(y, m, n, b);
		//	ft_printf("else x %d, y %d, m: %d, n: %d, b: %d\n", x, y, m , n, b);
//			ft_printf("else %u %u\n", y, x);
	//		ft_printf("%d %d\n", y, x);
			if (y < (int)image->height && y > -1 && x < (int)image->width && x > -1 )
				mlx_put_pixel(image, x, (int)image->height - y, color);
			y++;
		}

	}
}
*/
/*
t_ft_point get_mnb(t_ft_point start, t_ft_point end)
{
	return ();
}*/

void put_line(t_ft_point start, t_ft_point end)
{

	//get_mnb(start, end);
	int m;
	int n;
	int b;
	uint32_t color = ft_pixel(0xFF, 0xFF, 0xFF, 0xFF);
//	printf("%d %d\n", start.x, end.x);
//	printf("%d %d\n", start.y, end.y);
	m = determine_m(start, end);
	//printf("m: %d\n", m);
	n = determine_n(start, end);
	//printf("n: %d\n", n);
	b = determine_b(start, end);
	//printf("b: %d\n", b);
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
	if (m == 0 || (m > -1 && n > -1 && m < n) || (m < 0 && n < 0 && n < m))
	{
		//while((x <= max_x) && (y <= max_y) && (x >= min_x) &&( y >= min_y))
//		while((x <= max_x) && ((image->height - y) <= (uint32_t)max_y) && (x >= min_x) &&((image->height - y) >= (uint32_t)min_y))
// TODO: adjust for the error margins when identifying beginnings and ends of the line
		while((x <= max_x + 2) && (y <= max_y + 2) && (x >= min_x - 2) && (y >= min_y - 2))
		{
			y = get_straight_line_y(x, m, n, b);
	//		ft_printf("x: %d y: %d, max_x: %d max_y: %d, min_x: %d, min_y: %d\n", x, y, max_x, max_y, min_x, min_y);
//			if (y < (int)image->height && y > -1 && x < (int)image->width && x > -1 )
			mlx_put_pixel(image, x, (int)image->height - y, color);
			x++;
		}
	}
	else
	{
		while((x <= max_x + 2) && (y <= max_y + 2) && (x >= min_x - 2) && (y >= min_y - 2))
		{
			x = get_straight_line_x(y, m, n, b);
//			if (y < (int)image->height && y > -1 && x < (int)image->width && x > -1 )
			mlx_put_pixel(image, x, (int)image->height - y, color);
			y++;
		}
	}
}

/*
void put_line(int m, int n, int b, int top, int bot, int left, int right)
{
	int x = 0;
	int y = 0;
	int m = someA;
	int n = someB;
	int b = someC;
	uint32_t color = ft_pixel(0xFF, 0xFF, 0xFF, 0xFF);
	if (m == 0 || (m > -1 && n > -1 && m < n) || (m < 0 && n < 0 && n < m))
	{
		while((x <  (int)image->width) && (y < (int)image->height))
		{
			y = get_straight_line_y(x, m, n, b);
		//	ft_printf("if x %d, y %d, m: %d, n: %d, b: %d\n", x, y, m , n, b);
	//		ft_printf("if %u %u\n", y, x);
			if (y < (int)image->height && y > -1 && x < (int)image->width && x > -1 )
				mlx_put_pixel(image, x, (int)image->height - y, color);
			x++;
		}
	}
	else
	{
		while((x < (int)image->width) && (y < (int)image->height))
		{
			x = get_straight_line_x(y, m, n, b);
		//	ft_printf("else x %d, y %d, m: %d, n: %d, b: %d\n", x, y, m , n, b);
//			ft_printf("else %u %u\n", y, x);
	//		ft_printf("%d %d\n", y, x);
			if (y < (int)image->height && y > -1 && x < (int)image->width && x > -1 )
				mlx_put_pixel(image, x, (int)image->height - y, color);
			y++;
		}

	}
}
*/
/*
int32_t main(int argc, char **argv)
{
	if (argc != 4)
		return (EXIT_FAILURE);
	mlx_t* mlx;
	++argv;
	someA = ft_atoi(*argv);
	++argv;
	someB = ft_atoi(*argv);
	++argv;
	someC = ft_atoi(*argv);
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
	
//	mlx_loop_hook(mlx, ft_randomize, mlx);
	mlx_loop_hook(mlx, put_line, mlx);
	mlx_loop_hook(mlx, ft_hook, mlx);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}
*/

/*

#include <MLX42/MLX42.h>
//WIDTH, HEIGHT, "MLX42", true
int main()
{
	int width = 512;
	int height = 512;
	
	void *ptr = mlx_init(width, height, "MLX42", true);
	mlx_image_t *image;
	image = mlx_new_image(ptr, 128, 128);
	mlx_image_to_window(ptr, image, 0, 0);
	
	mlx_terminate(ptr);
}
*/

// not all lines shown?
//TODO: implement flood fill?
void put_lines(t_dimensions dim, t_ft_point **coords)
{
	int y;
	int x;

	y = 0;
	x = 0;
	while(y < dim.length)
	{
		while(x < dim.width)
		{
			if ((y + 1) < dim.length)
				put_line(coords[y][x], coords[y + 1][x]);
			if ((x + 1) < dim.width)
				put_line(coords[y][x + 1], coords[y][x]);
	//		if ((x - 1) > 0)
	//			put_line(coords[y][x - 1], coords[y][x]);
	//		if ((y - 1) > 0)
	//			put_line(coords[y - 1][x], coords[y][x]);
			x++;
		}
		x = 0;
		y++;
	}
}
void put_42(void *param)
{
//	TODO: move out parsing
	int fd;
	fd = open(((t_name_holder *)param)->file_name, O_RDONLY);
	t_dimensions image_size = ((t_name_holder *)param)->image_size;
	t_dimensions dim;
//	uint32_t color = ft_pixel(0xFF, 0xFF, 0xFF, 0xFF);

	if (fd < 0)
	{
/*		if (errno)
		{
			perror(strerror(errno));
		}
*/
		perror("Cannot find file");
//		TODO: handle
//		return (1);
	}
	
	t_list *file_lines = get_file_lines(fd);
	close(fd);
	t_list *tmp = file_lines;

	dim = validate_lines(file_lines);
	t_ft_point	**coords = alloc_data_space(dim);
	

	fill_with_data(dim, coords, file_lines);
	ft_lstclear(&tmp, delete_content);
	//ft_printf("%d %d\n", asd.width, asd.length);
	int x = 0;
	int y = 0;
	int ext_coef = 40;
	
	while(y < dim.length)
	{
		while (x < dim.width)
		{
			extend_lines(&coords[y][x], ext_coef);
			translate_angles(&coords[y][x]);
			x++;
		}
		x = 0;
		y++;
	}
	x = 0;
	y = 0;

	make_positive(dim, coords);
	while(y < dim.length)
	{
		while (x < dim.width)
		{
//			ft_printf("yo!");
		//	ft_printf("in a loop, x: %d, y: %d, z: %d\n", coords[y][x].x, coords[y][x].y, coords[y][x].z);
// TODO: come up with a correct translation of coordinates onto image
			if (coords[y][x].x < image_size.width && coords[y][x].y < image_size.length )
			{
//				ft_printf("in a loop, x: %d, y: %d, z: %d\n", coords[y][x].x, coords[y][x].y, coords[y][x].z);
	//			mlx_put_pixel(image, (uint32_t)coords[y][x].x, (uint32_t)image_size.length - (uint32_t)coords[y][x].y, color);
			}
			else
			{
				perror("image too small");
				exit(1);
			}
			x++;
		}
//		ft_printf("\n");
		x = 0;
		y++;
	}
	
	put_lines(dim, coords);
//	put_line(coords[2][2], coords[2][3]);
//	ft_printf("__________________________________________________________________________");
	// TODO: free coords
}

// TODO: check what happens if you change space to tab
/*int main(int argc, char **argv)
{}{
	if (argc != 2)
		return (1);
	argv++;
	int fd = open(*argv, O_RDONLY);
	t_dimensions dim;

	if (fd < 0)
	{
		perror("Cannot find file");
		return (1);
	}

	t_list *file_lines = get_file_lines(fd);
	close(fd);
	t_list *tmp = file_lines;

	dim = validate_lines(file_lines);
	t_ft_point	**coords = alloc_data_space(dim);

	fill_with_data(dim, coords, file_lines);
	//ft_printf("%d %d\n", asd.width, asd.length);
	int x = 0;
	int y = 0;

	
	while(y < dim.length)
	{
		while (x < dim.width)
		{
//			coords[x][y]
			translate_angles(&coords[y][x]);
			ft_printf("%d ",coords[y][x].x);
			//file_lines = file_lines->next;
			x++;
		}
		ft_printf("\n");
		x = 0;
		y++;
	}
	ft_lstclear(&tmp, delete_content);
	return (0);
}*/

int32_t main(int argc, char **argv)
{
	if (argc != 2)
		return (EXIT_SUCCESS);
//		return (EXIT_FAILURE);
	mlx_t* mlx;
	t_name_holder some;
/*	++argv;
	someA = ft_atoi(*argv);
	++argv;
	someB = ft_atoi(*argv);
	++argv;
	someC = ft_atoi(*argv);*/
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
	some.file_name = *(++argv);
	some.image_size = (t_dimensions){HEIGHT, WIDTH};
//	mlx_loop_hook(mlx, ft_randomize, mlx);
//	mlx_loop_hook(mlx, put_line, mlx);
	mlx_loop_hook(mlx, put_42, &some);
	mlx_loop_hook(mlx, ft_hook, mlx);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}
