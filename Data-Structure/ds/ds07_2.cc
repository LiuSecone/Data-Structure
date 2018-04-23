/*
filename:ds07_2.cc
date:2017/11/26
author:Secone
*/
#include <iostream>
#include <vector>

using namespace std;

vector<vector<int>> map;

void init();
void input();
bool dfs(int, int, int);

int main() {
	init();
	input();
	cout << dfs(1, 4, 0) << endl;
	return 0;
}

void init() {
	vector<int> temp;
	//initialize the map
	for (int i = 0; i <= 10; ++i) {
		map.push_back(temp);
	}
	return;
}

void input() {
	cout << "please input the edge and end by 0 0: " << endl;
	int temp1, temp2;
	//read the edge
	cin >> temp1 >> temp2;
	while (temp1 != 0 && temp2 != 0) {
		map[temp1].push_back(temp2);
		cin >> temp1 >> temp2;
	}
	return;
}

bool dfs(int current, int target, int depth) {
	//cut tree
	if (depth >= 3) return false;
	for (auto iter : map[current]) {
		//get the target return answer
		if (iter == target) {
			return true;
		}
		//not get the target, keep search
		return dfs(iter, target, depth + 1);
	}
}
