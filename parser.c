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

t_dimensions get_map_dimensions()
{

}


int main(int argc, char **argv)
{
	char *line;
	char **line_split;
	char **tmp_line_split;
	if (argc != 2)
		return (1);
	++argv;
	if (check_name(*argv))
		ft_printf("good name");
	else
		return (1);
	int fd = open(*argv, O_RDONLY);
	if (!(fd > 0))
	{
		perror("Cannot find file");
		return (1);
	}
	line = get_next_line(fd);
	ft_printf("line: %s \nafter gnl", line);
	//include smth for errno and check it after each use of gnl?
	int line_count = 0;
	int column_count = 0;
	int prev_count = -1;

//	t_ft_point *matrix_line = ft_calloc(sizeof(t_ft_point) * (columns + 1));
//	t_ft_point **coordinate_matrix = ft_calloc(sizeof(t_ft_point *) * (rows + 1))
	while(line)
	{
		line_split = ft_split(line, ' ');
		tmp_line_split = line_split;
		if (!line_split)
		{
			//some error handling
		}
		while (*tmp_line_split)
		{
			ft_printf("going through line split: %s\n", *tmp_line_split);
			// add to coordinate matrix
			char *tmp_ptr;
			int num;
			num = (int)ft_strtol(*tmp_line_split, &tmp_ptr, 10);
			if (*tmp_ptr != 0)
			{
				// handle error
				return (1);
			}
			coordinate_matrix[column_count][line_count]= num
			column_count++;
			tmp_line_split++;
		}
		if (prev_count == -1)
			prev_count = column_count;
		if (column_count != prev_count)
		{
			// handle
			return (1);
		}
		column_count = 0;
		line = get_next_line(fd);
		line_count++;
	}
	free(line);

	return (0);
}
