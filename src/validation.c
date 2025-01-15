/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutuzov <mbutuzov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 18:07:54 by mbutuzov          #+#    #+#             */
/*   Updated: 2025/01/15 20:17:59 by mbutuzov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static	int	is_legal_number(char *num)
{
	char	*endptr;
	long	result;

	result = ft_strtol(num, &endptr, 10);
	if (!(*endptr == '\0' || *endptr == '\n' || *endptr == ','))
		return (0);
	return (!(result < INT_MIN || result > INT_MAX));
}

static	int	validate_line(char *line)
{
	char	**line_split;
	char	**tmp_line_split;
	int		column_count;

	column_count = 0;
	line_split = ft_split(line, ' ');
	tmp_line_split = line_split;
	if (!line_split)
		return (-1);
	while (*tmp_line_split)
	{
		if (is_legal_number(*tmp_line_split))
			column_count++;
		else
		{
			column_count = -1;
			break ;
		}
		tmp_line_split++;
	}
	free_split(line_split);
	return (column_count);
}

t_map	validate_lines(t_list *lines, t_map dim)
{
	int	column_count;
	int	line_count;

	dim.length = 0;
	dim.width = 0;
	line_count = ft_lstsize(lines);
	while (lines)
	{
		column_count = validate_line((char *)lines->content);
		if (!dim.width)
			dim.width = column_count;
		if (column_count == -1)
			return (dim);
		if (dim.width != column_count)
		{
			dim.width = -1;
			return (dim);
		}
		lines = lines->next;
	}
	dim.length = line_count;
	return (dim);
}
