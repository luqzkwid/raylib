#include <iostream>

using namespace std;
int
main(void){
    int maximum = 10;
    for(int a=0; a <= 10; a++){
        cout << "Hello, Index:" << a << endl;
        if(a == maximum){
            cout << "A == " << a << endl;
            cout << "A + 1: " << a + 1 << endl;
        }
    }
    return 0;
}
