#include <iostream>
#include <iomanip> 
#include <windows.h>
using namespace std;

// Define global variables for first matrix
int a11, a12, a13, a21, a22, a23, a31, a32, a33;

// Define global variables for second matrix
int b11, b12, b13, b21, b22, b23, b31, b32, b33;

int matrix_3x3_1()
{
    cout << "Enter the value A11 : "; cin >> a11;
    cout << "Enter the value A12 : "; cin >> a12;
    cout << "Enter the value A13 : "; cin >> a13;
    cout << "Enter the value A21 : "; cin >> a21;
    cout << "Enter the value A22 : "; cin >> a22;
    cout << "Enter the value A23 : "; cin >> a23;
    cout << "Enter the value A31 : "; cin >> a31;
    cout << "Enter the value A32 : "; cin >> a32;
    cout << "Enter the value A33 : "; cin >> a33;
    cout <<endl;
    return 0;
}

int matrix_3x3_2()
{
    cout << "Enter the value B11 : "; cin >> b11;
    cout << "Enter the value B12 : "; cin >> b12;
    cout << "Enter the value B13 : "; cin >> b13;
    cout << "Enter the value B21 : "; cin >> b21;
    cout << "Enter the value B22 : "; cin >> b22;
    cout << "Enter the value B23 : "; cin >> b23;
    cout << "Enter the value B31 : "; cin >> b31;
    cout << "Enter the value B32 : "; cin >> b32;
    cout << "Enter the value B33 : "; cin >> b33;
    return 0;
}
void drawMatrix(const string& title, int m11, int m12, int m13,
                                int m21, int m22, int m23,
                                int m31, int m32, int m33) {
    cout << title << ":\n";
    cout << "+------+------+------+\n";
    cout << "| " << setw(4) << m11 << " | " << setw(4) << m12 << " | " << setw(4) << m13 << " |\n";
    cout << "+------+------+------+\n";
    cout << "| " << setw(4) << m21 << " | " << setw(4) << m22 << " | " << setw(4) << m23 << " |\n";
    cout << "+------+------+------+\n";
    cout << "| " << setw(4) << m31 << " | " << setw(4) << m32 << " | " << setw(4) << m33 << " |\n";
    cout << "+------+------+------+\n";
}

int add_Matrix()
{
    drawMatrix("Sum Of Matrix A&B",a11+b11,a12+b12,a13+b13,a21+b21,a22+b22,a23+b23,a31+b31,a32+b32,a33+b33);
    return 0;
}
int sub_Matrix()
{
    drawMatrix("Difference Of Matrix A&B",a11-b11,a12-b12,a13-b13,a21-b21,a22-b22,a23-b23,a31-b31,a32-b32,a33-b33);
    return 0;
}
int scalar_mult()
{
    int sca_num ;
    cout<<"Enter the scalar number :";
    cin>>sca_num;
    drawMatrix("Product Of Matrix A",a11*sca_num,a12*sca_num,a13*sca_num,a21*sca_num,a22*sca_num,a23*sca_num,a31*sca_num,a32*sca_num,a33*sca_num);
    return 0;
}
void multiply_matrix() {
    int c11 = a11*b11 + a12*b21 + a13*b31;
    int c12 = a11*b12 + a12*b22 + a13*b32;
    int c13 = a11*b13 + a12*b23 + a13*b33;

    int c21 = a21*b11 + a22*b21 + a23*b31;
    int c22 = a21*b12 + a22*b22 + a23*b32;
    int c23 = a21*b13 + a22*b23 + a23*b33;

    int c31 = a31*b11 + a32*b21 + a33*b31;
    int c32 = a31*b12 + a32*b22 + a33*b32;
    int c33 = a31*b13 + a32*b23 + a33*b33;

    drawMatrix("Product of Matrix A × B", c11, c12, c13, c21, c22, c23, c31, c32, c33);
}

int transpose_matrix(int a11, int a12, int a13,
                     int a21, int a22, int a23,
                     int a31, int a32, int a33)
{
    drawMatrix("Transpose Of Matrix A",a11,a21,a31,a12,a22,a32,a13,a23,a33);
}
int if_identity_matrix(int c11, int c12, int c13,
                       int c21, int c22, int c23,
                       int c31, int c32, int c33)
{
    if (c11 == 1 && c22 == 1 && c33 == 1 &&
        c12 == 0 && c13 == 0 &&
        c21 == 0 && c23 == 0 &&
        c31 == 0 && c32 == 0)
    {
        SetConsoleOutputCP(CP_UTF8);
        cout << "👍The matrix is an Identity Matrix" << endl;
    }
    else
    {
        SetConsoleOutputCP(CP_UTF8);
        cout << "❌The matrix is NOT an Identity Matrix" << endl;
    }
    return 0;
}

