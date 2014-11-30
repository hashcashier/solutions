//Closest pair problem - plane sweep
#include <iostream>
#include <algorithm>
#include <set>
#include <cmath>

using namespace std;
double *x, *y;
struct cmpx {
    bool operator() (const int a, const int b) const {
        return x[a] < x[b] || (a != b && y[a] < y[b]);
    }
};

struct cmpy {
    bool operator() (const int a, const int b) const {
        return y[a] < y[b] || (a != b && x[a] < x[b]);
    }
};

double distsq(int a, int b) {
    return (x[a]-x[b])*(x[a]-x[b]) + (y[a]-y[b])*(y[a]-y[b]);
}

int main() {
    int N;
    cin >> N;
    if(N <= 1)
        return 0;

    x = new double[N], y = new double[N];
    for(int i = 0; i < N; i++)
        cin >> x[i] >> y[i];
    set<int, cmpx> xset, sweep;
    set<int, cmpy> yset;
    for(int i = 0; i < N; i++)
        sweep.insert(i);

    double d = distsq(0, 1);
    set<int, cmpx>::iterator it, it2, it3;
    for(it = sweep.begin(); it != sweep.end(); it++) {
        it2 = xset.insert(*it).first;

        if(xset.size() < 2) continue;

        for(it3 = xset.begin(); it3 != it2; it3++)
            if(distsq(*it3, *it2) > d)
                yset.erase(*it3), xset.erase(it3), it3 = xset.begin();
            else
                break;

        it3 = it2 = yset.insert(*it).first;
        while(++it3 != yset.end()) {
            if(y[*it3] - y[*it2] > d)
                break;
            else
                d = min(d, distsq(*it3, *it2));
        }

        it3 = it2;
        while(it3-- != yset.begin()) {
            if(y[*it2] - y[*it3] > d)
                break;
            else
                d = min(d, distsq(*it3, *it2));
        }
    }

    cout << sqrt(d) << endl;

    return 0;
}
