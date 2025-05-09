#include "data.h"

Data::Data(int numSources, int numDestinations) : numSources(numSources), numDestinations(numDestinations) {
    supply.resize(numSources);
    demand.resize(numDestinations);
    cost.resize(numSources, vector<int>(numDestinations));
}

Data::Data(int numSources, int numDestinations, vector<int> supply, vector<int> demand, vector<vector<int>> cost)
    : numSources(numSources), numDestinations(numDestinations), supply(supply), demand(demand), cost(cost) {
    this->supply = supply;
    this->demand = demand;
    this->cost = cost;
}

void Data::setSupply(int index, int value) {
    if (index >= 0 && index < numSources) {
        supply[index] = value;
    }
}

void Data::setDemand(int index, int value) {
    if (index >= 0 && index < numDestinations) {
        demand[index] = value;
    }
}

void Data::setCost(int source, int destination, int value) {
    if (source >= 0 && source < numSources && destination >= 0 && destination < numDestinations) {
        cost[source][destination] = value;
    }
}

int Data::totalSupply() {
    int total = 0;
    for (int i = 0; i < numSources; ++i) {
        total += supply[i];
    }
    return total;
}

int Data::totalDemand() {
    int total = 0;
    for (int i = 0; i < numDestinations; ++i) {
        total += demand[i];
    }
    return total;
}

void Data::toBalance() {
    int totalSupply = this->totalSupply();
    int totalDemand = this->totalDemand();

    if (totalSupply > totalDemand) {
        demand.push_back(totalSupply - totalDemand);
        numDestinations++;
        for (int i = 0; i < numDestinations; ++i) {
            cost[i].push_back(0);
        }
        
    } else if (totalDemand > totalSupply) {
        supply.push_back(totalDemand - totalSupply);
        numSources++;
        cost.push_back(vector<int>(numDestinations, 0));
    }
}

void Data::printData() {
    cout << "Sources:" << setw(12);;
    for (int i = 0; i < numSources; ++i) {
        cout << supply[i] << setw(5);
    }
    cout << endl << "--------------------------------------------------" << endl;
    cout << "Destinations|" << endl;
    for (int i = 0; i < numDestinations; ++i) {
        cout << setw(12) << demand[i] << "|" << setw(7);
        for (int j = 0; j < numSources; ++j) {
            cout << cost[j][i] << setw(5);
        }
        cout << endl;
    }
    cout << "total supply: " << totalSupply() << endl;
    cout << "total demand: " << totalDemand() << endl;
    cout << "---------------------------------------------------" << endl;
}