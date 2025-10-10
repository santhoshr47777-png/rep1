#include <iostream>
using namespace std;
int main(){
    int a,b,q,r;
    cout<<"Enter two values";
    cin>>a>>b;
    r=a%b;
    q=a/b;
    cout<<"Quotient :"<<q<<endl;
    cout<<"Reminder :"<<r;
    return 0;
}