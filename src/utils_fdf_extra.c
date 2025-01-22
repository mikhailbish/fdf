/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_fdf_extra.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutuzov <mbutuzov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 20:34:55 by mbutuzov          #+#    #+#             */
/*   Updated: 2025/01/22 20:35:08 by mbutuzov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	paint_black_square(t_fdf fdf)
{
	unsigned int	i;
	unsigned int	max;
	int32_t			*ptr;

	max = fdf.image->width * fdf.image->height;
	i = 0;
	ptr = (int32_t *)fdf.aquarium->pixels;
	while (i < max)
		ptr[i++] = 0xFF000000;
}
