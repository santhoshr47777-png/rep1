#include <iostream>
#include <bits/stdc++.h>

using namespace std;
void rupp_to_doll()
{
    cout<<"Enter the amount of rupees:";
    int rupp;
    cin>>rupp;
    cout<<"The amount of dollers is:"<<rupp*0.012<<endl;
};

void doll_to_rupp()
{
    cout<<"Enter the value of dollers:";
    int doll;
    cin>>doll;
    cout<<"The amount of ruppes is:"<<doll*86.36<<endl;
};
int main() 
{
    int x=1;
    cout<<"                           MONEY CONVERTION "<<endl;
    cout<<"1.Rupees to Doller"<<endl;
    cout<<"2.Doller to Rupees"<<endl;
    cout<<"0.Quit"<<endl;
    while (x<1000)
    {
        int choice;
        cout<<"Enter your choice :";
        cin>>choice;
        if (choice==1)
            rupp_to_doll();
        else if (choice==2)
            doll_to_rupp();
        else if (choice==0)
            break;
        else
            cout<<"Invalid Input"<<endl;
        x++;
    };
    
    return 0;
}