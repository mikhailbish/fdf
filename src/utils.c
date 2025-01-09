/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutuzov <mbutuzov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 15:52:28 by mbutuzov          #+#    #+#             */
/*   Updated: 2024/09/13 21:39:36 by mbutuzov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	free_split(char **args)
{
	char	**tmp;

	tmp = args;
	while (*args)
	{
		free(*args);
		args++;
	}
	free(tmp);
}

int	count_split(char **texts)
{
	int	i;

	i = 0;
	while (texts[i])
	{
		i++;
	}
	return (i);
}
