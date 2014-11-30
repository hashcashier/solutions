//ASC28I
#include <iostream>
#include <cstdio>
#include <vector>
#include <set>
#include <map>
#include <cstring>
#include <queue>

using namespace std;

typedef pair<int, int> ii;
typedef set<int>::iterator s_it;

vector<int> dfs_num, dfs_low, dfs_parent, art_vertex, tart_vertex;
vector< set<int> > adj, adjList, bridgeList;
vector< ii > bridges;
//set<int> bridges[20100];

int dfsCtr, root, rootC, V, E, f[20100];

void artBridge(int u, vector<int> &art_vertex) {
    dfs_low[u] = dfs_num[u] = dfsCtr++;
    for(s_it it = adj[u].begin(); it != adj[u].end(); it++) {
        int v = *it;
        if(!dfs_num[v]) {
            dfs_parent[v] = u;
            if(u == root) rootC++;
            artBridge(v, art_vertex);
            if(dfs_low[v] >= dfs_num[u])
                art_vertex[u] = true;
            if(dfs_low[v] > dfs_num[u])
                bridges.push_back(ii(u, v)), bridgeList[u].insert(v), bridgeList[v].insert(u);

            dfs_low[u] = min(dfs_low[u], dfs_low[v]);
        } else if(v != dfs_parent[u]) {
            dfs_low[u] = min(dfs_low[u], dfs_num[v]);
        }
    }
}
void init(vector<int> &art_vertex) {
    dfs_num.assign(V, 0);
    dfs_low.assign(V, 0);
    dfs_parent.assign(V, 0);
    art_vertex.assign(V, 0);
    dfsCtr = 1;
}
void check(vector<int> &art_vertex) {
    for(int i = 0; i < V; i++)
        if(!dfs_num[i]) {
            root = i;
            rootC = 0;
            artBridge(i, art_vertex);
            art_vertex[root] = rootC > 1;
        }
}

vector<int> pset, wset, weight;


void absorb(int a, int b) {
    adjList[a].insert(adjList[b].begin(), adjList[b].end());
}
int findSet(int i) { return pset[i] == i ? i : (pset[i] = findSet(pset[i]));}
bool isSameSet(int a, int b) { return findSet(a) == findSet(b);}
void unionSet(int a, int b) {
    int i = findSet(a), j = findSet(b);
    if(i == j) return;
    if(wset[i] > wset[j])
        pset[j] = i, wset[i] += wset[j], absorb(i, j);
    else
        pset[i] = j, wset[j] += wset[i], absorb(j, i);
}

void init2(int N) {
    pset.assign(N, 0);
    wset.assign(N, 1);
    for(int i = 0; i < N; i++)
        pset[i] = i;
}

vector<int> ft;
bool proc[20100], vis[20100];

int lastOne(int i) {
    return i & (-i);
}
int ft_rsq(int b) { // Sum until index b
    int sum = 0;
    for(; b; b -= lastOne(b))
        sum += ft[b];
    return sum;
}
int ft_adjust(int k, int v) { // adjust k'th element by v
    for(; k <= ft.size(); k+= lastOne(k))
        ft[k] += v;
}

int main() {
    freopen("travel.in", "r", stdin);
//    freopen("travel.out", "w", stdout);
    cin >> V >> E;
    init(art_vertex);
    adj.assign(V, set<int>());
    bridgeList.assign(V, set<int>());
    // construct
    for(int i = 0; i < E; i++) {
        int a,b;
        cin >> a >> b;
        a--, b--;
        adj[a].insert(b);
        adj[b].insert(a);
    }
    check(art_vertex);
    init2(V);
    // merge
    adjList.assign(V, set<int>());
    for(int u = 0; u < V; u++)
        for(s_it it = adj[u].begin(); it != adj[u].end(); it++) {
            int v = *it;
            if(!art_vertex[v] && !art_vertex[u]) {
                unionSet(u, v);
            } else
//            if(dfs_low[v] <= dfs_num[u])
//                unionSet(u, v);
        }
    // reconfigure
//    cout << "RECONFIG" << endl;
    for(int u = 0; u < V; u++) {
        if(findSet(u) == u) {
            set<int> tmp;
            for(set<int>::iterator it = adjList[u].begin(); it != adjList[u].end(); it++)
                if(*it != u && findSet(*it) == *it)
                    tmp.insert(*it);//, cout << u << ' ' << *it << endl;
            adj[u] = tmp;
        } else
            adj[u].clear();
    }
//    cout << "RECONFIG" << endl;
    // reinspect
    memset(f, 0, sizeof f);
    bridges.clear();
    bridgeList.assign(V, set<int>());
    weight = wset;
    init(tart_vertex);
    check(tart_vertex);
//    // check
//    cout << "CHECK" << endl;
//    for(int i = 0; i < bridges.size(); i++)
//        cout << bridges[i].first << ' ' << bridges[i].second << endl;
//    cout << "CHECK" << endl;
    // segregate
    for(int i = 0; i < bridges.size(); i++) {
        int u = bridges[i].first, v = bridges[i].second;
        adj[u].erase(v), adj[v].erase(u);
    }
    /*
    // calculate
    // this is all wrong
    ft.assign(V+10, 0);
    map<int, int> nodes;
    set<int> Q;
    Q.insert(findSet(0));
    int before = 0, gain = 0, num_nodes_bef = 0;
    while(!Q.empty()) {
        gain = 0;
        int u = *(Q.begin()); Q.erase(Q.begin());
        if(proc[u]) continue;
        proc[u] = vis[u] = true;
        nodes[u] = before;

        queue<int> QQ;
        QQ.push(u);
        while(!QQ.empty()) {
            int v = QQ.front(); QQ.pop();
            gain += weight[v];

            for(s_it it = adj[v].begin(); it != adj[v].end(); it++) {
                int q = *it;

                if(vis[q]) continue;

                int num = nodes.size();
                nodes[q] = num;
                vis[q] = true;

                QQ.push(q);
            }

            if(bridgeList[v].size()) {
                for(s_it itt = bridgeList[v].begin(); itt != bridgeList[v].end(); itt++) {
                    int q = *itt;
                    if(!proc[q])
                        Q.insert(q);
                }
            }
        }

        before += gain;
        num_nodes_bef = nodes.size();
    }
    */

    // output
    for(int u = 0; u < V; u++) {
        if(art_vertex[u]) {
            cout << f[u] << endl;
        } else {
            cout << V-1 << endl;
        }
    }


}
