//6341 Entmoot
#include <iostream>
#include <cstdio>
#include <set>

#define EPS 1e-6

using namespace std;

typedef pair<int, int> ii;

long long sqr(long long a) {
    return a*a;
}

long double sqr(long double a) {
    return a*a;
}

int main() {
    int T;
    cin >> T;
    while(T--) {
        int N;
        cin >> N;

        long long ents[N][3];
        for(int i = 0; i < N; i++)
            cin >> ents[i][0] >> ents[i][1] >> ents[i][2];

        long double lo = 0, hi = 1e7;
        while(hi-lo > EPS) {
            long double mid = (hi+lo)/2;

            bool ok = sqr(ents[0][0]-ents[1][0]) + sqr(ents[0][1]-ents[1][1]) <= sqr((ents[0][2] + ents[1][2])*mid);
            if(ok) {
                // do stuff
            }


            if(ok) hi = mid;
            else   lo = mid;
        }

        cout << lo << endl;
    }


    return 0;
}
