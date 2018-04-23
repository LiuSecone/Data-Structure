/*
filename: ds02_1.cc
date: 2017/10/21
author: Secone
*/
#include <iostream>
#include <vector>
#include <string>

using namespace std;

//every element
struct Student {
	string name;
	int score;
	long int numb;
};

class LinerTable {
private:
	vector<struct Student> m_vec;
public:
	void add_student_(const struct Student stu);
	void print_data_();
};

void GetOptions(int &);
void ExcuteOption(const int, LinerTable &);

int main () {
	LinerTable table;
	int option;
	GetOptions(option);
	while (option) {
		ExcuteOption(option, table);
		GetOptions(option);
	}
	return 0;
}

void LinerTable::add_student_(const struct Student stu) {
	//if find any number of the element is bigger than number of stu
	//then insert stu before it
	for (auto iter = m_vec.begin(); iter != m_vec.end(); ++iter) {
		if (stu.numb < iter -> numb) {
			m_vec.insert(iter, stu);
			return;
		}
	}
	//the number of stu is the bigggest, add it at the last
	m_vec.push_back(stu);
}

void LinerTable::print_data_() {
	int cnt = 0;
	//range for to output
	for (auto &iter : m_vec) {
		++cnt;
		cout << cnt << ' ' << iter.numb << ' ' 
			<< iter.name << ' ' << iter.score << endl;
	}
	return;
}

void GetOptions(int &option) {
	cout << "1.Add a student" << endl;
	cout << "2.Print all data" << endl;
	cout << "0.Exit the system" << endl;
	cin >> option;
	return;
}

void ExcuteOption(const int option, LinerTable &table) {
	if (option - 1) {
		table.print_data_();
	} else {
		struct Student temp;
		//get the input data
		cout << "Please input the number of the student: " << endl;
		cin >> temp.numb;
		cout << "Please input the name of the student: " << endl;
		getchar();
		getline(cin, temp.name);
		cout << "Please input the score of the student: " << endl;
		cin >> temp.score;
		table.add_student_(temp);
	}
	return;
}
