/*
filename:ds05_1.cc
date:2017/11/4
author:Secone
*/
#include <iostream>
#include <vector>

using namespace std;

struct Triad {
	int x = 0, y = 0, value = 0;
};

class Matrix {
private:
	int m_row, m_column;
	vector<struct Triad> m_triad;
public:
	Matrix(int r = 0, int c = 0);
	Matrix(int r, int c, const vector<struct Triad> &vec);
	Matrix operator+(const Matrix &com);
	Matrix operator*(const Matrix &com);
	void output_();
};

Matrix::Matrix(int r, int c) {
	m_row = r;
	m_column = c;
	//get matrix
	for (int i = 0; i < r; ++i) {
		for (int j = 0; j < c; ++j) {
			int temp;
			cin >> temp;
			if (temp) {
				struct Triad temp_triad;
				temp_triad.y = i;
				temp_triad.x = j;
				temp_triad.value = temp;
				m_triad.push_back(temp_triad);
			}
		}
	}
}
Matrix::Matrix(int r, int c, const vector<struct Triad> &vec) {
	m_row = r;
	m_column = c;
	//copy triad
	m_triad.assign(vec.begin(), vec.end());
}
Matrix Matrix::operator+(const Matrix &com) {
	if (m_row == com.m_row && m_column == com.m_column) {
		auto iter1 = m_triad.begin();
		auto iter2 = com.m_triad.begin();
		vector<struct Triad> temp_vec;
		for (int i = 0; i < m_row; ++i) {
			for (int j = 0; j < m_column; ++j) {
				struct Triad temp;
				temp.x = j;
				temp.y = i;
				if (iter1->y == i && iter1->x == j) {
					temp.value += iter1->value;
					//point to next triad
					++iter1;
				}
				if (iter2->y == i && iter2->x == j) {
					temp.value += iter2->value;
					++iter2;
				}
				if (temp.value) {
					temp_vec.push_back(temp);
				}
			}
		}
		return Matrix(m_row, m_column, temp_vec);
	}
	else {
		return Matrix(0, 0);
	}
}
Matrix Matrix::operator*(const Matrix &com) {
	if (m_row == com.m_column && m_column == com.m_row) {
		vector<struct Triad> temp_vec;
		for (int i = 0; i < m_row; ++i) {
			for (int j = 0; j < m_row; ++j) {
				struct Triad temp;
				temp.x = j;
				temp.y = i;
				//traversal two triad get the ans of this node
				for (auto iter1 = m_triad.begin(); iter1 != m_triad.end(); ++iter1) {
					for (auto iter2 = com.m_triad.begin(); iter2 != com.m_triad.end(); ++iter2) {
						if (iter1->y == i && iter2->x == j && iter1->x == iter2->y) {
							temp.value += iter1->value * iter2->value;
						}
					}
				}
				if (temp.value) {
					temp_vec.push_back(temp);
				}
			}
		}
		return Matrix(m_row, m_row, temp_vec);
	}
	else {
		return Matrix(0, 0);
	}
}
void Matrix::output_() {
	if (m_row && m_column){
		auto iter = m_triad.begin();
		for (int i = 0; i < m_row; ++i) {
			for (int j = 0; j < m_column; ++j) {
				//this triad is not empty and is the right node
				if (iter != m_triad.end() && i == iter->y & j == iter->x) {
					cout << iter->value;
					++iter;
				}
				else {
					cout << 0;
				}
				cout << ' ';
			}
			cout << endl;
		}
	}
	else {
		cout << "illegal" << endl;
	}
	return;
}

int main() {
	int r, c;
	cin >> r >> c;
	Matrix m1(r, c);
	cin >> r >> c;
	Matrix m2(r, c);
	(m1 + m2).output_();
	(m1 * m2).output_();
	return 0;
}
