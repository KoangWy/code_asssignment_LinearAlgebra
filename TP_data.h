#include "data.h"

//data_1
Data data_1() {
    Data data(3, 4);
    data.setSupply(0, 40);
    data.setSupply(1, 35);
    data.setSupply(2, 65);
    data.setDemand(0, 30);
    data.setDemand(1, 40);
    data.setDemand(2, 50);
    data.setDemand(3, 20);
    data.setCost(0, 0, 8);
    data.setCost(0, 1, 6);
    data.setCost(0, 2, 10);
    data.setCost(0, 3, 9);
    data.setCost(1, 0, 9);
    data.setCost(1, 1, 12);
    data.setCost(1, 2, 13);
    data.setCost(1, 3, 7);
    data.setCost(2, 0, 14);
    data.setCost(2, 1, 9);
    data.setCost(2, 2, 16);
    data.setCost(2, 3, 5);

    cout << "Data 1:" << endl;
    data.printData();
    return data;
}

//data_2
Data data_2() {
    Data data(4, 3);
    data.setSupply(0, 50);
    data.setSupply(1, 60);
    data.setSupply(2, 70);
    data.setSupply(3, 80);
    data.setDemand(0, 40);
    data.setDemand(1, 50);
    data.setDemand(2, 60);
    data.setCost(0, 0, 10);
    data.setCost(0, 1, 12);
    data.setCost(0, 2, 8);
    data.setCost(1, 0, 9);
    data.setCost(1, 1, 11);
    data.setCost(1, 2, 13);
    data.setCost(2, 0, 15);
    data.setCost(2, 1, 10);
    data.setCost(2, 2, 12);
    data.setCost(3, 0, 14);
    data.setCost(3, 1, 9);
    data.setCost(3, 2, 16);
    
    cout << "Data 2:" << endl;
    data.printData();
    return data;
}

//data_3
Data data_3() {
    vector<int> supply = { 33, 57, 21, 45, 39, 50, 12 };
    vector<int> demand = { 67, 25, 16, 40, 18, 30 };
    vector<vector<int>> cost = {
        {  8,  6, 10,  9,  7,  5 },
        {  9, 12, 13,  3,  8, 11 },
        { 14,  9, 16,  5,  6,  4 },
        { 10,  8, 12, 11,  9,  7 },
        { 18, 10, 14, 13, 12, 11 },
        { 11,  9,  2,  7,  6,  5 },
        { 12, 10, 14, 13, 11,  9 }
    };
    Data data(7, 6, supply, demand, cost);

    cout << "Data 3:" << endl;
    data.printData();
    return data;
}