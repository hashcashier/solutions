//ASC28I
#include <iostream>
#include <cstdio>
#include <vector>
#include <set>
#include <map>
#include <cstring>

using namespace std;

vector<int> dfs_num, dfs_low, dfs_parent, art_vertex;
vector< vector<int> > adj;

int dfsCtr, root, rootC, V, E;

void artBridge(int u) {
    dfs_low[u] = dfs_num[u] = dfsCtr++;
    for(int i = 0; i < (int) adj[u].size(); i++) {
        int v = adj[u][i];
        if(!dfs_num[v]) {
			dfs_parent[v] = u;
            if(u == root) rootC++;
            artBridge(v);
            if(dfs_low[v] >= dfs_num[u])
                art_vertex[u] = true;
            dfs_low[u] = min(dfs_low[u], dfs_low[v]);
        } else if(v != dfs_parent[u]) {
            dfs_low[u] = min(dfs_low[u], dfs_num[v]);
        }
    }
}

void init() {
    dfs_num.assign(V, 0);
    dfs_low.assign(V, 0);
    dfs_parent.assign(V, 0);
    art_vertex.assign(V, 0);
    adj.assign(V, vector<int>());
    dfsCtr = 1;
}

void check() {
    for(int i = 0; i < V; i++)
        if(!dfs_num[i]) {
            root = i;
            rootC = 0;
            artBridge(i);
            art_vertex[root] = rootC > 1;
        }
}

bool vis[20100];

int CNT(int u) {
    int res = 0;
    for(int j = 0; j < adj[u].size(); j++) {
        int v = adj[u][j];
        if(!vis[v])
            vis[v] = true, res += CNT(v);
    }
    return 1 + res;
}

int F(int u) {
    int res = 0, tot = 0;
    memset(vis, false, sizeof vis);
    vis[u] = true;
    for(int j = 0; j < adj[u].size(); j++) {
        int v = adj[u][j];
        if(!vis[v]) {
            vis[v] = true;
            int value = CNT(v);
            res += value*(V - value - tot);
            tot += value;
        }
    }
    return res;
}

int main() {
    freopen("travel.in", "r", stdin);
    freopen("travel.out", "w", stdout);
    cin >> V >> E;
    init();

    for(int i = 0; i < E; i++) {
        int a,b;
        cin >> a >> b;
        a--, b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    check();

    for(int u = 0; u < V; u++) {
        if(art_vertex[u]) {
            cout << F(u) << endl;
        } else {
            cout << V-1 << endl;
        }
    }


}
