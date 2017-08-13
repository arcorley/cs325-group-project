#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <fstream>
#include <vector>
#include <string.h>
#include <fcntl.h>

//declaration of node struct. used to hold the contents of each line in the input file
struct Node{
	int id, x, y;
};


//this function prints out the contents of a vector. use to test that file was read in correctly
void printNodes(std::vector<struct Node> &a)
{
	for (int x = 0; x < a.size(); x++)
	{
		std::cout << "ID: " << a[x].id << " x: " << a[x].x << " y: " << a[x].y << std::endl;
	}
}

int main(int argc, char* argv[])
{
	/********************************************/
	/*				Get filename				*/
	/********************************************/
	std::string filename;
	if (argc < 2) //this section handles the case where the user didn't enter any arguments
	{
		std::cout << "Please enter a filename to read from:" << std::endl;
		std::getline(std::cin, filename);
	}
	else if (argc == 2) //this section handles the case where the user enters a filename argument
	{
		filename = argv[1];
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

	return 0;
}