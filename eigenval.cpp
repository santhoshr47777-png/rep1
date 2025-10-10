#include <iostream>
#include <windows.h>

using namespace std;

void input_matrix(int &a11, int &a12, int &a13,
                  int &a21, int &a22, int &a23,
                  int &a31, int &a32, int &a33) 
{
    SetConsoleOutputCP(CP_UTF8);
    cout << "Lambda symbol: \u03BB" << endl;
    cout << "Enter the value A11 : "; cin >> a11;
    cout << "Enter the value A12 : "; cin >> a12;
    cout << "Enter the value A13 : "; cin >> a13;
    cout << "Enter the value A21 : "; cin >> a21;
    cout << "Enter the value A22 : "; cin >> a22;
    cout << "Enter the value A23 : "; cin >> a23;
    cout << "Enter the value A31 : "; cin >> a31;
    cout << "Enter the value A32 : "; cin >> a32;
    cout << "Enter the value A33 : "; cin >> a33;
    cout << endl;
}

void eigval(int c11, int c12, int c13,
            int c21, int c22, int c23,
            int c31, int c32, int c33) 
{
    int s1,s2,s3;
    s1 = c11 + c22 + c33;
    s2 = ((c11*c22) - (c12*c21)) + ((c22*c33) - (c23*c32)) + ((c11*c33) - (c13*c31));
    s3 = c11*((c22*c33) - (c23*c32)) - c12*((c21*c33) - (c23*c31)) + c13*((c21*c32) - (c22*c31));
    
    cout << "Value of s1 = " << s1 << endl;
    cout << "Value of s2 = " << s2 << endl;
    cout << "Value of s3 = " << s3 << endl; 
    cout << "Characteristic polynomial: ";
    cout << "\u03BB³ - (" << s1 << ")\u03BB² + (" << s2 << ")\u03BB - (" << s3 << ") = 0" << endl;
    
}

int main() {
    int a11, a12, a13, a21, a22, a23, a31, a32, a33;
    
    input_matrix(a11, a12, a13, a21, a22, a23, a31, a32, a33);
    eigval(a11, a12, a13, a21, a22, a23, a31, a32, a33);

    return 0;
}
