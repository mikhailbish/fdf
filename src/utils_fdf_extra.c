/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_fdf_extra.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutuzov <mbutuzov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 20:34:55 by mbutuzov          #+#    #+#             */
/*   Updated: 2025/01/30 18:09:32 by mbutuzov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	paint_black_square(t_fdf fdf)
{
	uint32_t	i;
	uint32_t	max;
	int32_t		*ptr;

	if (!fdf.aquarium)
		return ;
	max = fdf.aquarium->width * fdf.aquarium->height;
	i = 0;
	ptr = (int32_t *)fdf.aquarium->pixels;
	while (i < max)
		ptr[i++] = 0xFF000000;
}
