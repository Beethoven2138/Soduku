#include <soduku.h>

CELL grid[WIDTH * HEIGHT];
CORD segments[9];

void init_grid(char *file_name)
{
	FILE *fp = fopen(file_name, "r");
	int c;
	char y = 0;
	char x = 0;
	while (1)
	{
		c = fgetc(fp);
		if (c == EOF)
			break;
		if ((c >= 48 && c <= 57) || c == 95)
		{
			if (c != 95 && c != 48)
				grid[y * WIDTH + x].value = c - 48;
			grid[y * WIDTH + x].segment = find_segment(x, y);
			if (++x >= WIDTH)
			{
				y++;
				x = 0;
			}
		}
	}
	segments[0].x = 1;
	segments[0].y = 1;
	segments[1].x = 4;
	segments[1].y = 1;
	segments[2].x = 7;
	segments[2].y = 1;
	segments[3].x = 1;
	segments[3].y = 4;
	segments[4].x = 4;
	segments[4].y = 4;
	segments[5].x = 7;
	segments[5].y = 4;
	segments[6].x = 1;
	segments[6].y = 7;
	segments[7].x = 4;
	segments[7].y = 7;
	segments[8].x = 7;
	segments[8].y = 7;
}

static char find_segment(char xPos, char yPos)
{
	if (yPos >= 0 && yPos <= 2)
	{
		if (xPos >= 0 && xPos <= 2)
			return 0;
		if (xPos >= 3 && xPos <= 5)
			return 1;
		return 2;
	}
	else if (yPos >= 3 && yPos <= 5)
	{
		if (xPos >= 0 && xPos <= 2)
			return 3;
		if (xPos >= 3 && xPos <= 5)
			return 4;
		return 5;
	}
	if (xPos >= 0 && xPos <= 2)
		return 6;
	if (xPos >= 3 && xPos <= 5)
		return 7;
	return 8;
}

static bool is_full(void)
{
	for (int i = 0; i < WIDTH * HEIGHT; i++)
	{
		if (grid[i].value == 0)
			return false;
	}
	return true;
}

bool valid_value(char x, char y)
{
	CORD segment = segments[grid[y * WIDTH + x].segment];
	char value = grid[y * WIDTH + x].value;
	//First check if there are other cells in the same segment with the same value
	for (char yPos = segment.y-1; yPos <= segment.y+1; yPos++)
	{
		for (char xPos = segment.x-1; xPos <= segment.x+1; xPos++)
		{
			if ((yPos != y || xPos != x) && grid[yPos * WIDTH + xPos].value == value)
				return false;
		}
	}
	for (char yPos = 0; yPos < HEIGHT; yPos++)
	{
		if (yPos != y && grid[yPos * WIDTH + x].value == value)
			return false;
	}
	for (char xPos = 0; xPos < WIDTH; xPos++)
	{
		if (xPos != x && grid[y * WIDTH + xPos].value == value)
			return false;
	}
	return true;
}

bool solve(char x, char y)
{
	print_grid();
	printf("\n\n\n");
	for (int i = 1; i <= 9; i++)
	{
		grid[y * WIDTH + x].value = i;
		if (valid_value(x, y))
		{
			if (is_full())
				return true;
			CORD next = next_free_cell(x, y);
			if (solve(next.x, next.y))
				return true;
		}
	}
	grid[y * WIDTH + x].value = 0;
	return false;
}

CORD next_free_cell(char x, char y)
{
	char next_x, next_y;

	/*CORD segment = segments[grid[y * WIDTH + x].segment];
	for (char yPos = segment.y-1; y <= segment.y+1; y++)
	{
		for (char xPos = segment.x-1; x <= segment.x+1; x++)
		{
			if ((yPos != y || xPos != x) && grid[yPos * WIDTH + xPos].value == 0)
			{
				CORD ret;
				ret.x = x;
				ret.y = y;
				return ret;
			}
		}
	}*/

	next_x = x + 1;
	next_y = y;

	if (next_x >= WIDTH)
	{
		next_x = 0;
		next_y++;
	}

	for (next_y; next_y < HEIGHT; next_y++)
	{
		for (next_x; next_x < WIDTH; next_x++)
		{
			if (grid[next_y * WIDTH + next_x].value == 0)
			{
				CORD ret;
				ret.x = next_x;
				ret.y = next_y;
				return ret;
			}
		}
	}
}

void print_grid(void)
{
	for (int y = 0; y < HEIGHT; y++)
	{
		for (int x = 0; x < WIDTH; x++)
		{
			printf("%d", grid[y * WIDTH + x].value);
			if (x == 2 || x == 5)
				printf(" ");
		}
		printf("\n");
		if (y == 2 || y == 5)
			printf("\n");
	}
}
