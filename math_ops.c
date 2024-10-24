/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_ops.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutuzov <mbutuzov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 20:26:55 by mbutuzov          #+#    #+#             */
/*   Updated: 2024/10/24 20:27:35 by mbutuzov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	mutate_3d_vector(double vector[3], double matrix[3][3])
{
	double	original_x;
	double	original_y;
	double	original_z;

	original_x = vector[0];
	original_y = vector[1];
	original_z = vector[2];
	vector[0] = matrix[0][0] * original_x
		+ matrix[0][1] * original_y + matrix[0][2] * original_z;
	vector[1] = matrix[1][0] * original_x
		+ matrix[1][1] * original_y + matrix[1][2] * original_z;
	vector[2] = matrix[2][0] * original_x
		+ matrix[2][1] * original_y + matrix[2][2] * original_z;
}
