#include <iostream>
#include <cmath>
#include <cstdio>
#include <algorithm>

#define EPS 1e-9

using namespace std;

int main() {
    freopen("approach.in", "r", stdin);
    int n, cse = 1;
    while(cin >> n && n) {
        int a[n], b[n], order[n];
        for(int i = 0; i < n; i++) {
            order[i] = i;
            cin >> a[i] >> b[i];
            a[i] *= 60, b[i] = b[i]*60;
        }

        double res = 0;
        do {
            double lo = 0, high = 1440*60, mid;
            while(fabs(high-lo) > EPS) {
                mid = (lo+high)/2;
                bool possible = true;
                double curtime = 0;

                for(int i = 0; i < n; i++)
                    if(curtime > b[ order[i] ])
                        possible = false;
                    else
                        curtime = max(curtime, 1.0*a[ order[i] ]) + mid;

                if(possible)
                    res = max(res, mid), lo = mid;
                else
                    high = mid;

            }
        } while(next_permutation(order, order+n));

        int rnd = res;
        if(fabs(res-rnd > 0.5))
            rnd++;
        int mins = rnd/60, secs = rnd%60;
        cout << "Case " << cse++ << ": " << mins << (secs < 10 ? ":0" : ":") << secs << endl;
    }
}
