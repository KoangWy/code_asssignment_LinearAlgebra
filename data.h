#ifndef DATA_H
#define DATA_H

#include <vector>
#include <iostream>
#include <iomanip>
using namespace std;

// Transportation problem's data structure
class Data {
public:
    vector<int> supply;
    vector<int> demand;
    vector<vector<int>> cost;
    int numSources;
    int numDestinations;

    Data(int numSources, int numDestinations);
    Data(int numSources, int numDestinations, vector<int> supply, vector<int> demand, vector<vector<int>> cost);
    void setSupply(int index, int value);
    void setDemand(int index, int value);
    void setCost(int source, int destination, int value);
    int totalSupply();
    int totalDemand();
    void printData();
    void toBalance(); // Add a method to balance the supply and demand by adding a dummy source or destination
};

#endif // DATA_H