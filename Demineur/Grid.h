#pragma once
#include"Cell.h"

struct Grid
{
	int row;
	int col;
	int totalSize;
};

void InitGrid(Grid*, int, int);
Grid DefineGrid();

