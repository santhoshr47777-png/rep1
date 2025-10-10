#include <iostream>
using namespace std;
int main(){
    string sentence;
    int v = 0, c = 0;
    cout << "Enter the sentence: ";
    getline(cin, sentence);
    for (int i = 0; i < sentence.length(); i++) {
        if (sentence[i] == 'a' || sentence[i] == 'e' || sentence[i] == 'i' || sentence[i] == 'o' || sentence[i] == 'u' ||
            sentence[i] == 'A' || sentence[i] == 'E' || sentence[i] == 'I' || sentence[i] == 'O' || sentence[i] == 'U') {
            v++;
        }
        else if (isalpha(sentence[i])) {
            c++;
        }
    }
    cout<<"vowels :"<<v<<endl; 
    cout<<"consonants :"<<c;
    return 0;
}