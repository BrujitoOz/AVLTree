#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <string>
#include <sstream>
#include "AVLTree.h"
using namespace std;
class Book {
	string name;
	int year;
	float score;
public:
	Book(string name, int year, float score) : name(name), year(year), score(score) {}
	string GetName() { return name; }
	int GetYear() { return year; }
	float GetScore() { return score; }

	void SetName(string name) { this->name = name; }
	void SetYear(int year) { this->year = year; }
	void SetScore(float score) { this->score = score; }
};

string rndStr() {
	int n = 10 + rand() % 21;
	stringstream ss;
	for (int i = 0; i < n; i++) {
		ss << (char)('a' + rand() % 27);
	}
	return ss.str();
}
int main() {
	typedef AVLTree<Book*, string, nullptr> TreeStr;
	typedef AVLTree<Book*, int, nullptr> TreeInt;
	typedef AVLTree<Book*, float, nullptr> TreeFlt;

	auto l1 = [](Book* a) { return a->GetName(); };
	auto l2 = [](Book* a) { return a->GetYear(); };
	auto l3 = [](Book* a) { return a->GetScore(); };

	TreeStr* NameTree = new TreeStr(l1);
	TreeInt* YearTree = new TreeInt(l2);
	TreeFlt* ScoreTree = new TreeFlt(l3);

	for (int i = 0; i < 1e4; i++) {
		string name = rndStr();
		int year = 1800 + rand() % 220;
		float score = (1 + rand() % 101) / 20;
		Book* book = new Book(name, year, score);
		NameTree->add(book);
		YearTree->add(book);
		ScoreTree->add(book);
		if ((i + 1) % 10000 == 0) {
			cout << "+";
		}
	}
	cout << endl;
	auto prnt = [](Book* a) {
		if (a != nullptr) {
			cout << "{"
				<< a->GetName() << ", "
				<< a->GetYear() << ", "
				<< a->GetScore() << "}\n";
		}
		else {
			cout << "Not found\n";
		}
	};
	cout << NameTree->Height() << endl;
	cout << YearTree->Height() << endl;
	cout << ScoreTree->Height() << endl;

	prnt(NameTree->find("asa"));
	prnt(YearTree->find(2011));
	prnt(ScoreTree->find(4.5));
	delete NameTree, YearTree, ScoreTree;
	system("pause");
	return 0;
}