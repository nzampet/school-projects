/*
 * Name: Nikolaus Zampetopoulos
 * Date Submitted: 10/24/2022
 * Lab Section: 003
 * Assignment Name: Finding the Closest Pair of Points
 */

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <cmath>

using namespace std;

struct point
{
    double x;
    double y;
};


/*Takes in references to two cells and updates the passed in
  reference to the minimum to a new minimum if a lower vlaue is found
  It loops through each point in both cells and compares all of them
  If two points have the same locaion in memory they are the same point
  and are skipped
  returned as a double type value
*/
void compareCells(vector<point> &cell1,
                  vector<struct point> &cell2,
                  double &min) {
	for (point &pt1 : cell1) {
		for (point &pt2 : cell2) {
			if (&pt1 == &pt2) continue;

			double dist = sqrt((pt1.x - pt2.x) * (pt1.x - pt2.x) +
                               (pt1.y - pt2.y) * (pt1.y - pt2.y));
			if (dist < min) min = dist;
		}
	}
}

/*Implement the following function
  Reads in a file specified by the parameter
  Format of file: #of points on first line
                  remaining (#of points) lines: x-value and y-value of point
                  one point per line
                  x-value and y-value are double-precision values and
                  bounded by the unit square 0.0 <= x,y < 1.0
  Should use "spatial hashing" where the #of cells scales with the #of points
  and find the distance between the closest pair of points which will be
  returned as a double type value
*/
double closestPair(string filename) {
	//Open file
	ifstream file;
	file.open(filename);
	//Read in size
	int size;
	file >> size;
	//Calculate size of our grid of cells that will hold points
	//I think this is a good size for the grid for efficiency. It
	//averages 10 or less points per cell while not using too much memory
	//We find this number by finding the number of cells that 10 points
	//would use and then take the square root to find the width and height
	//if it were a triangle. I take the ceiling for cases where there are
	//less than 10 and for the extra speed. If I used a smaller number
	//instead of 10 it would be faster, but at the cost of memory.
	int gridSize = (int)ceil(sqrt(size / 10));
	//Initalize and populate our grid by reading from the file
	vector<vector<vector<point>>> grid(gridSize,
                                       vector<vector<point>>(gridSize));
	for (int i = 0; i < size; i++) {
		point newPoint;
		file >> newPoint.x;
		file >> newPoint.y;

		grid[(int)(newPoint.x * gridSize)]
            [(int)(newPoint.y * gridSize)].push_back(newPoint);
	}

	//Loop through our grid and check for matches
	double minimum = 1;
	for (int y = 0; y < gridSize; y++) {
		for (int x = 0; x < gridSize; x++) {
			compareCells(grid[x][y], grid[x][y], minimum);
			if (x != gridSize - 1)
				compareCells(grid[x][y], grid[x + 1][y], minimum);
			if (y != gridSize - 1)
				compareCells(grid[x][y], grid[x][y + 1], minimum);
			if (x != gridSize - 1 && y != gridSize - 1)
				compareCells(grid[x][y], grid[x + 1][y + 1], minimum);
		}
	}

	return minimum;
}

int main()
{
    double min;
    string filename;
    cout << "File with list of points within unit square: ";
    cin >> filename;
    min = closestPair(filename);
    cout << setprecision(16);
    cout << "Distance between closest pair of points: " << min << endl;
    return 0;
}