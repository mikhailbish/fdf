/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutuzov <mbutuzov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 15:59:15 by mbutuzov          #+#    #+#             */
/*   Updated: 2025/01/14 17:43:04 by mbutuzov         ###   ########.fr       */
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

/*

push_swap " " error
push_swap "" error
push_swap

*/

static	int	validate_line(char *line)
{
	char	**line_split;
	char	**tmp_line_split;
	int	column_count;

	column_count = 0;
	line_split = ft_split(line, ' ');
	tmp_line_split = line_split;
	if (!line_split)
	{
		//TODO: introduce error messages?
		//some error handling
		ft_printf("problems in validate line split\n");
		return (-1);
	}
	while (*tmp_line_split)
	{
		if (is_legal_number(*tmp_line_split))
			column_count++;
		else
		{
			ft_printf("illegal number\n");
			column_count = -1;
			break;
		}
		tmp_line_split++;
	}
	free_split(line_split);
	return (column_count);
}

// TODO: make sure errors are handled
t_map	validate_lines(t_list *lines)
{
	int	column_count;
	int	line_count;
	//char	*line;
	t_map	dim;

	dim.length = 0;
	dim.width = 0;
	line_count = ft_lstsize(lines);
	while(lines)
	{
		column_count = validate_line((char *)lines->content);
		if (!dim.width)
			dim.width = column_count;
		if (column_count == -1)
		{
			perror("memory error at validation\n");
			return (dim);
		}
		if (dim.width != column_count)
		{
//			wrong number of columns in a line
		}
		lines = lines->next;
	}
	dim.length = line_count;
	return (dim);
	
}
