/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_extra2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutuzov <mbutuzov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 18:14:38 by mbutuzov          #+#    #+#             */
/*   Updated: 2025/01/30 18:29:08 by mbutuzov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	remove_new_line(char *content)
{
	size_t	line_length;

	if (content)
	{
		line_length = ft_strlen(content);
		if (line_length > 0 && content[line_length - 1] == '\n')
			content[line_length - 1] = 0;
	}
}

void	reset_background_image(uint32_t uwidth, uint32_t uheight, t_fdf *fdf)
{
	mlx_image_t	*aquarium;

	if (fdf->aquarium)
	{
		aquarium = fdf->aquarium;
		fdf->aquarium = 0;
		mlx_delete_image(fdf->mlx, aquarium);
	}
	fdf->aquarium = mlx_new_image(fdf->mlx, uwidth, uheight);
	if (!fdf->aquarium)
		free_fdf_parts_and_exit_error(*fdf, "Can't realoc new image\n");
	if (mlx_image_to_window(fdf->mlx, fdf->aquarium, 0, 0) == -1)
		free_fdf_parts_and_exit_error(*fdf, "Image to window fail\n");
	mlx_set_instance_depth(fdf->aquarium->instances, -1);
	paint_black_square(*fdf);
}
