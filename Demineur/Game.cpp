#pragma once

#include<iostream>
#include"Game.h"
#include"Basic.h"

void PrintColNum(Cell* cells, Grid* grid)
{
	std::cout << "    ";
	for (int i = 0; i < grid[0].row; i++)
	{
		if (i < 10 && i > -10)
		{
			std::cout << " " << i << "  ";
		}
		else
		{
			std::cout << i << "  ";
		}
	}
}
void PrintLine(Cell* cells, Grid* grid)
{
	std::cout << std::endl << "   +";
	for (int j = 0; j < grid[0].col; j++)
	{
		std::cout << "---+";
	}
	std::cout << std::endl;
}
void PrintCell(Cell* cells, Grid* grid, int index)
{
	if (!cells[index].reveal)
		std::cout << " " << cells[index].notReavealed << " |";
	else
	{
		if (cells[index].bomb)
			std::cout << " " << cells[index].bombChar << " |";
		else if (cells[index].nearbyBomb == 0)
			std::cout << "   |";
		else if (cells[index].nearbyBomb > 0)
			std::cout << " " << cells[index].nearbyBomb << " |";
	}
}
void CheckEndRow(Cell* cells, Grid* grid, int index)
{
	if (cells[index].col == 0)	//verify if i'm in new row (col 0)
	{
		PrintLine(cells, grid);
		if (cells[index].row < 10)
		{
			std::cout << " " << cells[index].row << " |";
		}
		else
		{
			std::cout << cells[index].row << " |";
		}
	}
}
void Init(Cell* cells, Grid* grid)
{
	PrintColNum(cells, grid);
	for (int i = 0; i < grid->totalSize; i++)
	{
		CheckEndRow(cells, grid, i);
		PrintCell(cells, grid, i);
	}
	PrintLine(cells, grid);
}

int* getNearCase(Cell* demineur, int index, int gridSize, int* size)
{
	*size = 8;
	int* result = CreateIntArray(*size);
	int z = 0;
	for (int i = 0; i < gridSize; i++)			//regarde si i est une case au tour de l'index
		if (demineur[i].row == demineur[index].row - 1 || demineur[i].row == demineur[index].row || demineur[i].row == demineur[index].row + 1)
			if (demineur[i].col == demineur[index].col - 1 || demineur[i].col == demineur[index].col || demineur[i].col == demineur[index].col + 1)
				if (i != index && !demineur[i].reveal)		//si la case n'est pas l'index et n'est pas reveler
				{
					result[z] = i;
					z++;
				}
	*size = z;
	result = SmallerArray(result, *size);
	return result;
}
void PlantAllBombs(Cell* cells, int* plantBomb, int numOfBombs, int gridSize)
{
	for (int i = 0; i < numOfBombs; i++)		//make bool bomb true for list of bomb
	{
		cells[plantBomb[i]].bomb = true;
		int nearSize;
		int* nearCase = getNearCase(cells, plantBomb[i], gridSize, &nearSize);
		for (int j = 0; j < nearSize; j++)		//rajoute 1 aux case alentour dedans nearbyBomb
		{
			cells[nearCase[j]].nearbyBomb += 1;
		}
	}
}
void SearchPlant(int numOfBomb, int gridSize, int* bomb, int* dontPlantBomb, int dontplantSize)
{
	for (int i = 0; i < numOfBomb; i++)
	{
		int randomNum = rand() % (gridSize);
		for (int j = 0; j <= i; j++)
		{
			if (bomb[j] != randomNum)		//verifie si je n'ai pas déjà eu ce nombre
			{
				bool plant = true;
				for (int k = 0; k < dontplantSize; k++)		//verifie si le nombre n'est pas au tour de la premiere case choisit
				{
					if (randomNum == dontPlantBomb[k])
					{
						plant = false;
						break;
					}
				}
				if (plant)
				{
					bomb[i] = randomNum;
					break;
				}
				else
				{
					i--;
					break;
				}
			}
			else
			{
				i--;
				break;
			}
		}
	}
}
void PlantBombs(Cell* cells, int gridSize, int* dontPlantBomb, int dontplantSize)
{
	int numOfBomb = gridSize / 15;
	int* bomb = CreateIntArray(numOfBomb);
	SearchPlant(numOfBomb, gridSize, bomb, dontPlantBomb, dontplantSize);

	PlantAllBombs(cells, bomb, numOfBomb, gridSize);
	free(bomb);
	bomb = nullptr;
}

void SupprInArray(int** array, int* size, int indexToRemove)
{
	*size -= 1;
	int* newArray = CreateIntArray(*size);
	bool z = false;
	for (int i = 0; i < indexToRemove; i++)
	{
		newArray[i] = (*array)[i];
	}

	for (int i = indexToRemove; i < *size; i++)
	{
		newArray[i] = (*array)[i + 1];
	}

	free(*array);
	*array = newArray;
}

void ClearVision(Cell* demineur, int index, Grid* difficulty)
{
	int tmpSize = 1;
	int* tmp = CreateIntArray(tmpSize);
	tmp[0] = index;
	for (int i = 0; i < tmpSize; i++)			//rendre visible les cases :
	{
		demineur[tmp[i]].reveal = true;			//rendre visible la case choisit
		if (demineur[tmp[i]].nearbyBomb == 0)	//regarde si la case choisie n'a pas de bombes au tour
		{
			int nearbySize;
			int* nearby = getNearCase(demineur, tmp[i], difficulty[0].totalSize, &nearbySize);	//récupère les cases au tour
			SupprInArray(&tmp, &tmpSize, i);				//supprime la case verifier de la list
			i--;
			for (int j = 0; j < nearbySize; j++)			//faire le tour des case autour
			{
				demineur[nearby[j]].reveal = true;
				if (demineur[nearby[j]].nearbyBomb != 0)
				{
					SupprInArray(&nearby, &nearbySize, j);
					j--;
				}
			}
			MergeIndexArray(&tmp, nearby, &tmpSize, nearbySize);
		}
	}
	free(tmp);
	tmp = nullptr;
}