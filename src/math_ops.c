/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_ops.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutuzov <mbutuzov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 18:06:54 by mbutuzov          #+#    #+#             */
/*   Updated: 2025/01/21 11:21:57 by mbutuzov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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
	matrix[1][1] = cos(angle);
	matrix[1][2] = sin(angle);
	matrix[2][0] = 0;
	matrix[2][1] = -sin(angle);
	matrix[2][2] = cos(angle);
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
	matrix[0][0] = cos(angle);
	matrix[0][1] = 0;
	matrix[0][2] = -sin(angle);
	matrix[1][0] = 0;
	matrix[1][1] = 1;
	matrix[1][2] = 0;
	matrix[2][0] = -sin(angle);
	matrix[2][1] = 0;
	matrix[2][2] = cos(angle);
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
	matrix[0][0] = cos(angle);
	matrix[0][1] = -sin(angle);
	matrix[0][2] = 0;
	matrix[1][0] = sin(angle);
	matrix[1][1] = cos(angle);
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
	rotate_z(point, get_radians(-45));
//	rotate_x(point, get_radians(-35.264));
//	rotate_x(point, -atan(1 / sqrt(2)));
	rotate_x(point, -atanh(1 / sqrt(2)));
}
