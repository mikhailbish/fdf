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

#include <stdio.h>
#include <sys/time.h>
float timedifference_msec(struct timeval t0, struct timeval t1)
{
    return (t1.tv_sec - t0.tv_sec) * 1000.0f + (t1.tv_usec - t0.tv_usec) / 1000.0f;
}

void print_time_passed(void func(void *), void *param)
{
	struct timeval t0;
	struct timeval t1;
	float elapsed;
	gettimeofday(&t0, 0);
	func(param);
	gettimeofday(&t1, 0);
	elapsed = timedifference_msec(t0,t1);
	printf("p d seconds %f\n", elapsed);
}
/*
	TODO: test
		print_time_passed(process_data, &dim)
	
	process_data(&dim);

*/


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
