#include <iostream>
#include <cmath> // Required for sqrt()

using namespace std;

int main() {
    double number;
    cout << "Enter a number: ";
    cin >> number;

    double result = sqrt(number); // Compute square root

    cout << "Square root of " << number << " is " << result << endl;

    return 0;
}
