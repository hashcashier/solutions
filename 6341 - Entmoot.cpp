//6341 - Entmoot
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <complex>

#define EPS 1e-7

using namespace std;
int N, x[50], y[50], s[50];

long double maxDist(long double X, long double Y) {
    long double res = 0;
    for(int i = 0; i < N; i++) {
        long double dx = X - x[i], dy = Y - y[i];
        res = max(res, sqrt(dx*dx + dy*dy)/s[i]);
    }
    return res;
}

long double minY(long double X) {
    long double lo = -1e6, hi = 1e6, res = 3e6;
    while(fabs(lo-hi) > EPS) {
        long double left = (hi-lo)/3 + lo, right = (2*(hi-lo))/3 + lo;
        long double resL = maxDist(X, left), resR = maxDist(X, right);
        if(resL < resR)
            hi = right;
        else
            lo = left;
        res = min(res, min(resL, resR));
    }
    return res;
}

long double minX() {
    long double lo = -1e6, hi = 1e6, res = 3e6;
    while(fabs(lo-hi) > EPS) {
        long double left = (hi-lo)/3 + lo, right = (2*(hi-lo))/3 + lo;
        long double resL = minY(left), resR = minY(right);
        if(resL < resR)
            hi = right;
        else
            lo = left;
        res = min(res, min(resL, resR));
    }
    return res;
}

int main() {
//    freopen("6341 - Entmoot.in", "r", stdin);
    int T;
    cin >> T;
    while(T--) {
        cin >> N;
        for(int i = 0; i < N; i++)
            cin >> x[i] >> y[i] >> s[i];
        cout << setprecision(6) << fixed << minX() << endl;
    }
    return 0;
}
