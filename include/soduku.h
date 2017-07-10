#ifndef SODUKU_H
#define SODUKU_H

#define WIDTH 9
#define HEIGHT 9

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct CELL 
{
	char value;
	char segment;
} CELL;

typedef struct CORD
{
	char x;
	char y;
} CORD;

extern CELL grid[WIDTH * HEIGHT];
extern CORD segments[9];

void init_grid(char *file_name);

static bool is_full(void);

static char find_segment(char xPos, char yPos);

bool solve(char x, char y);

void print_grid(void);

static CORD next_free_cell(char x, char y);

#endif
