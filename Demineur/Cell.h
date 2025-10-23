#pragma once

struct Cell
{
	bool bomb;
	bool reveal;
	bool flag;
	int nearbyBomb;

	int row;
	int col;

	char notReavealed = '#';
	char bombChar = '*';
	char flagChar = 'F';
};
Cell* CreateCellsArray(int size);
void InitVecteur(Cell* vecteur, int row, int col);