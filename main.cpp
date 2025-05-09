/*
* Topic 25: Applications of Linear Algebra in Transportation Problems
* Build: g++ -std=c++17 -o main main.cpp data.cpp
* Run: ./main
*/
#include "TP_data.h"
#include <algorithm>
#include <queue>
#include <climits>
#include <cmath>
#include <functional>
#include <cfloat>

struct Cell{
    int cost, i, j;
};
bool costComparison(const Cell& a, const Cell& b){
    return a.cost < b.cost;
}

int LeastCostMethod(Data& data, vector<vector<int>>& resultCostMatrix) {
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
    resultCostMatrix = allocator; // Update the result cost matrix
    return totalCost;
}

//MODI method
int MODI(Data& data, vector<vector<int>>& resultCostMatrix) {
    int m = data.numSources;
    int n = data.numDestinations;
    auto& cost = data.cost;

    // work with a double‐precision allocation to insert tiny eps
    vector<vector<double>> alloc(m, vector<double>(n, 0.0));
    for (int i = 0; i < m; ++i)
        for (int j = 0; j < n; ++j)
            alloc[i][j] = resultCostMatrix[i][j];

    // the smallest non‐zero “epsilon” to break degeneracy
    const double EPS = 1e-6;

    // count current basic variables
    int basicCount = 0;
    for (int i = 0; i < m; ++i)
      for (int j = 0; j < n; ++j)
        if (alloc[i][j] > 0.0)
          ++basicCount;

    // add EPS to some zeros until we have m + n - 1 basics
    for (int i = 0; basicCount < m + n - 1 && i < m; ++i) {
      for (int j = 0; basicCount < m + n - 1 && j < n; ++j) {
        if (alloc[i][j] == 0.0) {
          alloc[i][j] = EPS;
          ++basicCount;
        }
      }
    }

    // MODI iteration
    int iter = 0;
    while (true) {
      if (++iter > 1000) {
        cout << "Too many iterations, exiting..." << endl;
        break;
      }

      // potentials u and v
      vector<double> u(m, NAN), v(n, NAN);
      u[0] = 0.0;

      bool changed = true;
      while (changed) {
        changed = false;
        for (int i = 0; i < m; ++i) {
          for (int j = 0; j < n; ++j) {
            if (alloc[i][j] > 0.0) {
              if (!isnan(u[i]) && isnan(v[j])) {
                v[j] = cost[i][j] - u[i];
                changed = true;
              }
              if (!isnan(v[j]) && isnan(u[i])) {
                u[i] = cost[i][j] - v[j];
                changed = true;
              }
            }
          }
        }
      }

      // compute reduced costs
      double minDelta = 0.0;
      int bi = -1, bj = -1;
      vector<vector<double>> delta(m, vector<double>(n, 0.0));
      for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
          if (alloc[i][j] == 0.0) {
            delta[i][j] = cost[i][j] - (u[i] + v[j]);
            if (delta[i][j] < minDelta) {
              minDelta = delta[i][j];
              bi = i; bj = j;
            }
          }
        }
      }
      if (minDelta >= 0.0) break;  // optimal

      // build row/col adjacency for basics + (bi,bj)
      vector<vector<int>> rowAdj(m), colAdj(n);
      for (int i = 0; i < m; ++i)
        for (int j = 0; j < n; ++j)
          if (alloc[i][j] > 0.0 || (i == bi && j == bj)) {
            rowAdj[i].push_back(j);
            colAdj[j].push_back(i);
          }

      // find alternating cycle
      vector<pair<int,int>> path;
      vector<vector<bool>> seen(m, vector<bool>(n, false));
      function<bool(int,int,int)> dfs = [&](int i, int j, int dir) {
        if (i == bi && j == bj && path.size() >= 4 && path.size()%2==0)
          return true;
        if (seen[i][j]) return false;
        seen[i][j] = true;
        path.emplace_back(i,j);

        if (dir == 0) {         // move along row
          for (int nj : rowAdj[i]) {
            if ((i==bi&&nj==bj&&path.size()>=3) || nj!=j)
              if (dfs(i, nj, 1)) return true;
          }
        } else {               // move along column
          for (int ni : colAdj[j]) {
            if ((ni==bi&&j==bj&&path.size()>=3) || ni!=i)
              if (dfs(ni, j, 0)) return true;
          }
        }

        seen[i][j] = false;
        path.pop_back();
        return false;
      };
      dfs(bi, bj, 0);

      // find theta = min allocation on odd positions
      double theta = DBL_MAX;
      for (int k = 1; k < (int)path.size(); k+=2) {
        auto [i,j] = path[k];
        theta = min(theta, alloc[i][j]);
      }

      // update allocations along the cycle
      for (int k = 0; k < (int)path.size(); ++k) {
        auto [i,j] = path[k];
        if (k%2==0) alloc[i][j] += theta;
        else          alloc[i][j] -= theta;
      }
    }

    // compute & write back integer result
    int totalCost = 0;
    for (int i = 0; i < m; ++i) {
      for (int j = 0; j < n; ++j) {
        int x = int(round(alloc[i][j]));
        resultCostMatrix[i][j] = x;
        totalCost += x * cost[i][j];
      }
    }
    return totalCost;
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
    vector<vector<int>> resultCostMatrix1 = data1.cost;
    vector<vector<int>> resultCostMatrix2 = data2.cost;
    vector<vector<int>> resultCostMatrix3 = data3.cost;


    // Call the Least Cost Method and MODI method
    cout << "LCM1 = " << LeastCostMethod(data1, resultCostMatrix1) << endl;
    cout << "LCM2 = " << LeastCostMethod(data2, resultCostMatrix2) << endl;
    cout << "LCM3 = " << LeastCostMethod(data3, resultCostMatrix3) << endl;
    cout << "MODI1 = " << MODI(data1, resultCostMatrix1) << endl;
    cout << "MODI2 = " << MODI(data2, resultCostMatrix2) << endl;
    cout << "MODI3 = " << MODI(data3, resultCostMatrix3) << endl;
    return 0;
}
/* g++ -std=c++17 main.cpp data.cpp -o main
./main*/