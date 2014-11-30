//CF255A
#include <iostream>
#include <vector>
#include <set>
#include <cstring>

using namespace std;

int arr[100010], f[100000][2], n;

int F(int i, int j) {
    if(f[i][j] != -1) return f[i][j];
    if(i == n-1)
        return f[i][j] = 1;
    else if(arr[i+1] > arr[i])
        return f[i][j] = 1 + F(i+1, j);
    else if(!j && (i + 2 == n || arr[i+2] - arr[i] > 1))
        return f[i][j] = 1 + F(i+1, 1);
    else if(!j)
        return f[i][j] = 2;
    return f[i][j] = 1;
}

int main() {
    memset(f, -1, sizeof f);
    cin >> n;

    for(int i = 0; i < n ;i++)
        cin >> arr[i];

    int res = 0;
    for(int i = 0; i < n; i++)
        res = max(res, F(i, 0));
    cout << res << endl;

    return 0;
}
