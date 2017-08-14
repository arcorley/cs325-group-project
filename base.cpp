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

	file = fopen(filename.c_str(), "r");

	while ((read = getline(&line, &len, file)) != -1)
	{
		Node z = {0};
		int lineItr = 1;
		char* token = strtok(line, " "); //get the first number in the line

		while (token != NULL)
		{
			sscanf(token, "%d", &temp); //convert token to an int
			if (lineItr == 1) //first number on the line is the id
			{
				z.id = temp;
			}
			else if (lineItr == 2) //second number on the line is the x coord
			{
				z.x = temp;
			}
			else //else this is the y coord
			{
				z.y = temp;
			}

			token = strtok(NULL, " "); //get the next number in the string
			lineItr++;
		}

		input.push_back(z); //push the new node onto the vetor
		i++;
		line = NULL;
		token = NULL;
		len = 0;
	}

	/********************************************/
	/*	 	    Call algorithm on vector 		*/
	/********************************************/
	int* resultCities = new int[input.size()];
	int total = 0;

	tspNN(input, input.size(), resultCities, &total);

	writeResults(resultCities, input.size(), total, outfilename);

	//printResultSet(resultCities, input.size());

	//std::cout << std::endl << "Total Distance: " << total << std::endl;

	delete[] resultCities;

	return 0;
}
