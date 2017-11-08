/*
filename:ds05_1.cc
date:2017/11/8
author:Secone
*/
#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct Tree {
	char name;
	struct Tree *left, *right;
};

void ChooseMode(int &mode) {
	cout << "Please input the mode you want to use:" << endl;
	cout << "1. Create tree by first ordre." << endl;
	cout << "2. Create tree by first and middle order." << endl;
	cin >> mode;
	--mode;
	getchar();
	return;
}

struct Tree *CreateByFirst(char name) {
	//condition of end is this node is * or called NULL
	if (name == '*') {
		return NULL;
	}
	struct Tree *root = new struct Tree;
	//name this node
	root->name = name;
	//get left children and right children by recursion
	root->left = CreateByFirst(getchar());
	root->right = CreateByFirst(getchar());
	return root;
}

struct Tree *CreateByTwo(const string &str1, const string &str2) {
	//str1 or str2 is empty means this node is not existed
	if (str1.empty()) {
		return NULL;
	}
	//find the root position
	int position = str2.find(str1[0]);
	int length = str1.length();
	struct Tree *root = new struct Tree;
	//name this node
	root->name = str1[0];
	//cut the string and get left children and right children by recursion
	root->left = CreateByTwo(str1.substr(1, position), str2.substr(0, position));
	root->right = CreateByTwo(str1.substr(position + 1, length - position - 1), str2.substr(position + 1, length - position - 1));
	return root;
}

int CountNode(struct Tree *root) {
	if (root == NULL) {
		return 0;
	}
	//count by recursion
	return CountNode(root->right) + CountNode(root->left) + 1;
}

void PrintTree(struct Tree *root, int depth) {
	if (root == NULL) {
		return;
	}
	for (int i = 0; i < depth; ++i) {
		cout << '	';
	}
	cout << root->name << endl;
	//print by recursion
	PrintTree(root->left, depth + 1);
	PrintTree(root->right, depth + 1);
	return;
}

int main() {
	int mode = 0;
	//choose mode
	ChooseMode(mode);
	//create tree
	struct Tree *tree = nullptr;
	if (!mode) {
		tree = CreateByFirst(getchar());
	}
	else {
		string str1, str2;
		cin >> str1 >> str2;
		tree = CreateByTwo(str1, str2);
	}
	//print node number
	cout << CountNode(tree) << endl;
	//print tree
	PrintTree(tree, 0);
	return 0;
}