#pragma once
#include"Game.h"
#include"Basic.h"
#include <iostream>

void InitGrid(Grid* result, int row, int col)
{
	result->row = row;
	result->col = col;
	result->totalSize = row * col;
}

void ShowDifficultyChoice()
{
	Print("Difficulty :");
	Print("1 . Easy 9 x 9");
	Print("2 . Easy 16 x 16");
	Print("3 . Easy 16 x 32");
	Print("4 . Personnal");
}
void Easy(Grid* result)
{
	InitGrid(result, 9, 9);
}
void Medium(Grid* result)
{
	InitGrid(result, 16, 16);
}
void Hard(Grid* result)
{
	InitGrid(result, 16, 32);
}
void Personnal(Grid* result)
{
	int row = AskInt("Number of row ?");
	int col = AskInt("Number of col ?");
	InitGrid(result, row, col);
}

Grid DefineGrid()
{
	Grid result;
	int input;
	do
	{
		ShowDifficultyChoice();
		input = AskInt("Choice :");
		switch (input)
		{
		case 1:
			Easy(&result);
			Print("You choose the EASY difficulty");
			return result;
		case 2:
			Medium(&result);
			Print("You choose the MEDIUM difficulty");
			return result;
		case 3:
			Hard(&result);
			Print("You choose the HARD difficulty");
			return result;
		case 4:
			Personnal(&result);
			return result;
		default:
			Print("Please, choose a difficulty.");
			break;
		}
	} while (true);
}