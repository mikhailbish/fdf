// -----------------------------------------------------------------------------
// Codam Coding College, Amsterdam @ 2022-2023 by W2Wizard.
// See README in the root project for more information.
// -----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "fdf.h"

#define WIDTH 512
#define HEIGHT 512

//#define WIDTH 2048
//#define HEIGHT 2048

static mlx_image_t* image;
static int someA;
static int someB;
static int someC;

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

void put_line()
{
	int x = 0;
	int y = 0;
	int m = someA;
	int n = someB;
	int b = someC;
	uint32_t color = ft_pixel(0xFF, 0xFF, 0xFF, 0xFF);
	if (m == 0 || (m > -1 && n > -1 && m < n) || (m < 0 && n < 0 && n > m))
	{
		while((x <  (int)image->width) && (y < (int)image->height))
		{
			y = get_straight_line_y(x, m, n, b);
			ft_printf("if m: %d, n: %d, b: %d\n", m , n, b);
	//		ft_printf("if %u %u\n", y, x);
			if (y < (int)image->height)
				mlx_put_pixel(image, x, (int)image->height - y, color);
			x++;
		}
	}
	else
	{
		while((x < (int)image->width) && (y < (int)image->height))
		{
			x = get_straight_line_x(y, m, n, b);
			ft_printf("else m: %d, n: %d, b: %d\n", m , n, b);
//			ft_printf("else %u %u\n", y, x);
	//		ft_printf("%d %d\n", y, x);
			if (y < (int)image->height)
				mlx_put_pixel(image, x, (int)image->height - y, color);
			y++;
		}

	}
}

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
