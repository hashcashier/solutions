//6190 - Beautiful Spacing
#include <iostream>
#include <cstring>
#include <cstdio>

#define MAXN 60000

int q[MAXN];
long long g[MAXN];
int N, W, L, J, JJ;
bool f[MAXN];

using namespace std;

bool F(int i) {
    if(g[N] - g[i] + (N-i-1) <= W || q[i] == W) f[i] = true;
    else if(g[JJ-1] - g[i] + (JJ-i-2) <= W && g[JJ-1] - g[i] + L*(JJ-i-2) >= W) f[i] = true;
    else return false;

//    else
    {
        int lo = i + 2, hi = N-1, res = i + 1;
        while(lo <= hi) {
            int mid = (lo+hi)/2;
            long long sum = g[mid+1] - g[i], num = mid-i;
            if(sum + num <= W && sum + num*L >= W) {
                res = max(res, mid);
                lo = mid + 1;
            } else {
                hi = mid - 1;
            }
        }

        if(res == i+1) {
            long long sum = g[res+1] - g[i];
            f[i] = sum + 1 <= W && sum + L >= W;
        } else
            f[i] = J <= res+1;
    }
}

int main() {
    freopen("6190 - Beautiful Spacing.in", "r", stdin);
    while(scanf("%d %d", &W, &N) != EOF && W && N) {
        for(int i = 0; i < N; i++)
            scanf("%d", &q[i]);

        g[0] = 0;
        for(int i = 1; i <= N; i++)
            g[i] = q[i-1] + g[i-1];

        int lo = 1, hi = W, res = W;
        while(lo <= hi) {
            J = N-1;
            JJ = N;
            L = (lo+hi)/2;
            for(int i = N; i >= 0; i--) {
                F(i);
                if(f[i])
                    JJ = J, J = i;
            }
            if(f[0])
                res = min(res, L),
                hi = L - 1;
            else
                lo = L + 1;
        }
        printf("%d\n", res);
    }
}
