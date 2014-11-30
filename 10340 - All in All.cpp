#include <iostream>
#include <cstdio>

using namespace std;

int main() {
//    freopen("10340 - All in All.in", "r", stdin);
    string a, b;
    while(cin >> a >> b) {
        int n = a.length(), m = b.length(), p = 0;
        for(int i = 0; i < m && p < n; i++)
            if(b[i] == a[p])
                p++;
        cout << (p == n ? "Yes" : "No") << endl;
    }
}
