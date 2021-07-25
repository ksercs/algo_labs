#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

void theQuickBrownFox (vector<int> &arr, int n){
    for (int i = 0; i < n; i++)
        swap(arr[i], arr[i / 2]);
}

int main() {
    int n = 0;
    ifstream cin ("antiqs.in");
    ofstream cout ("antiqs.out");
    cin >> n;
    vector<int> arr;
    arr.resize(n);
    for (int i = 0; i < n; i++)
        arr[i] = i + 1;
    theQuickBrownFox(arr, n);
    for (int i = 0; i < n; i++)
        cout << arr[i];
    return 0;
}
