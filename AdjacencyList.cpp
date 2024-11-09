#include <iostream>
#include <algorithm>
#include <string>
#include <sstream>
#include <iomanip>
#include "AdjacencyList.h"
using namespace std;

// Inserts edges into adjacency list connecting corresponsding "from" and "to" webpages (also calculates in/out degrees)
void AdjacencyList::insertEdge(string from, string to)
{
    // Create "from" to "to" and "to" to "from" maps

    // If we haven't seen "to" before, push it into adjList (essentially also tracks out degrees)
    adjList[from].push_back(to);

    // If we haven't seen "from" before, push it into inDegree (keeps track of in degrees)
    inDegree[to].push_back(from);
}

// References:
// Office Hours (Amay)
// Programming Quiz from this week

// Prints the PageRank of all pages after p powerIterations in ascending alphabetical order of webpages and rounding rank to two decimal places
string AdjacencyList::PageRank(int p)
{
    // Store output in a string/stringstream and then return it from this function after printing so that it is easier to test with Catch
    stringstream result;

    // Initialize unique websites set to use in calculations
    set<string> uniqueWebsites = getUniqueWebsites();

    // Preform initial rank calculation regardless of p (if p>1 calculate more, if not this will be final rank)
    if (p == 1)
    {
        // Get size of adjList to use in calculations
        double rank = 1.0 / uniqueWebsites.size();

        // Loop through URLs in adjList
        for (const auto& url : uniqueWebsites)
        {
            // Place calculated rank into rank map for each URL
            Rank[url] = rank;
        }
    }

    // If power iteration > 1, preform prev p / outDegree of "to"
    if (p > 1)
    {
        // REPEAT AS WE NEED THE INITIAL CALCULATION FOR P > 1
        // Get size of adjList to use in calculations
        double rank = 1.0 / uniqueWebsites.size();

        // Loop through URLs in uniqueWebsites
        for (const auto& url : uniqueWebsites)
        {
            // Place calculated rank into rank map for each URL
            Rank[url] = rank;
        }

        // Loop through remaining power iterations excluding p1 which we already calculated
        for (int p_iteration = 0; p_iteration < p - 1; p_iteration++)
        {
            // Use temporary map to store newRanks while we are still using ranks from the previous iteration
            map<string, double> tempMap;

            // Loop through URLs in uniqueWebsites to update ranks
            for (const auto& url : uniqueWebsites)
            {
                // Set current URL to use when calculating ranks
                string current = url;
                double newRank = 0.0;

                // Set rank to zero if the current URL of adjList has no in degrees
                if (inDegree[current].empty())
                {
                    newRank = 0.0;
                }

                // If not, continue to calculate rank as intended
                else
                {
                    // Loop through in degrees to calculate rank and add together if there are multiple
                    for (const string& inDegreeURL : inDegree[current])
                    {
                        // To calculate rank:
                        // Numerator: take most recently calculated rank value
                        double prevRank = Rank[inDegreeURL];

                        // Denominator: take the out degree of the current in degree
                        int outDegree = adjList[inDegreeURL].size();

                        double calculatedRank = prevRank / outDegree;

                        newRank += calculatedRank;
                    }
                }

                // Add calculated rank to temp map
                tempMap[current] = newRank;
            }

            // Overwrite in Rank now that we are finished using previous rank values
            Rank = tempMap;
        }
    }

    // Basically print out contents of Rank as that is the expected output (set double two decimal places)
    for (const auto& doubleTostring : Rank)
    {
        result << doubleTostring.first << " " << fixed << setprecision(2) << doubleTostring.second << endl;
    }

    return result.str();
}

// References:
// https://stackoverflow.com/questions/15927033/what-is-the-correct-way-of-using-c11s-range-based-for
//https://stackoverflow.com/questions/4826404/getting-first-value-from-map-in-c
//https://stackoverflow.com/questions/22515592/how-to-use-setprecision-in-c