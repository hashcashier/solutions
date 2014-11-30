//11709 - Trust groups
#include <iostream>
#include <cstdio>
#include <vector>
#include <map>

using namespace std;

class graph {
    public:
    vector< vector<int> > adjList;
    int N, dfs_ctr, dfs_scc;
    vector<int> dfs_num, dfs_low, stk, vis;


    graph(int n) {
        N = n;
        adjList.assign(N, vector<int>());
    }

    void connect(int a, int b) {
        adjList[a].push_back(b);
    }

    void dfs(int u) {
        dfs_low[u] = dfs_num[u] = dfs_ctr++;
        stk.push_back(u);
        vis[u] = 1;
        for(int i = 0; i < adjList[u].size(); i++) {
            int v = adjList[u][i];
            if(!dfs_num[v])
                dfs(v);
            if(vis[v])
                dfs_low[u] = min(dfs_low[u], dfs_low[v]);
        }
        if(dfs_low[u] == dfs_num[u]) {
            dfs_scc++;
            while(true) {
                int v = stk.back(); stk.pop_back(); vis[v] = 0;
                if(u == v) break;
            }
        }
    }

    int SCCNUM() {
        dfs_ctr = 1;
        dfs_scc = 0;
        dfs_num.assign(N, 0);
        dfs_low.assign(N, 0);
        vis.assign(N, 0);
        for(int i = 0; i < N; i++)
            if(!dfs_num[i])
                dfs(i);
        return dfs_scc;
    }
};

int main() {
//    freopen("11709 - Trust groups.in", "r", stdin);
    int P, T;
    while(cin >> P >> T && (P || T)) {
        map<string, int> trans;
        graph G(P);
        for(int i = 0; i < P; i++) {
            string a,b,c;
            cin >> a >> b;
            c = a + b;
            trans[c] = i;
        }
        for(int i = 0; i < T; i++) {
            string a,b,c,d;
            cin >> a >> b;
            c = a + b;
            cin >> a >> b;
            d = a + b;
            G.connect(trans[c], trans[d]);
        }
        cout << G.SCCNUM() << endl;
    }
    return 0;
}
