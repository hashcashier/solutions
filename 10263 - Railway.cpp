//10263 - Railway
#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

int main() {
    double xm, xy;
    int N;
    while(cin >> xm >> xy >> N) {
        double xa, xb, ya, yb, xr, yr;
        cin >> xa >> ya;
        for(int i = 0; i < N; i++) {
            cin >> xb >> yb;

            double Ax = xb-xa, Ay = yb - ya, A = Ax*Ax + Ay*Ay;
            double Bx =

            xa = xb;
            ya = yb;
        }

        cout << setprecision(4) << fixed << xr << endl << yr << endl;
    }
}
