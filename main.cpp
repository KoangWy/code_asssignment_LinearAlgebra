/*
* Topic 25: Applications of Linear Algebra in Transportation Problems
* Build: g++ -std=c++17 -o main main.cpp data.cpp
* Run: ./main
*/
#include "TP_data.h"

int LeastCostMethod(Data& data) {
    // Implement the Least Cost Method algorithm here

    return 0;
}

int MODI(Data& data) {
    // Implement the MODI method algorithm here

    return 0;
}

int main() {
    Data data1 = data_1();
    data1.toBalance();
    cout << "Data 1 after balancing:" << endl;
    data1.printData();
    cout << endl;

    Data data2 = data_2();
    data2.toBalance();
    cout << "Data 2 after balancing:" << endl;
    data2.printData();
    cout << endl;

    Data data3 = data_3();
    data3.toBalance();
    cout << "Data 3 after balancing:" << endl;
    data3.printData();
    cout << endl;

    // Call the Least Cost Method and MODI method
    LeastCostMethod(data1);
    MODI(data1);
    LeastCostMethod(data2);
    MODI(data2);
    LeastCostMethod(data3);
    MODI(data3);
    return 0;
}