int if_diagonal_matrix(int c11, int c12, int c13,
                       int c21, int c22, int c23,
                       int c31, int c32, int c33)
{
    if(c11 == 0 && c22 == 0 && c33 == 0 )
        {SetConsoleOutputCP(CP_UTF8);
        cout<<"👍The matrix is a Diagonal Matrix";
        }
    else
        SetConsoleOutputCP(CP_UTF8);
        cout<<"❌The matrix is NOT a Diagonal Matrix";

}
int check_symmetric_matrix(int c11, int c12, int c13,
                       int c21, int c22, int c23,
                       int c31, int c32, int c33)
{
    if (a12 == a21 && a13 == a31 && a23 == a32) {
        SetConsoleOutputCP(CP_UTF8);
        cout << "👍Matrix A is symmetric." << endl;
    } else {
        SetConsoleOutputCP(CP_UTF8);
        cout << "❌Matrix A is NOT symmetric." << endl;
    }
    return 0;
}
int modulus_a(int c11, int c12, int c13,
                       int c21, int c22, int c23,
                       int c31, int c32, int c33)
{
    int mod;
    mod=c11*((c22*c33)-(c23*c32))-c12*((c21*c33)-(c23*c31))+c13*((c21*c32)-(c22*c31));
    cout<<"The Modulus of the Matrix A = "<<mod<<endl;

}


int main() {
    cout<<"                                               Welcome to Matrix Calculator "<<endl;
    cout<<endl;
    SetConsoleOutputCP(CP_UTF8);
    matrix_3x3_1();
    matrix_3x3_2();
    cout<<endl;
    bool run = true;

    while (run)
    {
        cout<<endl;
        cout<<"1.Fill the Matrix A again"<<endl;
        cout<<"2.Fill the Matrix B again "<<endl;
        cout<<"3.Display Matrix  A"<<endl;
        cout<<"4.Display Matrix  B"<<endl;
        cout<<"5.➕Add the Matrix A&B"<<endl;
        cout<<"6.➖Subract the Matrix A&B"<<endl;
        cout<<"7.✖️Scalar Multiplication with a number and Matrix A"<<endl;\
        cout<<"8.✖️Product of two Matrix A&B"<<endl;
        cout<<"9.🔄Transpose of Matrix A"<<endl;
        cout<<"10.Check if it is Identity Matrix"<<endl;
        cout<<"11.Check if it is Diagonal Matrix"<<endl;
        cout<<"12.check if it is symmetric matrix"<<endl;
        cout<<"13.To get the modulus of matrix A"<<endl;
        cout<<endl;
        SetConsoleOutputCP(CP_UTF8);
        cout<<"🚪 PRESS 0 FOR QUIT"<<endl;
        cout<<"Enter your Choice:"<<endl;
        int choice ;
        cin>>choice;
        switch (choice)
        {
            case 1:
                matrix_3x3_1();
                break;
            case 2:
                matrix_3x3_2();
                break;
            case 3:
                drawMatrix("Matrix A", a11, a12, a13, a21, a22, a23, a31, a32, a33);
                break;
            case 4:
                drawMatrix("Matrix B", b11, b12, b13, b21, b22, b23, b31, b32, b33);
                break;
            case 5:
                add_Matrix();
                break;
            case 6:
                sub_Matrix();
                break;
            case 7:
                scalar_mult();
                break;
            case 8:
                multiply_matrix();
                break;
            case 9:
                transpose_matrix(a11, a12, a13, a21, a22, a23, a31, a32, a33);
                break;
            case 10:
                if_identity_matrix(a11, a12, a13, a21, a22, a23, a31, a32, a33);
                break;
            case 11:
                if_diagonal_matrix(a11, a12, a13, a21, a22, a23, a31, a32, a33);
                break;
            case 12:
                check_symmetric_matrix(a11, a12, a13, a21, a22, a23, a31, a32, a33);
                break;
            case 13:
                modulus_a(a11, a12, a13, a21, a22, a23, a31, a32, a33);
                break;
            case 0:
                run=false;
                break;
            default:
                cout<<"Invlaid Choice";
        };
    
    };
    return 0;
}   