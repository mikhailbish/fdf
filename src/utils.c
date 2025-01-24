/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutuzov <mbutuzov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 18:07:33 by mbutuzov          #+#    #+#             */
/*   Updated: 2025/01/24 19:22:21 by mbutuzov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int32_t	ft_abs(int32_t num)
{
	if (num < 0)
		return (-num);
	return (num);
}

void	ft_free(void **adr)
{
	if (*adr)
	{
		free(*adr);
		*adr = 0;
	}
}

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
