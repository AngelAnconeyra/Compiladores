#include<iostream>
#include <conio.h>
#include <ctype.h>
using namespace std;

int preanalisis;
void parea(int);
void Term();
void Resto();
void error();
void Signo();

void Num(){
    if(isdigit(preanalisis)){
        parea(preanalisis);
    }
    else{
        error();
    }
}

void Signo(){
    if(preanalisis == '+'){
        parea('+');
    }
    else if(preanalisis == '-'){
        parea('-');
    }
    else{
        error();
    }
}

void Exp(){
    if (isdigit(preanalisis)){ 
        Term();
        Resto();
    }
    else{
        error();
    }
}

void Term(){
    if (isdigit(preanalisis)){
        cout<< char(preanalisis);
        parea(preanalisis);
    }
    else{
        error();
    }
}

void Resto(){
    if (preanalisis == '+'){
        Signo();
        Term();
        cout<< "+";
        Resto();
    }
    else if(preanalisis == '-'){
        Signo();
        Term();
        cout<< "-";
        Resto();
    }
    else if(preanalisis == '\n'){
        return;
    }
    else{
        error();
    }
}

void error(){
    printf("Error de sintaxis");
}

void parea(int t){
    if (preanalisis==t){
        preanalisis=getchar();
    }
    else{
        error();
    }
}

//1+5   1 5 +
//5-3+1  5 3 - 1 +

int main()  {
    cout<< "Entrada: ";
    preanalisis=getchar();
    cout<<"Salida: "; 
    Exp();
}
