/*
 * Name: Nikolaus Zampetopoulos
 * Date Submitted: 9/27/2022
 * Lab Section: 003
 * Assignment Name: Lab 3: Finding Groups Using Recursion
 */

#include "Grouping.h"

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

//Implement the (parameterized) constructor and findGroup functions below

//Grouping constructor that takes a string file name, opens the file, and 
//initalizes neccessary variables for grouping, then calls the grouping function
Grouping::Grouping(string fileName) {
    ifstream inputFile;
    inputFile.open(fileName, ios::in);

    //Loop through input file and scan in elements we populate our grid with
    char inputChar;
    for (int x = 0; x < 10; x++) {
        for (int y = 0; y < 10; y++) {
            inputFile.get(inputChar);

            if (inputChar == '.') {
                grid[x][y] = 0;
            } else if (inputChar == 'X') {
                grid[x][y] = 1;
            }

            //Also initalize the checkedGrid
            checkedGrid[x][y] = false;
        }
        inputFile.get(inputChar); //For new lines
    }

    //Clean up
    inputFile.close();

    //Call our group finding function
    for (int x = 0; x < 10; x++) {
        for (int y = 0; y < 10; y++) {
            findGroup(x, y, -1);
        }
    }
}

//Recursive function that when called on a group will find and
//add all new elements to the correct group
void Grouping::findGroup(int r, int c, int g) {
    if (r < 0 || c < 0 || r > 9 || c > 9) return;
    
    if (!grid[r][c]) return;

    if (checkedGrid[r][c]) return;

    checkedGrid[r][c] = true;

    if (g == -1) {
        g = groups.size();
        groups.push_back(vector<GridSquare>());
    }

    groups[g].push_back(GridSquare(r, c));

    findGroup(r + 1, c, g);
    findGroup(r - 1, c, g);
    findGroup(r, c + 1, g);
    findGroup(r, c - 1, g);
}

//Simple main function to test Grouping
//Be sure to comment out main() before submitting
int main()
{
    Grouping input1("input1.txt");
    input1.printGroups();
    
    return 0;
}

//Do not modify anything below

GridSquare::GridSquare() : row(0), col(0) {} //Default constructor, (0,0) square

GridSquare::GridSquare(int r, int c) : row(r), col(c) {} //(r,c) square

//Compare with == operator, used in test cases
bool GridSquare::operator== (const GridSquare r) const
{
    if ((row == r.row) && (col == r.col))
    {
        return true;
    }
    return false;
}

int GridSquare::getRow() //return row value
{
    return row;
}

int GridSquare::getCol() //return column value
{
    return col;
}

//Output using << operator, used in Grouping::printGroups()
//Function definition for <ostream> << <GridSquare>
ostream& operator<< (ostream& os, const GridSquare obj)
{
    os << "(" << obj.row << "," << obj.col << ")";
    return os;
}

Grouping::Grouping() : grid{},groups() {} //Default constructor, no groups

void Grouping::printGroups() //Displays grid's groups of squares
{
    for(unsigned int g=0; g<groups.size(); g++)
    {
        cout << "Group " << g+1 << ": ";
        for(unsigned int s=0; s<groups[g].size(); s++)
        {
            cout << " " << groups[g][s];
        }
        cout << endl;
    }
}

vector<vector<GridSquare>> Grouping::getGroups() //Needed in unit tests
{
    return groups;
}