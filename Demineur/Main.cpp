#pragma once
#include"Game.h"
#include"Basic.h"
#include"PlayerInteraction.h"
#include<iostream>
#include<time.h>

void PrintMoveAvailable()
{
	Print("1 . Clear a case.");
	Print("2 . Plant or Remove a Flag.");
}
int ChooseMove()
{
	bool a;
	do
	{
		PrintMoveAvailable();
		int input = AskInt("Choice :");
		switch (input)
		{
		case 1:
			a = false;
			Print("You choose to CLEAR a case");
			return input;
		case 2:
			a = false;
			Print("You choose to PLANT or REMOVE a Flag");
			return input;
		default:
			a = true;
			Print("Please, choose a move.");
			break;
		}
	} while (a);

}
int GetIndex(int maxCol, int row, int col)
{
	int index = row * maxCol + col;
	return index;
}
void ChooseCase(int* index, Grid* grid)
{
	bool a = true;
	int row;
	int col;
	do
	{
		row = AskInt("Row num ?");
		if (row <= grid[0].row && row >= 0)
		{
			col = AskInt("Col num ?");
			if (col <= grid[0].col && col >= 0)
			{
				a = false;
			}
		}
	} while (a);
	*index = GetIndex(grid[0].col, row, col);
}

void FlagManageur(Cell* demineur, int index, Grid* grid)
{
	demineur[index].flag = !demineur[index].flag;
}
void Update(Cell* demineur, Grid* grid, int moveChoosen, int index)
{
	if (moveChoosen == 1)
		ClearVision(demineur, index, grid);
	else if (moveChoosen == 2)
		FlagManageur(demineur, index, grid);
	else
		Print("Error Fonction Update.");

}
void PlayerMove(Cell* demineur, Grid* grid, int* moveChoosen, int* index)
{
	*moveChoosen = ChooseMove();
	ChooseCase(index, grid);
}

void GameManager()
{
	Grid grid = DefineGrid();
	Cell* cells = CreateCellsArray(grid.totalSize);
	{
		int index = 0;
		for (int i = 0; i < grid.row; i++)
			for (int j = 0; j < grid.col; j++)
			{
				InitVecteur(&cells[index], i, j);
				index++;
			}
	}
	Init(cells, &grid);
	//player move
	int moveChoosen;
	int index;
	ChooseCase(&index, &grid);
	int nobombSize;
	int* nobomb = getNearCase(cells, index, grid.totalSize, &nobombSize);
	PlantBombs(cells, grid.totalSize, nobomb, nobombSize);
	ClearVision(cells, index, &grid);

	bool gameOver = false;
	bool win = false;
	bool lose = false;
	do
	{
		Init(cells, &grid);
		PlayerMove(cells, &grid, &moveChoosen, &index);
		ClearVision(cells, index, &grid);
		if (cells[index].bomb)
		{
			Print("You lose !");
			gameOver = true;
			lose = true;
		}
		for (int i = 0; i < grid.totalSize; i++)
		{
			if (!cells[i].bomb && !cells[i].reveal)
			{
				gameOver = false;
				win = false;
				break;
			}
			else
			{
				gameOver = true;
				win = true;
			}
		}
	} while (!gameOver);
	if (win)
		Print("You win !");
	else if (lose)
		Print("You lose !");
	else
		Print("Error gameOver");
}
bool PlayAgain()
{
	Print("Do you want to play again ? (y/n)");
	char input;
	do
	{
		std::cin >> input;

		if (input == 'y' || input == 'Y')
			return true;
		else if (input == 'n' || input == 'N')
			return false;
		else
			Print("Please enter y or n.");
	} while (true);
}
int main()
{
	srand(time(NULL));
	bool play;
	do
	{
		GameManager();
		play = PlayAgain();
	} while (play);
}