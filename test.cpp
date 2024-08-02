#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int main(){
    vector<int> scores{0,1,5,3,4,5,6};
    int point;
    point = distance(scores.begin(),find(scores.begin(),scores.end(),5));
    cout << point;
    return 0;
}
