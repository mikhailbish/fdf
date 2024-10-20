#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct s_some
{
	void *ptr;
} t_some;


void print_strings(t_some holder)
{
	char **strs = (char **)holder.ptr;
	int i = 0;
	while (i < 5)
	{
		printf("%s\n", strs[i]);
		i++;
	}
}

int main()
{
	t_some strholder;

	char strs[5][10] = {
		"hello",
		"world",
		"some",
		"other",
		"bleh"
	};
	char **ptr = malloc(sizeof(char *) * 5);
	if (!ptr)
		return 1;
	char **tmp = ptr;
	int i = 0;
	while (i < 5)
	{
		tmp[i] = malloc(10 * sizeof(char));
		if (!tmp[i])
			return 1;
		strcpy(tmp[i], strs[i]);
		i++;
	}
	strholder.ptr = (void *)ptr;
	print_strings(strholder);
	return 0;
}
