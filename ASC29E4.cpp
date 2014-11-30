//ASC29E
#include <iostream>
#include <cstdio>
#include <set>

using namespace std;

int main() {
    cin >> n;
    long long res = 0;
    for(int B = 0; B < n; B++)
        for(int T = B+1; T < n; T++)
            res += F(0, T, B, 1, 1);
    cout << res << endl;
    return 0;
}
