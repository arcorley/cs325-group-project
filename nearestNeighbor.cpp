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

void removeNode(std::vector<struct Node> &x, int id)
{
	x.erase(
		std::remove_if(x.begin(), x.end(), [&](Node const & z)
		{
			return z.id == id;
		}),
		x.end());
}

void printResultSet(int resultSet[], int n)
{
	std::cout << "Current Result Set: " << std::endl;
	for (int x = 0; x < n; x++)
	{
		std::cout << resultSet[x] << std::endl;
	}
}

void printNodes(std::vector<struct Node> &a)
{
	for (int x = 0; x < a.size(); x++)
	{
		std::cout << "ID: " << a[x].id << " x: " << a[x].x << " y: " << a[x].y << std::endl;
	}
}

void tspNN(std::vector<struct Node> &a, int n, int resultSet[], int total)
{
	std::vector<struct Node> g;

	for (int x = 0; x < n; x++) //copy contents of a over to g
	{
		g.push_back(a[x]);
	}

	std::sort(g.begin(), g.end(), compare); //sort g in ascending order of x

	resultSet[0] = g[0].id; //set the starting city to the city with the smallest x and y
	removeNode(g, 0);

	//set up variables for loop
	Node *currentCity = &g[0]; //pointer to the current city
	int cityNumber = 0, totalDistance = 0;
	Node *nextCity = NULL;

	//int distance = 99999999;
	//int tempDistance = 0;
	//cityNumber++;

	while (g.size() > 0)
	{
		int distance = 99999999;
		int tempDistance = 0;
		cityNumber++;

		for (int i = 0; i < n; i++)
		{
			tempDistance = sqrt( (pow((currentCity->x - g[i].x), 2)) + (pow((currentCity->y - g[i].y), 2)) );

			/*std::cout << "Current city x: " << currentCity->x << std::endl;
			std::cout << "Iteration x: " << g[i].x << std::endl;
			std::cout << "Power: " << (pow((currentCity->x - g[i].x), 2)) << std::endl;;
			std::cout << "Current city y: " << currentCity->y << std::endl;
			std::cout << "Iteration y: " << g[i].y << std::endl;
			std::cout << "Power: " << (pow((currentCity->y - g[i].y), 2)) << std::endl;
			std::cout << "Sqrt: " << sqrt( (pow((currentCity->x - g[i].x), 2)) + (pow((currentCity->y - g[i].y), 2)) ) << std::endl;
			std::cout << "tempDistance: " << tempDistance << std::endl << std::endl; */

			if (tempDistance < distance)
			{
				distance = tempDistance;
				nextCity = &g[i];
			}
		}

			std::cout << "Current G Size: " << g.size() << std::endl;
			std::cout << "Calculated Lowest Distance: " << distance << std::endl;
			std::cout << "City to add to result set: " << nextCity->id << std::endl;
			resultSet[cityNumber] = nextCity->id;
			std::cout << "Current total distance computed: " << totalDistance << std::endl;
			totalDistance += distance;
			std::cout << "New total distance: " << totalDistance << std::endl;
			//std::cout << "Id to erase: " << currentCity->id << std::endl;
			std::cout << "Current City: " << currentCity->id << std::endl;
			removeNode(g, currentCity->id);
			currentCity = nextCity;
			std::cout << "New City: " << currentCity->id << std::endl << std::endl;
			//std::cout << "Next city to process: " << currentCity->id << std::endl;
	}

	total = totalDistance;
}