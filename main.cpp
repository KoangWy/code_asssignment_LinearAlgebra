/*
* Topic 25: Applications of Linear Algebra in Transportation Problems
* Build: g++ -std=c++17 -o main main.cpp data.cpp
* Run: ./main
*/
#include "TP_data.h"

struct Cell{
    int cost, i, j;
};
bool costComparison(const Cell& a, const Cell& b){
    return a.cost < b.cost;
}
int LeastCostMethod(Data& data) {
    int totalCost = 0;
    int n = data.numDestinations; // Number of shop
    int m = data.numSources; //  Number of supplier
    vector<int> supply = data.supply;
    vector<int> demand = data.demand;
    vector<vector<int>> cost = data.cost;
    vector<vector<int>> allocator(m, vector<int>(n , 0)); // Vector m hang n cot toan la 0

    vector<Cell> cells;
    for(int i = 0; i < m; i++){
        for(int j = 0; j < n; j++){
            cells.push_back({cost[i][j], i, j});
        }
    }
    sort(cells.begin(), cells.end(), costComparison);
    vector<bool> rowDone(m, false), colDone(n, false); // Vector m hang n cot toan la false
    for(auto & cell : cells){
        int i = cell.i, j = cell.j;
        if (rowDone[i] || colDone[j]) { 
            continue;
        }

        int qty = min(supply[i], demand[j]);
        allocator[i][j] = qty;
        supply[i]  -= qty;
        demand[j]  -= qty;
        totalCost  += qty * cell.cost;

        // If a row or column is exhausted, mark it done
        if (supply[i] == 0) rowDone[i] = true;
        if (demand[j] == 0) colDone[j] = true;
    }
    return totalCost;
}
vector<vector<int>> NWmethod(Data& data){
    int n = data.numDestinations; // Number of shop
    int m = data.numSources; //  Number of supplier
    vector<int> supply = data.supply;
    vector<int> demand = data.demand;
    vector<vector<int>> cost = data.cost;
    vector<vector<int>> allocator(m, vector<int>(n , 0));
    int i = 0, j = 0;
    while (i < m && j < n) {
        int qty = min(supply[i], demand[j]);
        allocator[i][j] = qty;
        supply[i]  -= qty;
        demand[j]  -= qty;
        if (supply[i] == 0)     ++i;
        else if (demand[j]==0)  ++j;
    }
    return allocator;
}
    //End of step 1: Finish the basic allocator using Northwest Corner method so MODI can be implemented
int MODI(Data& data) {
    int totalScore = 0;
    const int INF = 1e9; //Infinite number
    int n = data.numDestinations; // Number of shop
    int m = data.numSources; //  Number of supplier
    vector<int> supply = data.supply;
    vector<int> demand = data.demand;
    vector<vector<int>> cost = data.cost;
    vector<vector<int>> allocator = NWmethod(data);
    while (true) {
        vector<int> u(m, INF), v(n, INF); // 2 vectors to store u[i] and v[j]
        u[0] = 0; //Basic of MODI method
        bool changed = true;
        while (changed) {
            changed = false;
            for (int i = 0; i < m; ++i) {
                for (int j = 0; j < n; ++j) {
                    if (allocator[i][j] > 0) {
                        if (u[i] != INF && v[j] == INF) {
                            v[j] = cost[i][j] - u[i];
                            changed = true;
                        }
                        if (v[j] != INF && u[i] == INF) {
                            u[i] = cost[i][j] - v[j];
                            changed = true;
                        }
                    }
                }
            }
        }
        //End of step 2: Finish calculating u[i] and v[j]
        int bestDelta = 0, bi=-1, bj=-1; // best i and best j = -1 
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (allocator[i][j] == 0) {
                    int currDelta = cost[i][j] - (u[i] + v[j]);
                    if (currDelta < bestDelta) {
                        bestDelta = currDelta;
                        bi = i; bj = j;
                    }
                }
            }
        }
        if (bestDelta >= 0) break;
        //Condition to end loop: all delta return positive value
        //End of step 3: Constantly integrating until all deta >= 0
        int i0 = bi, j0 = bj;
        bool found = false;
        vector<pair<int, int>> loop4;
        loop4.reserve(4);
        
        for (int j1 = 0; j1 < n && !found; ++j1) {  
            if (j1==j0 || allocator[i0][j1]==0) continue;
            for (int i1 = 0; i1 < m && !found; ++i1) {
                if (i1==i0 || allocator[i1][j1]==0) continue;
                if (allocator[i1][j0] > 0) {
                    loop4.clear();
                    loop4.push_back({i0,j0});
                    loop4.push_back({i0,j1});
                    loop4.push_back({i1,j1});
                    loop4.push_back({i1,j0});
                    found = true;
                }
            }
        }
        if (!found) {

            break; // Thoát khỏi vòng lặp while(true)
        }
        //End of step 4: find square
        int theta = INT_MAX;
        for (int k = 1; k < 4; k += 2) {
            auto [ii, jj] = loop4[k];
            theta = min(theta, allocator[ii][jj]);
        }
        for (int k = 0; k < 4; k++) {
            auto [ii, jj] = loop4[k];
            allocator[ii][jj] += (k % 2 == 0 ? +theta : -theta);
        }
        //End of step 5: Value modification for square
    }
    for (int i = 0; i < m; ++i)
            for (int j = 0; j < n; ++j)
                if (allocator[i][j] > 0)
                    totalScore += allocator[i][j] * cost[i][j];
    return totalScore;
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
    cout << "LCM1 = " << LeastCostMethod(data1) << '\n'; 
    cout << "LCM2 = " << LeastCostMethod(data2) << '\n'; 
    cout << "LCM3 = " << LeastCostMethod(data3) << '\n'; 
    cout << "MODI 1 =" << MODI(data1) << "\n";
    cout << "MODI 2 =" << MODI(data2) << "\n";
    cout << "MODI 3 =" << MODI(data3) << "\n";
    return 0;
}
/* g++ -std=c++17 main.cpp data.cpp -o main
./main*/