#include "map.h"

using namespace std;

int main() {
	setlocale(LC_ALL, "rus");
	map<int, string> test;
	list<int>* keys = new list<int>();
	list<string>* values = new list<string>();
	node<int, string>* temp = new node<int, string>;
	keys = test.get_keys();
	test.insert(1, "jan");
	test.insert(2, "feb");
	test.insert(3, "mar");
	test.insert(4, "apr");
	test.insert(5, "may");
	test.insert(6, "jun");
	test.insert(7, "jul");
	test.insert(8, "aug");
	test.insert(9, "sep");
	test.insert(10, "oct");
	test.insert(11, "nov");
	test.insert(12, "dec");
	test.print();
	keys = test.get_keys();
	values = test.get_values();
	keys->print_to_console();
	cout << endl;
	values->print_to_console();
	test.clear();
	return 0;
}