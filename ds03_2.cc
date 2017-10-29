/*
filename:ds03_2.cc
date:2017/10/29
author:Secone
*/
#include <iostream>

using namespace std;

struct Node {
	int element;
	struct Node *next;
};

class Queue {
private:
	struct Node *m_ptail;
	int m_size;
public:
	Queue () {
		m_ptail = NULL;
		m_size = 0;
		return;
	}
	int push_(const int &);
	int pop_();
	int top_();
	int size_();
};

int Queue::push_(const int &element) {
	++m_size;
	struct Node *newnode = new struct Node;
	newnode -> element = element;
	if (m_ptail) { //if it is not empty
		newnode -> next = m_ptail -> next;
		m_ptail -> next = newnode;
	} else { //if it is empty
		m_ptail = newnode;
		newnode -> next = newnode;
	}
	return m_size;
}

int Queue::pop_() {
	//if it is empty
	if (!m_ptail) {
		return -1;
	}
	--m_size;
	if (m_ptail -> next == NULL) { //if just one element
		delete m_ptail;
		m_ptail = NULL;
	} else {
		//find the second last element
		struct Node *curnode = m_ptail;
		while (curnode -> next != m_ptail) {
			curnode = curnode -> next;
		}
		curnode -> next = m_ptail -> next;
		delete m_ptail;
		m_ptail = curnode;
	}
	return m_size;
}

int Queue::top_() {
	return m_ptail -> element;
}

int Queue::size_() {
	return m_size;
}

int main() {
	Queue que;
	que.push_(5);
	que.push_(7);
	que.push_(3);
	que.push_(8);
	cout << que.push_(55) << endl;
	que.pop_();
	que.pop_();
	cout << que.pop_() << endl;
	que.pop_();
	cout << que.pop_() << endl;
	cout << que.pop_() << endl;
	return 0;
}
 
