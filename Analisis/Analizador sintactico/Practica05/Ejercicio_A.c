/*
Expre -> Term Resto
Expre -> (Expre) Resto
Resto ->
Resto -> ;
Resto -> +|-|*  Term print{+|-|*}
Resto -> +|-|*  Term print{+|-|*} Resto
Resto -> +|-|*  (Expre) print{+|-|*}
Term -> prit{num} num
*/
#include<iostream>
#include<fstream>
#include<string>
#include<stack>
#define MAS '+'
#define MENOS '-'
#define MULTI '*'
#define NUM 256
#define PAREN 257
#define FIN -1
using namespace std;

stack<int> Pila;
string texto;
string posfijo;
char lexema[80];
int tok;
void Resto();
void Term();
void error();
void parea(int);
int scanner();
int cont;

void Posfijo(){
    stack<int> Pila;
    string num;
    for(int i = 0; i< posfijo.size();i++){
        if(isdigit(posfijo[i])){
            num+= posfijo[i];
        }
        else if(posfijo[i] == '+'){
            int a = Pila.top();
            Pila.pop();
            int b = Pila.top();
            Pila.pop();
            Pila.push(a+b);
        }
        else if(posfijo[i] == '-'){
            int a = Pila.top();
            Pila.pop();
            int b = Pila.top();
            Pila.pop();
            Pila.push(b-a);
        }
        else if(posfijo[i] == '*'){
            int a = Pila.top();
            Pila.pop();
            int b = Pila.top();
            Pila.pop();
            Pila.push(b*a);
        }
        else if(posfijo[i] == ' ' && num.size() != 0){
            Pila.push(stoi(num));
            num.erase();
        }
    }
    cout<< Pila.top();
}

void Exp(){
    if (tok==NUM){ 
        Term();
        Resto(); 
    }
    else if(tok==PAREN){
        parea(PAREN);
        Exp(); 
        parea(PAREN);
        Resto();
    }
    else{
        error();
    }
}

void Resto(){
    if (tok == MAS){ 
        parea(MAS);
        if(tok==NUM){
            Term();
            posfijo += '+';
            if(tok==PAREN){
                return;
            }
            else if(tok==FIN){
                Resto();
            }
        }
        else if(tok==PAREN){
            parea(PAREN);
            Exp();
            parea(PAREN);
            posfijo += '+';
        }
    }
    else if (tok == MENOS){
        parea(MENOS);
        if(tok==NUM){
            Term();
            posfijo += '-';
            if(tok==PAREN){
                return;
            }
            else if(tok==FIN){
                Resto();
            }
        }
        else if(tok==PAREN){
            parea(PAREN);
            Exp(); 
            parea(PAREN);
            posfijo += '-';
        }
    }
    else if (tok == MULTI){ 
        parea(MULTI);
        if(tok==NUM){
            Term();
            posfijo += '*';
            if(tok==PAREN){
                return;
            }
            else if(tok==FIN){
                Resto();
            }
        }
        else if(tok==PAREN){
            parea(PAREN);
            Exp();
            parea(PAREN);
            posfijo += '*';
        }
    }
    else if(tok == FIN){
        return;
    } //cadena vacia
    else{
        error();
    }
}

void Term(){
    if (tok==NUM){ 
        posfijo += " ";
        posfijo +=lexema;
        posfijo += " ";
        parea(NUM); 
    }
    else{
        error();
    }
}

void error(){
    printf("Error de sintaxis");
}

void parea(int t){
    if (tok==t){
        tok=scanner();
    }
    else{
        error();
    }
}

int scanner(){
    int c,i;
    do{
        cont++;
        c=texto[cont];
    }while(c==' ');
    if (c=='\n' || c==';'){
        return FIN;
    }
    if (c == '(' || c == ')'){
        return PAREN;
    }
    if (c==MAS || c==MENOS || c==MULTI){
        return c;
    }
    if(isdigit(c)){
        i=0;
        do { 
            lexema[i++]=c; 
            cont++;
            c=texto[cont]; 
        }while(isdigit(c));
        lexema[i]=0;
        cont--;
        return NUM;
    }
    return 0;
}

int main(){
    ifstream Archivo("Programa1.txt");
    while (getline(Archivo, texto)){
        cont = -1;
        tok = scanner();
        Exp();
        cout<<posfijo<<" = ";
        Posfijo();
        cout<<endl;
        texto.erase();
        posfijo.erase();
    }
    Archivo.close();
}
