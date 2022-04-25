#include <iostream>
using namespace std;
#include "Classes.h"

int main() {
	map<int, int> a;
	map<int, int> b;

	a.insert(5, 33);
	a.insert(3, 13);
	a.insert(2, 53);
	a.insert(1, 41);
	a.insert(10, 61);
	a.insert(6, 11);
	a.insert(8, 21);
	a.insert(4, 15);
	a.insert(14, 31);
	a.insert(44, 20);

	b.insert(12, 55);
	b.insert(7, 65);
	b.insert(54, 40);
	b.insert(55, 60);
	b.insert(78, 75);
	b.insert(81, 57);
	b.remove(54);

	a.get_values();
	cout << endl;
	a.get_keys();
	cout << endl;
	cout << a.find(1)->elem << endl << endl;

	b.get_values();
	cout << endl;
	b.get_keys();
	cout << endl;
	cout << b.find(7)->elem << endl << endl;

	a.print();
	cout << endl;
	b.print();

	cout << endl;
	a.clear();

	return 0;
}
