/*
filename:ds07_1.cc
date:2017/11/25
author:Secone
*/
#include <iostream>
#include <iomanip>

using namespace std;

int map[100] = { 0 };
int path[100] = { 0 };

void init() {
	cout << "Please input the edge and end by 0 0 0: " << endl;
	for (int i = 0; i <= 5; ++i) {
		for (int j = 0; j <= 5; ++j) {
			path[i * 6 + j] = -1;
			if (i != j) {
				//initial the weight of edge is infinate
				map[i * 6 + j] = 0xFFFFFF;
			}			
		}
	}
}
void input() {
	char temp1, temp2;
	int temp3;
	//get edge
	cin >> temp1 >> temp2 >> temp3;
	while (temp1 != '0' && temp2 != '0' && temp3 != 0) {
		map[(temp1 - 'a') * 6 + (temp2 - 'a')] = temp3;
		cin >> temp1 >> temp2 >> temp3;
	}
}
void cal() {
	//floyd calculate the A and path
	for (int i = 0; i <=5 ; ++i) {
		for (int j = 0; j <= 5; ++j) {
			for (int k = 0; k <= 5; ++k) {
				if (map[i * 6 + k] + map[k * 6 + j] < map[i * 6 + j]) {
					map[i * 6 + j] = map[i * 6 + k] + map[k * 6 + j];
					path[i * 6 + j] = k;
				}
			}
		}
	}
}
void output() {
	//output the path and distance
	for (int i = 0; i <= 5; ++i) {
		for (int j = 0; j <= 5; ++j) {
			cout << i << "->" <<  j << ':';
				if (map[i * 6 + j] != 0xffffff) {
					cout << map[i * 6 + j] << ", route is ";
					cout << i << "->";
					int temp = i;
					while (path[temp * 6 + j] != -1) {
						cout << path[temp * 6 + j] << "->";
						temp = path[temp * 6 + j];
					}
					cout << j;
				}
				else {
					cout << "N/A";
				}
				cout << endl;
		}
		cout << endl;
	}
}

int main() {
	init();
	input();
	cal();
	output();
	return 0;
}
