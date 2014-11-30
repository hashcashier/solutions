//6745 Traitor
#include <iostream>
#include <cstring>
#include <cstdio>
#include <vector>

using namespace std;

int f[10010][2][2], g[10010][2][2], n, k;
bool top[10010], s[10010];
vector< vector<int> > adjList;

int F(int u, int can, int watched) {
    int &res = f[u][can][watched];
    if(res != -1)
        return res;
    res = 0;
    if(adjList[u].size() == 0)
        return res;

    if((s[u] && !can && watched) || (!s[u] && !can)) {
        for(int i = 0; i < adjList[u].size(); i++) {
            int v = adjList[u][i];
            res += F(v, 1, 0);
        }
    } else if ((s[u] && watched && can) || (!s[u] && can)) {
        res = F(u, 0, 1);
        int tres = 0;
        g[u][can][watched] = -1;
        for(int i = 0; i < adjList[u].size(); i++) {
            int v = adjList[u][i];
            if(s[v] && 1 + F(v, 1, 1) - F(v, 1, 0) > tres)
                tres = max(tres, 1 + F(v, 1, 1) - F(v, 1, 0)),
                g[u][can][watched] = v;
        }
        res += tres;
    } else if(s[u]) {
        if(!watched && can) {
            // cant -> pick one to watch me, watched -> pick one to watch
            int resa = F(u, 1, 1), resb = F(u, 0, 0);
            int tresa = 0, tresb = 0;
            for(int i = 0; i < adjList[u].size(); i++) {
                int v = adjList[u][i];
                if(v != g[u][1][1]) // not who i watched
                    tresa = max(tresa, 1 + F(v, 0, 0) - F(v, 1, 0));
                if(v != g[u][0][0] && s[v]) // not who's watching me
                    tresb = max(tresb, 1 + F(v, 1, 1) - F(v, 1, 0));
            }
//            cout << u << ' ' << g[u][1][1] << ' ' << g[u][0][0] << endl;
//            cout << resa << ' ' << resb << endl;
            resa += max(tresa, 0);
            resb += max(tresb, 0);
            res = max(resa, resb);
        } else if(!watched && !can) {
            res = F(u, 0, 1);
            int tres = 0;
            g[u][can][watched] = -1;
            for(int i = 0; i < adjList[u].size(); i++) {
                int v = adjList[u][i];
                if(1 + F(v, 0, 0) - F(v, 1, 0) > tres)
                    tres = max(tres, 1 + F(v, 0, 0) - F(v, 1, 0)),
                    g[u][can][watched] = v;
            }
            res += tres;
        }
    }
//    cout << u << ' ' << can << ' ' << watched << ' ' << res << endl;
    return res;
}

int main() {
//    freopen("6745 Traitor.in", "r", stdin);
    while(cin >> n >> k && (n || k)) {
        memset(f, -1, sizeof f);
        memset(top, false, sizeof top);
        adjList = vector< vector<int> >(n, vector<int>());
        for(int i = 0; i < n; i++) {
            int x;
            cin >> x;
            if(x == 0) {
                top[i] = true;
                continue;
            }
            x--;
            adjList[x].push_back(i);
        }
        memset(s, false, sizeof s);
        for(int i = 0; i < k; i++) {
            int x;
            cin >> x;
            x--;
            s[x] = true;
        }
        int res = 0;
        for(int i = 0; i < n; i++)
            if(top[i])
                res += F(i, 1, 0);
        cout << res << endl;
    }

}
