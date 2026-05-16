#include <vector>
#include <iostream>
using namespace std;
int
main(void){
    vector<int> vec = {0};
    for(int i=1; i <= 10; i++){
        cout << i << " ";
        vec.push_back(i);
    }
    cout << "\n";
    for (vector<int>::iterator it = vec.begin(); it != vec.end();)
    {
        if (*it % 2 == 0)
            it = vec.erase(it);
        else
            ++it;
    }
    for(int j=0; j < vec.size(); j++){
        cout << vec.at(j) << " ";
    }
    return 0;
}
