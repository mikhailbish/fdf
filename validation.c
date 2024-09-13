/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutuzov <mbutuzov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 15:59:15 by mbutuzov          #+#    #+#             */
/*   Updated: 2024/09/13 19:11:02 by mbutuzov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

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
t_dimensions validate_file(int fd)
{
	int 	column_count;
	char	*line;
	char	**line_split;
	char	**tmp_line_split;
	t_dimensions dim;

	column_count = 0;
	line = get_next_line(fd);
	while(line)
	{
		column_count = validate_line(line);
		if (!dim.width)
			dim.width = column_count;
		if (column_count == -1)
		{
//			alloc fail in validate line
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

int	validate_line(char *line)
{
	char	**args;
	int		validation_result;

	if (argc == 1)
		return (-1);
	if (argc == 2)
	{
		if (argv[1][0] == 0)
			return (0);
		args = ft_split(argv[1], ' ');
		if (!args)
			return (0);
		if (argv[1][0] != 0 && *args == 0)
		{
			free(args);
			return (0);
		}
/*		if (*args == 0)
			return (-1);*/
		validation_result = validate_args(args, count_split(args));
		free_split(args);
		return (validation_result);
	}
	args = ++argv;
	return (validate_args(args, --argc));
}
