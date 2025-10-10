#include <iostream>
#include <string>
#include <vector>
using namespace std;
class student{
    public:
        int roll_no;
        string name;
        string mobile_no;
        string mail_add;
        call(){
            cout<<"hello"<<endl;
        }
};

int main() {
    student santhosh;
    santhosh.roll_no=10;
    santhosh.name=="SANTHOSH R"<<endl;
    santhosh.mobile_no=="6382478738"<<endl;
    santhosh.mail_add=="santhoshr47777@gmail.com"<<endl;
    cout<<santhosh.name;
    cout<<santhosh.mobile_no;
    cout<<santhosh.mail_add;

    student s12;
    s12.name="asas0";
    cout<<s12.name;

    return 0;
};