//6350 TV Reports

#include <iostream>
#include <cstdio>

using namespace std;

int main() {
//    freopen("6350 TV Reports.in", "r", stdin);
    int n, p, h, x;
    while(cin >> n >> p >> h) {
        for(int i = 0; i < n; i++) {
            cin >> x;
            if(x < p) {
                cout << "NTV: Dollar dropped by " << (p-x) << " Oshloobs" << endl;
            } else if(x > h) {
                cout << "BBTV: Dollar reached " << x << " Oshloobs, A record!" << endl;
            }
            p = x;
            h = max(h, p);
        }
    }
}

