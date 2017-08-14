#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <fstream>
#include <vector>
#include <string.h>
#include <string>
#include <fcntl.h>
#include <algorithm>
#include <sstream>
#include "nodeStruct.h"
#include "nearestNeighbor.h"

void printResultSet(int resultSet[], int n)
{
	std::cout << "Result Set: " << std::endl;
	for (int x = 0; x < n; x++)
	{
		std::cout << "City " << x << ": " << resultSet[x] << std::endl;
	}
}

void writeResults(int resultSet[], int n, int total, std::string file)
{
	int x, y;

	FILE* myfile;
	myfile = fopen(file.c_str(), "w");

	fprintf(myfile, "%d\n", total);

	for (x = 0; x < n; x++)
	{
		fprintf(myfile, "%d\n", resultSet[x]);
	}

	fclose(myfile);
}

int computeDistance(struct Node x, struct Node y)
{
	return round(sqrt( (pow((x.x-y.x), 2)) + (pow((x.y-y.y), 2)) ));
}

void createDistanceMatrix(std::vector<struct Node> &x, int** matrix)
{
	for (int y = 0; y < x.size(); y++)
	{
		for (int z = 0; z < x.size(); z++)
		{
			matrix[y][z] = computeDistance(x[y], x[z]);
		}
	}
}

void copyArray(int a[], int b[], int n)
{
	for (int x = 0; x < n; x++)
	{
		b[x] = a[x];
	}
}

void printArray(int a[], int n)
{
	for (int x = 0; x < n; x++)
	{
		std::cout << a[x] << std::endl;
	}
}

void zeroArray(int a[], int n)
{
	for (int x = 0; x < n; x++)
	{
		a[x] = 0;
	}
}

int main(int argc, char* argv[])
{
	/********************************************/
	/*				Get filename				*/
	/********************************************/
	std::string filename;
	std::string outfilename;
	std::string ext = ".tour";
	if (argc < 2) //this section handles the case where the user didn't enter any arguments
	{
		std::cout << "Please enter a filename to read from:" << std::endl;
		std::getline(std::cin, filename);
		outfilename.append(filename);
		outfilename.append(ext);
	}
	else if (argc == 2) //this section handles the case where the user enters a filename argument
	{
		filename = argv[1];
		outfilename.append(filename);
		outfilename.append(ext);
	}
	else 
	{
		printf("Invalid arguments. Proper syntax is 'program filename'\n");
		return 0;
	}

	/********************************************/
	/*	  Read file into a vector of structs	*/
	/********************************************/
	std::vector<struct Node> input;
	FILE* file;
	char buffer[100];
	int temp, i = 0;
	char* line;
	size_t len = 0;
	ssize_t read;
	int x;

	file = fopen(filename.c_str(), "r");

	while ((read = getline(&line, &len, file)) != -1)
	{
		Node z = {0};
		int lineItr = 1;
		std::istringstream iss(line);

		while (iss >> x)
		{
			if (lineItr == 1) //first number on the line is the id
			{
				z.id = x;
			}
			else if (lineItr == 2) //second number on the line is the x coord
			{
				z.x = x;
			}
			else //else this is the y coord
			{
				z.y = x;
			}

			lineItr++;
		}

		input.push_back(z); //push the new node onto the vetor
		i++;
		line = NULL;
		//token = NULL;
		len = 0;
	}
	fclose(file);

	/********************************************/
	/*	 	    Create distance matrix			*/
	/********************************************/

	/***** Declare a 2D array to hold distances ******/
	int** matrix;
	matrix = new int *[input.size()];
	for (int p = 0; p < input.size(); p++)
	{
		matrix[p] = new int[input.size()];
	}

	createDistanceMatrix(input, matrix); //create the distance matrix	

	/********************************************/
	/*	 	    Call algorithm on vector 		*/
	/********************************************/
	int* resultCities = new int[input.size()];
	int* finalCities = new int[input.size()];
	int total = 0;
	int finalTotal = 9999999;

	for (int m = 0; m < input.size(); m++)
	{
		//call the algorithm
		tspNN(input, input.size(), resultCities, &total, matrix);

		if (total < finalTotal)
		{
			finalTotal = total;
			//copy result array to final array
			copyArray(resultCities, finalCities, input.size());
		}
		//swap out the starting element by moving it to the back
		std::rotate(input.begin(), input.begin() + 1, input.end()); //move the first element to the end
		zeroArray(resultCities, input.size());
	}

	writeResults(finalCities, input.size(), finalTotal, outfilename);

	return 0;
}
