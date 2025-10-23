#include<iostream>

#include "Basic.h"

void Print(const char* msg)
{
	std::cout << msg << std::endl;
}
int AskInt(const char* msg)
{
	Print(msg);
	int value;
	std::cin >> value;
	return value;
}
int GetIndex(int maxCol, int row, int col)
{
	int index = row * maxCol + col;
	return index;
}
int* CreateIntArray(int size)
{
	int* p = (int*)malloc(sizeof(int) * size);
	if (p == nullptr)
	{
		Print("ERROR NO SPACE FOR INT ARRAY");
		exit(1);
	}
	return p;
}
int* SmallerArray(int* array, int size)
{
	int* newArray = CreateIntArray(size);
	for (int i = 0; i < size; i++)
	{
		newArray[i] = array[i];
	}
	free(array);
	array = nullptr;
	return newArray;
}
void MergeIndexArray(int** array1, int* array2,int *size1,int size2)
{
	int size = *size1 + size2;
	int* newArray = CreateIntArray(size);
	for (int i = 0; i < *size1; i++)
	{
		newArray[i] = (*array1)[i];
	}
	bool copy = false;
	for (int i = 0; i < size2; i++)
	{
		for (int j = 0; j < *size1; j++)	//chercher si il y a déjà l'index
		{
			if (array2[i] == (*array1)[j])
			{
				copy = true;
				break;
			}
		}
		if(!copy)
			newArray[i + *size1] = array2[i];
		else
		{
			size2--;
			size--;
		}
		copy = false;
	}
	free(*array1);
	free(array2);
	*array1 = newArray;
	array2 = nullptr;
	*size1 = size;
}