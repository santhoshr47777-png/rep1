#include <iostream>
using namespace std;
int sum(int a,int b){
    int sum=a+b;
    cout<<sum<<endl;
    return 0;
}
int sum(double c,double d){
    int diff=c-d;
    cout<<diff<<endl;
    return 0;
}
int main(){
    sum(2,5);
    sum(5.5,2.2);
    return 0;
}