#pragma once
#include<iostream>
#include <string>
#include <set>
#include<unordered_map>
#include <map>
#include<vector>
using namespace std;

class AdjacencyList
{
    private:
        // Creates adjacency list that maps unique IDS associated with URLs to their corresponding webpages
        // Key: from, Value: to
        map<string, vector<string>> adjList;

        // Indegree storage for each node ("to" to "from" map)
        // Key: to, Value: from
        map<string, vector<string>> inDegree;

        // Map to store calculated ranks
        map<string, double> Rank;

    public:
        // Calculates PageRank of URLs
        string PageRank(int p);
        // Inserts edges going from "from" to "to" and vice versa
        void insertEdge(string from, string to);

        // GETTERS (for catch tests)

        // Use a set to get unique websites as it gets rid of duplicates (helper function)
        set<string> getUniqueWebsites()
        {
            set<string> uniqueWebsites;

            // Iterate through URLs in adjList
            for (const auto& url : adjList)
            {
                // Insert keys into the set
                uniqueWebsites.insert(url.first);
            }

            // Repeat but with the inDegree map this time
            for (const auto& url : inDegree)
            {
                // Insert keys into the set
                uniqueWebsites.insert(url.first);
            }

            return uniqueWebsites;
        }

        // Gets adjList
        const map<string, vector<string>>& getAdjList() const
        {
            return adjList;
        }
        // Gets in degree
        const map<string, vector<string>>& getInDegree() const
        {
            return inDegree;
        }
        // Gets calculated rank
        const map<string, double>& getRank() const
        {
            return Rank;
        }
};

// References:
// Office Hours (Amay): suggested to use a map for rank and in degree

