/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutuzov <mbutuzov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 18:39:49 by mbutuzov          #+#    #+#             */
/*   Updated: 2024/09/12 21:58:15 by mbutuzov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include "libft.h"
# include <MLX42/MLX42.h>
# include <fcntl.h>
# include <stdio.h>

typedef struct s_ft_point {
	int x;
	int y;
	int z;
}	t_ft_point;

int check_name(char *name);


#endif
