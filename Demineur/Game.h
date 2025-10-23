#pragma once

#include"Grid.h"

void Init(Cell* demineur, Grid* difficulty);

int* getNearCase(Cell* demineur, int index, int sizeDemineur, int* size);
void PlantBombs(Cell* demineur, int size, int* dontPlantBomb, int dontplantSize);
void ClearVision(Cell* demineur, int index, Grid* difficulty);