//1482 - Playing With Stones
#include <iostream>
#include <cstdio>

using namespace std;

int main() {
//    freopen("1482 - Playing With Stones.in", "r", stdin);
    int T;
    cin >> T;
    while(T--) {
        unsigned long long N, M, X = 0;
        cin >> N;

        for(int i = 0; i < N; i++){
            cin >> M;
            while(M&1)
                M = M/2;
            X ^= M;
        }

        cout << (X > 0 ? "YES" : "NO") << endl;
    }
    return 0;
}
