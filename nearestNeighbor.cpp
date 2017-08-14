#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <fstream>
#include <vector>
#include <string.h>
#include <fcntl.h>
#include <algorithm>
#include "nodeStruct.h"
#include "nearestNeighbor.h"

static bool compare( const struct Node &i, const struct Node &j)
{
	return i.x < j.x;
}

void printMatrix(int** matrix, int n)
{
	int x, y;

	FILE* myfile;
	myfile = fopen("distance_matrix.csv", "w");

	for(x = 0; x < n; x++)
	{
		for(y = 0; y < n; y++)
		{
			fprintf(myfile, "%d,", matrix[x][y]);
		}

		fprintf(myfile, "\n");
	}
	fclose(myfile);
}

int getVectorIndex(std::vector<struct Node> &x, int z)
{
	for (int i = 0; i < x.size(); i++)
	{
		if (x[i].id == z)
		{
			return i;
		}
	}
}

void getElementById(std::vector<struct Node> &x, int y, struct Node **z)
{
	for (int i = 0; i < x.size(); i++)
	{
		if (x[i].id == y)
		{
			*z = &x[i];
		}
	}
}

void printNodes(std::vector<struct Node> &a)
{
	for (int x = 0; x < a.size(); x++)
	{
		std::cout << "ID: " << a[x].id << " x: " << a[x].x << " y: " << a[x].y << std::endl;
	}
}

void tspNN(std::vector<struct Node> &a, int n, int resultSet[], int* total, int** matrix)
{
	std::vector<struct Node> g;

	for (int x = 0; x < n; x++) //copy contents of a over to g
	{
		g.push_back(a[x]);
	}

	std::sort(g.begin(), g.end(), compare); //sort g in ascending order of x


	resultSet[0] = g[0].id; //set the starting city to the city with the smallest x and y

	//set up variables for loop
	Node *currentCity = &g[0]; //pointer to the current city
	int cityNumber = 0, totalDistance = 0;
	Node *nextCity = NULL;
	int nextCityId, index = 0;

	while (g.size() > 0)
	{
		int distance = 99999999;
		int tempDistance = 0;
		cityNumber++;

		if (g.size() == 1) //if there's only 1 element left, just take its distance
		{
			distance = matrix[currentCity->id][g[0].id] + matrix[g[0].id][resultSet[0]]; //if this is the last node, add the distance of the final node, then the distance back to starting point
			nextCityId = g[0].id;
			nextCity = &g[0];
		}
		else //if there's more than 1 element left, do the for loop
		{
			for (int i = 0; i < g.size(); i++)
			{
				if (g[i].id != currentCity->id) //if i is equal to current city id, distance will be 0, so skip that case
				{
					tempDistance = matrix[currentCity->id][g[i].id]; //look up value of distance in matrix

					if (tempDistance < distance) //if we have a new min, assign it
					{
						distance = tempDistance;
						nextCityId = g[i].id;
						nextCity = &g[i];
					}
				}
			}
		}

			resultSet[cityNumber] = nextCityId; //add the city that was found to the result set
			totalDistance += distance; //add the distance found to the total distance
			index = getVectorIndex(g, currentCity->id); //get the index of the element to delete
			g.erase(g.begin() + index); //delete the element
			getElementById(g, nextCityId, &currentCity); //change current city to be the next city
	}

	*total = totalDistance; //write the total distance
}
