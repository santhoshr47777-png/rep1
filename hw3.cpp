#include <iostream>
using namespace std;
int main(){
    int a,b,temp;
    a=10;
    b=20;
    cout<<"Before swapping"<<endl;
    cout<<"a = "<<a<<endl;
    cout<<"b = "<<b<<endl; 
    temp=a;
    a=b;
    b=temp;
    cout<<"After swapping"<<endl;
    cout<<"a = "<<a<<endl;
    cout<<"b = "<<b<<endl;
}