#include <iostream>
#include <string>
#include <sstream>
#include "AdjacencyList.h"
using namespace std;

int main()
{
    // Declaring the number of lines, power iterations to be preformed
    int num_of_lines, power_iterations;
    string from, to;

    // Declare adjList object
    AdjacencyList adjList;

    // Reading the num of lines, power iterations
    cin >> num_of_lines;
    cin >> power_iterations;

    // For each of the next n lines, read in the vertices "from" and "to"
    for (int i = 0; i < num_of_lines; i++)
    {
        cin >> from;
        cin >> to;
        adjList.insertEdge(from, to);
    }

    string result = adjList.PageRank(power_iterations);
    cout << result;
    return 0;
}

// References:
// Project Breakdown Video
// https://cplusplus.com/reference/string/string/getline/
//https://cplusplus.com/reference/sstream/

