#include <iostream>
#include <vector>

using namespace std;

int main()
{

    int name = 1;
    int name1 = 3;
    int *i;
    cout << name << endl;
    vector<vector<int>> names(1);

    names[0].push_back(name);
    names[0].push_back(name1);

    i = names[0].data();

    std::cout << sizeof(i) << endl;

    vector<int>::iterator itr = names[0].begin();
    names[0].erase(itr);
    std::cout << sizeof(i) << endl;
}