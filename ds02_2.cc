/*
filename:ds02_2.cc
date:2017/10/21
author:Secone
*/
#include <iostream>
#include <string>

using namespace std;

//every element
struct Student {
	string name;
	int score;
	long int numb;
	struct Student *next;
};

void GetOptions(int &);
void ExcuteOption(const int &, struct Student *&);
void PrintData(struct Student *&);
void DeleteSomeData(int, int, struct Student *&);
void AddStudent(const struct Student &, struct Student *&);
	
int main () {
	struct Student *phead = NULL;
	int option;
	GetOptions(option);
	while (option) {
		ExcuteOption(option, phead);
		GetOptions(option);
	}
	return 0;
}

void AddStudent(const struct Student &temp, struct Student *& phead) {
	struct Student *pstu = new struct Student;
	if (!pstu) exit(-1);
	*pstu = temp;
	//head is NULL
	if (!phead) {
		phead = pstu;
		return;
	}
	//change pointer of head
	if (pstu -> numb < phead -> numb) {
		pstu -> next = phead;
		phead = pstu;
		return;
	}
	//insert in the liner table
	struct Student *pcur = phead;
	while (pcur -> next) {
		if (pstu -> numb < pcur -> next -> numb) {
			pstu -> next = pcur -> next;
			pcur -> next = pstu;
			return;
		}
		pcur = pcur -> next;
	}
	pcur -> next = pstu;
	return;
}

void PrintData(struct Student *&phead) {
	int cnt = 0;
	struct Student *ptemp = phead;
	while (ptemp) {
		++cnt;
		cout << cnt << ' ' << ptemp -> numb << ' ' << ptemp -> name << ' '
			<< ptemp -> score << endl;
		ptemp = ptemp -> next;
	}
}

void DeleteSomeData(int mink, int maxk, struct Student *&phead) {
	struct Student *ptemp = phead, *previous = NULL;
	phead = NULL;
	while (ptemp) {
		if (ptemp -> numb > mink && ptemp -> numb < maxk) { //need delete
			if (phead) { //had head pointer
				previous -> next = ptemp -> next;
				delete(ptemp);
				ptemp = previous -> next;
			} else { //don't had head pointer
				ptemp = ptemp -> next;
			}
		} else { //don't need delete
			if (!phead) {
				phead = ptemp;
			}
			previous = ptemp;
			ptemp = ptemp ->next;
		}
	}
	return;
}

void GetOptions(int &option) {
	cout << "1.Add a student" << endl;
	cout << "2.Print all data" << endl;
	cout << "3.Delete some data" << endl;
	cout << "0.Exit the system" << endl;
	cin >> option;
	return;
}

void ExcuteOption(const int &option, struct Student *&phead) {
	if (option == 1) {
		struct Student temp;
		//get the input data
		cout << "Please input the number of the student: " << endl;
		cin >> temp.numb;
		cout << "Please input the name of the student: " << endl;
		getchar();
		getline(cin, temp.name);
		cout << "Please input the score of the student: " << endl;
		cin >> temp.score;
		temp.next = NULL;
		AddStudent(temp, phead);
	}
	if (option == 2) {
		PrintData(phead);
	}
	if (option == 3) {
		cout << "Plead input the mink and the mink: " << endl;
		//get maxk and mink, make sure mink < maxk
		int maxk, mink;
		cin >> mink >> maxk;
		if (maxk < mink) {
			int temp;
			temp = mink; mink = maxk; maxk = temp;
		}
		cout << mink << ' ' << maxk << endl;
		DeleteSomeData(mink, maxk, phead);
	}
	return;
}
