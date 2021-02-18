#include "pch.h"
#include <iostream>
#include <vector>
using namespace std;

bool Strike(int x1, int y1, int x2, int y2) // возвращает true, если 1 бьется 2 ферзем
{
	return (x1 == x2 || y1 == y2 || (x1 + y1 == x2 + y2) || (x1 - y1 == x2 - y2));
}

bool noStrikeBoard(const int n, vector<vector<bool>> &array, int x, int y) // возвращает true, если ферзя на этой клетке никто не может побить
{
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++) {
			if (!(x == i && y == j))		// не та же самая клетка
				if (array[i][j])			// на этой клетке стоит ферзь
					if (Strike(x, y, i, j))	// может ли этот ферзь побить ферзя на клетке (x,y)
						return false;
		}
	return true;
}

void setArrayToFalse(const int n, vector<vector<bool>> &array) {
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			array[i][j] = false;
}

void countPositions(const int n, vector<vector<bool>> &array, int &countOut, int &row) {
	if (row == 0) {		// первый ряд 
		for (int i = 0; i < n; i++) {
			setArrayToFalse(n, array);
			row = 0;
			array[row][i] = true;
			if (1 == n) {
				countOut++;
				return;
			}
			row++;
			countPositions(n, array, countOut, row);
		}
	}
	else if (row == n - 1) {//последний ряд
		for (int i = 0; i < n; i++) {
			if (noStrikeBoard(n, array, row, i))
				countOut++;
		}
		//return;
	}
	else {	// ряды между
		for (int i = 0; i < n; i++) {
			if (noStrikeBoard(n, array, row, i)) {
				array[row][i] = true;
				int new_row = row + 1;
				countPositions(n, array, countOut, new_row);
				array[row][i] = false;
			}
		}
		//return;
	}
}

int main() {
	int n;
	cin >> n;
	vector<vector<bool>> array(n, vector<bool>(n));
	int count = 0;
	int row = 0;
	countPositions(n, array, count, row);
	cout << count << endl;
	return 0;
}