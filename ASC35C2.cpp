//ASC35C
#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

typedef long long LL;
typedef pair<LL, LL> ii;

LL m, n, p, s[100], r[100], av[100];

LL calc(LL power) {
    return (p/power) + (p%power > 0);
}

bool F(LL endTime) {
    for(int i = 0; i < m; i++)
        av[i] = endTime+1;

    for(int i = n-1; i >= 0; i--) {
        LL assgn = -1;
        for(int j = 0; j < m; j++)
            if(av[j] - calc(s[j]) >= r[i] && (assgn == -1 || s[j] < s[assgn]))
                assgn = j;

        if(assgn == -1) return false;
        av[assgn] -= calc(s[assgn]);
    }
    return true;
}

int main() {
    freopen("budget.in", "r", stdin);
    freopen("budget.out", "w", stdout);
    cin >> m >> n >> p;
    for(int i = 0; i < m; i++)
        cin >> s[i];
    for(int i = 0; i < n; i++)
        cin >> r[i];
    sort(r, r+n);

    LL lo = 1, hi = 2e12 + 11LL, sol = 0;
    while(lo <= hi) {
        LL mid = (hi+lo)/2;
        if(F(mid))  sol = mid, hi = mid-1;
        else        lo = mid+1;
    }
    cout << sol << endl;
    return 0;
}
