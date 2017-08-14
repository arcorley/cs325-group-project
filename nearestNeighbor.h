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

void tspNN(std::vector<struct Node> &a, int n, int resultSet[], int *total);

static bool compare( const struct Node &i, const struct Node &j);

void printNodes(std::vector<struct Node> &a);
