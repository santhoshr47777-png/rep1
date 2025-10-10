#include <iostream>
using namespace std;
int main() {
	cout.fill('*');
	cout.setf(ios::left, ios::adjustfield);
	cout.width(10);
	cout << "Ganga" << "\n";
	cout.precision(3);
	cout.setf(ios::internal, ios::adjustfield);
	cout.setf(ios::scientific, ios::floatfield);
	cout.width(15);
	cout << -99.12345 << "\n";
}