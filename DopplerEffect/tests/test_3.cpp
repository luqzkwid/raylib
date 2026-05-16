#include <vector>
#include <iostream>
using namespace std;
void print_vec(vector<int> vec){
    for(int i=0; i < vec.size(); i++){
        cout << vec.at(i) << " ";
    }
    cout << "\n";
}
int
main(void){
    vector<int> vec = {1,2,3,4,5,6};
    print_vec(vec);
    for(auto& it : vec){
        if(it % 2 == 0){
            std::erase(vec, it);
        }
    }
    print_vec(vec);
}
