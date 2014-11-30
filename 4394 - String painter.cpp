//4394 - String painter
#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>

using namespace std;
string A, B;
bool vis[110][110][31];
int chars[110][31];
int dp[110][110][31], N;

int DP(int idx, int n, int L) {
    if(n == 0)
        return 0;

    if(vis[idx][n][L])
        return dp[idx][n][L];

    vis[idx][n][L] = true;
    if(n == 1)
        return dp[idx][n][L] = (L == 30 ? A[idx] != B[idx] : char('a'+L) != B[idx]);

    int res = 100;
    for(int i = 0; i < 31; i++) {
        if(chars[idx][i] == -1 || chars[idx][i] > n)
            continue;

        int add = (i < 30), subres = DP(idx, 1, i) + DP(idx+1, n-1, i);
        for(int j = 2; j < n; j++)
            subres = min(subres, DP(idx, j, i) + DP(idx+j, n-j, i));

        res = min(res, add + subres);
    }

    return dp[idx][n][L] = res;
}

int main() {
    freopen("4394 - String painter.in", "r", stdin);
    int cse = 0;
    while(cin >> A >> B) {
        if(!A.length() || !B.length())
            return -1;

        memset(vis, false, sizeof vis);
        memset(chars, -1, sizeof chars);
        N = A.length();

        for(int i = 0; i < N; i++) {
            for(int j = i; j < N; j++) {
                int idx = B[j]-'a';
                if(chars[i][idx] == -1)
                    chars[i][idx] = j-i+1;
            }
            chars[i][30] = 0;
        }

        if(cse++) cout << endl;
        cout << DP(0, N, 30);
//        break;
    }
    return 0;
}
