#include"Cell.h"
#include"Basic.h"
#include<iostream>

Cell* CreateCellsArray(int size)
{
	Cell* p = (Cell*)malloc(sizeof(Cell) * size);
	if (p == nullptr)
	{
		Print("ERROR NO SPACE FOR CELLS ARRAY");
		exit(1);
	}
	return p;
}
void InitVecteur(Cell* vecteur, int row, int col)
{
	vecteur->col = col;
	vecteur->row = row;

	vecteur->bomb = false;
	vecteur->flag = false;
	vecteur->reveal = false;
	vecteur->nearbyBomb = 0;
}