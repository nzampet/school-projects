/*
 * Name: Nikolaus Zampetopoulos
 * Date Submitted: 11/19/2022
 * Lab Section: 003
 * Assignment Name: Using Recursion to Solve the N-Queens Problem
 */

#include <iostream>
#include <vector>

using namespace std;

template <typename T>
void initVect(vector<T> &vect, int n) {
    vect.resize(n);
    fill(vect.begin(), vect.end(), T());
}

struct Grid {
    //vector<bool> rows;
    vector<bool> cols;
    vector<bool> incDiag;
    vector<bool> decDiag;
    Grid(int n) {
        initVect(cols, n);
        initVect(incDiag, n * 2 - 1);
        initVect(decDiag, n * 2 - 1);
    }
};

//Returns the increasing diagonal index from row, and col positions
int getIncDiag(int row, int col) {
    return row + col;
}

//Returns the decreasing diagonal index from size, row, and col positions
int getDecDiag(int n, int row, int col) {
    return n - row + col - 1;
}

//Iterates over rows in our grid to test if each cell can have a queen or not
//The 0th row only goes half way and doubles the result for efficency
int iterateRow(Grid &grid, int n, int r) {
    int solutions = 0;
    int midSolutions = 0;

    //Iterate over columns
    for (int col = 0; col < (r ? n : n / 2 + n % 2); col++) {
        //If current row/col would intersect with another queen
        if (grid.cols[col] ||
            grid.incDiag[getIncDiag(r, col)] ||
            grid.decDiag[getDecDiag(n, r, col)]) continue;

        //base case, if we reached the final row
        if (r == n - 1) { (n == 1) ? midSolutions++ : solutions++; continue; }

        //Set intersections for new queen
        grid.cols[col] = true;
        grid.incDiag[getIncDiag(r, col)] = true;
        grid.decDiag[getDecDiag(n, r, col)] = true;

        //Recurse to new rows for successfully placed queen
        if (r == 0 && col == n / 2)
            midSolutions += iterateRow(grid, n, r + 1);
        else
            solutions += iterateRow(grid, n, r + 1);

        //Reset queen so we can move onto the next row
        grid.cols[col] = false;
        grid.incDiag[getIncDiag(r, col)] = false;
        grid.decDiag[getDecDiag(n, r, col)] = false;
    }

    if (r == 0) return solutions * 2 + midSolutions;
    return solutions;
}

//Uses recursion to count how many solutions there are for
//placing n queens on an nxn chess board
int nQueens(int n) {
    //Implement int nQueens(int n)
    //Feel free to implement any recursive helper functions
    Grid grid(n);
    return iterateRow(grid, n, 0);
}

int main() {
    cout << "1: " << nQueens(1) << endl;
    cout << "2: " << nQueens(2) << endl;
    cout << "3: " << nQueens(3) << endl;
    cout << "4: " << nQueens(4) << endl;
    cout << "5: " << nQueens(5) << endl;
    cout << "6: " << nQueens(6) << endl;
    cout << "7: " << nQueens(7) << endl;
    cout << "8: " << nQueens(8) << endl;
    cout << "9: " << nQueens(9) << endl;
    cout << "10: " << nQueens(10) << endl;
    cout << "11: " << nQueens(11) << endl;
    cout << "12: " << nQueens(12) << endl;
    return 0;
}