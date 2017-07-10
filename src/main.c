#include <stdlib.h>
#include <stdio.h>
#include <soduku.h>

#include <sys/resource.h>

CELL grid[WIDTH * HEIGHT];
CORD segments[9];

int main(int argc, char *argv[])
{
	const rlim_t k_stack_size = 64L * 1024L * 1024L * 300L;
	struct rlimit rl;
	int result;

	result = getrlimit(RLIMIT_STACK, &rl);
	if (result == 0)
	{
		if (rl.rlim_cur < k_stack_size)
		{
			rl.rlim_cur = k_stack_size;
			result = setrlimit(RLIMIT_STACK, &rl);
			if (result != 0)
			{
				fprintf(stderr, "setrlimit returned result = %d\n", result);
			}
		}
	}

	init_grid(argv[1]);
	char y, x;
	for (y = 0; y < HEIGHT; y++)
	{
		for (x = 0; x < WIDTH; x++)
		{
			if (grid[y * WIDTH + x].value == 0)
				goto exit;
		}
	}
exit:
	solve(x,y);
	print_grid();

	return 0;
}
