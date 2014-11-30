//ASC35C
#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

long long cd(long long a, long long b) {
    return (a/b) + ((a%b) > 0);
}

int main() {
    freopen("budget.in", "r", stdin);
//    freopen("budget.out", "w", stdout);
    long long n, m, p, x;
    cin >> m >> n >> p;

    long long g[n][2];
    for(int i = 0; i < m; i++)
        cin >> g[i][0], g[i][1] = 0;

    long long f[n];
    for(int i = 0; i < n; i++)
        cin >> f[i];
    sort(f, f+n);

    long long day = 1;
    for(int i = 0; i < n; i++) {
        long long tj = 0, tend = max(g[0][1], f[i]) + cd(p, g[0][0]);
        for(int j = 0; j < m; j++) {
            int temp = max(g[j][1], f[i]) + cd(p, g[j][0]);
            cout << i << ' ' << j << ' ' << temp << endl;
            if(temp < tend) {
                tj = j;
                tend = temp;
            } else if(temp == tend && g[j][0] < g[tj][0]) { // ********* clarification needed
                tj = j;
            }
        }
        g[tj][1] = tend;
        day = max(day, tend-1);
    }

    cout << day << endl;
    return 0;
}
