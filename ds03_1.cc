/*
filename:ds03_1.cc
date:2017/10/22
author:Secone
*/
#include <iostream>
#include <stack>

using namespace std;

int GetFibByRecursion(const int);
int GetFibByRecursive(const int);
int GetFibByStack(const int);

int main() {
	cout << GetFibByRecursive(10) << endl;
	cout << GetFibByRecursion(10) << endl;
	cout << GetFibByStack(10) << endl;
	return 0;
}

int GetFibByRecursion(const int n) {
	if (n <= 1) {
		return n;
	}
	return (GetFibByRecursion(n - 1) + GetFibByRecursion(n - 2));
}

int GetFibByRecursive(const int n) {
	int former = 0, ans = 1;
	for (int i = 2; i <= n; ++i) {
		ans += former;
		former = ans - former;
	}
	return ans;
}

int GetFibByStack(const int n) {
	stack<int> sta;
	sta.push(0);
	sta.push(1);
	for (int i = 2; i <= n; ++i) {
		int temp1, temp2;
		temp2 = sta.top();
		sta.pop();
		temp1 = sta.top();
		sta.pop();
		sta.push(temp2);
		sta.push(temp1 + temp2);
	}
	return sta.top();
}
