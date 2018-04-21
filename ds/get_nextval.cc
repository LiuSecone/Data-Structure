#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main() {
	string str;
	cin >> str;
	vector <int> vec;
	int i = 1, j = 0;
	vec.push_back(str.length());
	str = '*' + str;
	vec.push_back(0);
	while (i < vec[0]) {
		if (j == 0 || str[i] == str[j]) {
			++i; ++j;
			if (str[i] != str[j]) {
				vec.push_back(j);
			} else {
				vec.push_back(vec[j]);
			}
		} else {
			j = vec[j];
		}
	}
	for (auto &iter : vec) {
		cout << iter << ' ';
	}
	cout << str[0];
	return 0;
}
