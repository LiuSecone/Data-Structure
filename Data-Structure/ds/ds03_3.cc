/*
filename:ds03_2.cc
date:2017/10/22
author:Secone
*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

using namespace std;

void Dfs(int, int, vector<int> &);
void PrintAnswer(const vector<int> &);

int n, t, counter;
vector<int> weight;

int main () {
	cin >> n >> t;
	int sum = 0;
	for (int i = 0; i < n; ++i) {
		int temp;
		cin >> temp;
		weight.push_back(temp);
		sum += temp;
	}
	if (sum == t) {
		for (auto &iter : weight) {
			cout << iter << ' ';
		}
		cout << endl;
		++counter;
	} else {
		vector<int> stack;
		Dfs(-1, 0, stack);
	}
	cout << counter << endl;
	return 0;
}

void Dfs(int num, int totweight, vector<int> &stack){
	if (totweight == t) {
		PrintAnswer(stack);
		return;
	}
	if (totweight > t) {
		return;
	}
	if (num == n) {
		return;
	}
	stack.push_back(num + 1);
	Dfs(num + 1, totweight + weight[num + 1], stack);
	stack.pop_back();
	Dfs(num + 1, totweight, stack);
	return;
}

void PrintAnswer(const vector<int> &stack) {
	for (auto &iter : stack) {
		cout << iter << ' ';
	}
	cout << endl;
	++counter;
	return;
}
