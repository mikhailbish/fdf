/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutuzov <mbutuzov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 20:05:20 by mbutuzov          #+#    #+#             */
/*   Updated: 2024/08/20 21:25:57 by mbutuzov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void init_stacks(t_env *en, int argc)
{
	en->stacks[0] = init_stack(argc);
	if (en->stacks->length == -1)
	{
		(en->stacks + 1)->length = -1;
		return ;
	}
	en->stacks[1] = init_stack(argc);
	if (en->stacks->length == -1)
	{
		free(en->stacks[0].content);
		return ;
	}
}

t_env ft_parse_input(int argc, char **argv)
{
	char	**args;
	t_env	en;

	if (argc == 2)
	{
		args = ft_split(argv[1], ' ');
		if (!args)
		{
			en.stacks[1].length = -1;
			return (en);
		}
		init_stacks(&en, count_split(args));
		if (en.stacks[1].length == -1)
			return (en);
		fill_stack(en.stacks, args, count_split(args));
		free_split(args);
		return (en);
	}
	init_stacks(&en, --argc);
	if (en.stacks[1].length == -1)
		return (en);
	args = ++argv;
	fill_stack(en.stacks, args, argc);
	return (en); 
}
