#include <iostream>
#include "bigint.h"
using namespace std;

int main(){
    ACA::BigInt a, b, c(876487);
    cin >> a;
    cin >> b;
    /*cout << a+b << " a+b" << endl;
    cout << a*b <<" a*b " << endl;
    cout << a-b << endl;*/
    cout << (a^b) << " a^b"<< endl;
    //cout << boolalpha << (a>=b) << " : a>=b" << endl;
    //cout << boolalpha << (a<=b) << " : a<=b" << endl;
    return 0;

}