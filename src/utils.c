/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutuzov <mbutuzov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 15:52:28 by mbutuzov          #+#    #+#             */
/*   Updated: 2025/01/09 20:33:35 by mbutuzov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	ft_abs(int num)
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
