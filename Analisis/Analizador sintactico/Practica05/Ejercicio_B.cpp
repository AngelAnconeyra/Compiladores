/*
Input: 52 13 +
Ouput: 65
*/
#include<iostream>
#include<string>
#include<stack>

using namespace std;

int main(){
    stack<int> Pila;
    char c;
    string num;
    c = getchar();
    while(c != '\n'){
        if(isdigit(c)){
            num+= c;
        }
        else if(c == '+'){
            int a = Pila.top();
            Pila.pop();
            int b = Pila.top();
            Pila.pop();
            Pila.push(a+b);
        }
        else if(c == '-'){
            int a = Pila.top();
            Pila.pop();
            int b = Pila.top();
            Pila.pop();
            Pila.push(b-a);
        }
        else if(c == ' '){
            Pila.push(stoi(num));
            num.erase();
        }
        c = getchar();
    }
    cout<< Pila.top();


    return 0;
}
