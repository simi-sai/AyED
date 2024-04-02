
//Fibonacci

#include <iostream>
#include <sstream>
using namespace std;

int fib(int n) {
    if (n < 3) {
        return 1;
    } else {
        return fib(n-1)+fib(n-2);
    }
}

int fAux(int n, int p, int a1, int a2){
    if (n == p){
        return a1 + a2;
    } else {
        return fAux(n,p+1,a1+a2,a1);
    }
}

int fibSimple(int n){
    if (n < 3) {
        return 1;
    } else {
        fAux(n,3,1,1);
    }
}


int main()
{
    int a;
    cout << "Entre factorial: " << endl;
    cin >> a;
    cout << fibSimple(a) << endl;
    cout << fib(a) << endl;

    return 0;
}