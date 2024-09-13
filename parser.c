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
/*
t_dimensions get_map_dimensions()
{

}
*/

