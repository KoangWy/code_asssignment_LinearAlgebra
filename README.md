# 🚚 Application of Linear Algebra in Transportation Problems

This project demonstrates how **Linear Algebra** can be applied to solve **Transportation Problems** using classical optimization methods in **C++**.

- **Least Cost Method**: to find an initial feasible solution.
- **MODI Method**: to optimize the initial solution to reach minimum cost.

## 📌 Objectives

- Model transportation problems with supply, demand, and cost matrices.
- Balance unbalanced problems by introducing dummy sources or destinations.
- Apply initial allocation and optimization techniques to minimize transportation costs.

## 🧱 Project Structure

```
code_asssignment_LinearAlgebra/  # Assignment folder
  ├─ data.h                   # Data class definition
  ├─ data.cpp                 # Data class implementation
  ├─ TP_data.h                # Contains sample testcases (data_1, data_2,...)
  ├─ main.cpp                 # Entry point: runs the algorithms on selected data
  └─ README.md                # Project documentation (this file)
```

## 🔧 Prerequisites

- A C++17-compatible compiler (e.g., `g++` or `clang++`).
- C++ Standard Library support for STL containers.

## 🏗️ Build & Run

Navigate to the `code_asssignment_LinearAlgebra` directory:

```bash
cd code_asssignment_LinearAlgebra
```

Build and run using g++:

```bash
g++ -std=c++17 main.cpp data.cpp -o main
./main
```

## 🚀 Usage

1. The program loads three predefined datasets (`data_1`, `data_2`, `data_3`).
2. Each dataset is balanced (if needed) by adding a dummy source/destination.
3. The initial feasible solution is computed with the **Least Cost Method**.
4. The solution is optimized using the **MODI Method**.
5. Results (supply, demand, cost matrix, total cost) are printed to the console.

## 📝 License

This project is licensed under the [MIT License](./LICENSE).

*Built on May 2025*
