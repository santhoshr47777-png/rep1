#include <iostream>
using namespace std;
int main(){
    int large=0;
    array list [5]={1,2,3,4,5};
    for(int i=0;i<5;i++){
        if(list[i]>large){
            large=list[i];
        }
    }
    cout<<large;
    return 0;
}