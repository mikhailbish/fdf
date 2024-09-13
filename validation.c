/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutuzov <mbutuzov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 15:59:15 by mbutuzov          #+#    #+#             */
/*   Updated: 2024/09/13 22:08:54 by mbutuzov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	is_legal_number(char *num)
{
	char	*endptr;
	long	result;

	result = ft_strtol(num, &endptr, 10);
	if (*endptr != '\0')
		return (0);
	return (!(result < INT_MIN || result > INT_MAX));
}

/*

push_swap " " error
push_swap "" error
push_swap

*/

static int	validate_line(char *line)
{
	char	**line_split;
	char	**tmp_line_split;
	int	column_count;

	column_count = 0;
	line_split = ft_split(line, ' ');
	tmp_line_split = line_split;
	if (!line_split)
	{
		//some error handling
		return (-1);
	}
	while (*tmp_line_split)
	{
		ft_printf("column\n");
		// add to coordinate matrix
		if (is_legal_number(*tmp_line_split))
			column_count++;
		else
		{
			ft_printf("illegal num\n");
			column_count = -1;
			break;
		}
		tmp_line_split++;
	}
	free_split(line_split);
	return (column_count);
}

t_dimensions validate_file(int fd)
{
	int 	column_count;
	int	line_count;
	char	*line;
	t_dimensions dim;

	dim.length = 0;
	dim.width = 0;

	line_count = 0;
	column_count = 0;
	line = get_next_line(fd);
	while(line)
	{
		ft_printf("\nline\n");
		column_count = validate_line(line);
		if (!dim.width)
			dim.width = column_count;
		if (column_count == -1)
		{
//			alloc fail in validate line
//			or illegal values
		}
		if (dim.width != column_count)
		{
//			wrong number of columns in a line
		}
		free(line);
		line = get_next_line(fd);
		line_count++;
	}
	dim.length = line_count;
	return (dim);
	
}
