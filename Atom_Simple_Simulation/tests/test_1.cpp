#include <iostream>
#include <map>
using namespace std;
#define MAX_LAYERS 7
void print_map(map<int, int>m, int electrons){
    cout << "Layers - CapMaxElectrons\n";
    for(auto& [k, v] : m) {
        if(electrons - v > 0){
            electrons -= v;
            cout << k << "  ->  " << v << "  ";
            cout << "		Passou pela camada.  ";
            cout << "		Electrons: " << electrons;
            cout << "		Obtidos: " << v << endl;
        } else {
            cout << k << "  ->  " << v;
            cout << "       Electrons left: " << (electrons - v) * -1;
            cout << "       Could fill: " <<  electrons << " electrons on this layer." << endl;
            break;
        }
    }
}
int
main(void){
    int electrons = 10;
    map<int, int> m{{1, 2},{2, 8},{3, 18},{4, 32},{5, 32},{6, 18},{7, 8}};
    print_map(m,electrons);
    return 0;
}
