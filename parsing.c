#include "fdf.h"

int check_name(char *name)
{
	size_t	length;
	int	cmp_res;

	cmp_res = 0;
	length = ft_strlen(name);
	if (length < 4)
		return (0);
	cmp_res = ft_strncmp(name + length - 4, ".fdf", 4);
	if (cmp_res == 0)
		return (1);
	return (0);
}

void	delete_content(void *content)
{
	free((char *)content);	
}

t_list	*get_file_lines(int fd)
{
	char	*line;
	t_list	*head;
	t_list	*tmp;
	
	line = get_next_line(fd);
	if (!line)
	{
		//error in gnl
		return(0);	
	}
	head = ft_lstnew((void *)line);
	if (!head)
	{
		// error in lst new
		return(0);	
	}
	while (line)
	{
		line = get_next_line(fd);
		if (!line && errno == ENOMEM)
		{
			//error in gnl
			return(0);	
		} else if (!line)
			break ;
		tmp = ft_lstnew(line);
		if (!tmp)
		{
			// error in lst new
			return(0);	
		}
		ft_lstadd_back(&head, tmp);
	}
	return (head);
}
	
/*
	char	*line;
	t_list	*head;
	t_list	*tmp;

	line = (char *)-1;

	while (line)
	{
		line = get_next_line(fd);
		if (!line)
			break;
		tmp = ft_lstnew((void *)line);
		if (!tmp)
			break;
			//malloc list error
			//free list?
			//break??
			//no errno check
			// adjust errno?
		ft_lstadd_back(&head, tmp);
	}
	// gnl till the end
	if (!tmp)
		while(line)
		{
			free(line);
			line = get_next_line(fd)
		}
	if (errno == ENOMEM)
	{
		//error in gnl
	}
*/
/*
	line = get_next_line(fd);
	if (line)
		head->content = (void *)line;
	tmp = head;
	while(line)
	{
		tmp->next = *ft_lstnew(line);
		if (!tmp->next)
			ft_lstclear(head, delete_content);
		tmp = tmp->next;
		line = get_next_line(fd);
	}
	if (errno == ENOMEM)
	{
		//error in gnl
	}
*/	

/*
t_dimensions get_map_dimensions()
{

}
*/

