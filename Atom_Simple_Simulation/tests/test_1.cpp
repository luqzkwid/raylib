#include <iostream>
#include <map>
#include <vector>
#define MAX_LAYERS 7

using namespace std;

map<string, vector<int>>
diagnostic_layers(map<int, int> layers, int electrons) {
    map<string, vector<int>>lmap;
    lmap["completed_layers"];
    lmap["incompleted_layers"];
    for(auto& [level, max_electrons] : layers){
        if(electrons - max_electrons >= 0){
            // Here we have a completed layer!
            electrons -= max_electrons;
            lmap["completed_layers"].push_back(level);
        } else {
            lmap["incompleted_layers"].push_back(level);
            break;
        }
    }
    return lmap;
}
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
    int electrons = 100;
    map<int, int> m{{1, 2},{2, 8},{3, 18},{4, 32},{5, 32},{6, 18},{7, 8}};
    print_map(m,electrons);
    return 0;
}
