//4377 - Giant Screen
#include <iostream>
#include <cstdio>
#include <cmath>
#include <climits>

using namespace std;

int main() {
//    freopen("4377 - Giant Screen.in", "r", stdin);
    int rx, ry, dx, dy,n ;
    while(cin >> rx >> ry >> dx >> dy) {
        cin >> n;
        double rex, rey, dex, dey;
        long long res = LONG_LONG_MAX, price;
        for(int i = 0; i < n; i++) {
            cin >> rex >> rey >> dex >> dey >> price;
            long long x = max(ceil(rx/rex), ceil(dx/dex)), y = max(ceil(ry/rey), ceil(dy/dey));
//            cout << x << ' ' << y << endl;
            res = min(res, x*y*price);

            long long xx = max(ceil(rx/rey), ceil(dx/dey)), yy = max(ceil(ry/rex), ceil(dy/dex));
            res = min(res, xx*yy*price);
        }
        cout << res << endl;
    }
}
