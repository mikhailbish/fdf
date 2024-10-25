/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutuzov <mbutuzov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 15:59:15 by mbutuzov          #+#    #+#             */
/*   Updated: 2024/10/25 19:08:56 by mbutuzov         ###   ########.fr       */
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
//	ft_printf("line: %s\n", line);
	line_split = ft_split(line, ' ');
	tmp_line_split = line_split;
	if (!line_split)
	{
		//some error handling
		ft_printf("problems in validate line split\n");
		return (-1);
	}
	while (*tmp_line_split)
	{
//		ft_printf("column\n");
		// add to coordinate matrix
		if (is_legal_number(*tmp_line_split))
			column_count++;
		else
		{
//			ft_printf("illegal num: %s\n", *tmp_line_split);
			ft_printf("illegal number\n");
			column_count = -1;
			break;
		}
		tmp_line_split++;
	}
	free_split(line_split);
	return (column_count);
}
/*
t_map validate_file(int fd)
{
	int 	column_count;
	int	line_count;
	char	*line;
	t_map dim;

	dim.length = 0;
	dim.width = 0;

	line_count = 0;
	column_count = 0;
	line = get_next_line(fd);
	while(line)
	{
		ft_printf("\nline from file: %s\n", line);
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
	
}*/
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
	ft_printf("line count: %d\n", line_count);
	while(lines)
	{
		column_count = validate_line((char *)lines->content);
		if (!dim.width)
			dim.width = column_count;
		if (column_count == -1)
		{
			perror("memory error at validation\n")
			return (dim);
		/*	
			ft_printf("alloc fail in validate line or illegal values\n");
			exit(1);*/
//			alloc fail in validate line
//			or illegal values
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
