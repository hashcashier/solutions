//ASC28I Retry
#include <iostream>
#include <cstdio>
#include <set>
#include <map>
#include <vector>
#include <algorithm>
#include <cstring>
#include <climits>

using namespace std;

typedef pair<int, int> ii;
typedef set<int>::iterator s_it;
typedef map<int, int>::iterator m_it;

struct graph {
    int dfsCtr, root, rootC, V, E;
    vector<int> dfs_num, dfs_low, dfs_parent, art_vertex, tart_vertex;
    vector< set<int> > bridgeList, adj;
    vector< ii > bridges;

    void artBridge(int u) {
        dfs_low[u] = dfs_num[u] = dfsCtr++;
        for(s_it it = adj[u].begin(); it != adj[u].end(); it++) {
            int v = *it;
            if(!dfs_num[v]) {
                dfs_parent[v] = u;
                if(u == root) rootC++;
                artBridge(v);

                if(dfs_low[v] >= dfs_num[u])
                    art_vertex[u] = true;
                if(dfs_low[v] > dfs_num[u])
                    bridges.push_back(ii(u, v));

                dfs_low[u] = min(dfs_low[u], dfs_low[v]);
            } else if(v != dfs_parent[u]) {
                dfs_low[u] = min(dfs_low[u], dfs_num[v]);
            }
        }
    }
    void initArtPB() {
        dfs_num.assign(V, 0);
        dfs_low.assign(V, 0);
        dfs_parent.assign(V, 0);
        art_vertex.assign(V, 0);
        bridges.clear();
        dfsCtr = 1;
    }
    void checkAPB() {
        for(int i = 0; i < V; i++)
            if(!dfs_num[i]) {
                root = i;
                rootC = 0;
                artBridge(i);
                art_vertex[root] = rootC > 1;
            }
    }
    void init() {
        adj.assign(V, set<int>());
        bridgeList.assign(V, set<int>());
    }
};

struct UJSET {
    vector<int> pset, wset;
    int findSet(int i) { return pset[i] == i ? i : (pset[i] = findSet(pset[i]));}
    bool isSameSet(int a, int b) { return findSet(a) == findSet(b);}
    void unionSet(int a, int b) {
        int i = findSet(a), j = findSet(b);
        if(i == j) return;
        if(wset[i] > wset[j])
            pset[j] = i, wset[i] += wset[j];
        else
            pset[i] = j, wset[j] += wset[i];
    }
    void initUJSet(int N) {
        pset.assign(N, 0);
        wset.assign(N, 1);
        for(int i = 0; i < N; i++)
            pset[i] = i;
    }
};

struct countedTree {
    vector< map<int, int> > adjList;
    UJSET *U;
    int V;
    void init(int verts) {
        V = verts;
        adjList.assign(V, map<int,int>());
    }
    int F(int u, int p) {
        int res = U->wset[u];
        // Update edges going to children
        for(m_it it = adjList[u].begin(); it != adjList[u].end(); it++) {
//            int v = U->findSet(it->first), c = it->second;
            int v = (it->first), c = it->second;
            if(v == p || c) continue;
            it->second = F(v, u);
            res += it->second;
        }
        // Update edge going to parent
        for(m_it it = adjList[u].begin(); it != adjList[u].end(); it++)
            if(it->first == p)
                it->second = V - res;
        return res;
    }
};

int main() {
//    long long res = 0;
//    for(int i = 0; i < 20000; i++)
//        for(int j = 0; i + j < 20000; j++)
//                res = max(res, i*j*(20000 - i - j)*1LL);
//    cout << INT_MAX - res << endl;
//    return 0;
    freopen("travel.in", "r", stdin);
    freopen("travel.out", "w", stdout);
    int V, E;
    cin >> V >> E;
    graph GA;
    GA.V = V, GA.E = E;
    GA.init();
    // Original Graph
    for(int i = 0; i < E; i++) {
        int a, b;
        cin >> a >> b;
        a--, b--;
        GA.adj[a].insert(b);
        GA.adj[b].insert(a);
    }
    GA.initArtPB();
    GA.checkAPB();
    // Merge non art points
    UJSET A;
    A.initUJSet(V);
    for(int u = 0; u < V; u++) {
        for(s_it it = GA.adj[u].begin(); it != GA.adj[u].end(); it++) {
            int v = *it;
            if(!GA.art_vertex[u] && !GA.art_vertex[v]) {
                A.unionSet(u, v);
            }
        }
    }
    // Construct new adjacency list
    graph GB;
    GB.V = V, GB.E = E;
    GB.init();
    for(int u = 0; u < V; u++)
        for(s_it it = GA.adj[u].begin(); it != GA.adj[u].end(); it++) {
            int uu = A.findSet(u), vv = A.findSet(*it);
            if(uu != vv)
                GB.adj[ uu ].insert( vv );
        }
    // Re-run articulation points & bridges check
    GB.initArtPB();
    GB.checkAPB();
    // Remove Bridges from B
    for(int i = 0; i < GB.bridges.size(); i++) {
        int a = GB.bridges[i].first, b = GB.bridges[i].second;
        GB.adj[a].erase(b), GB.adj[b].erase(a);
    }
    // Merge into components
    graph GC; GC.V = GB.V, GC.E = GB.E; GC.init();
    UJSET C = A;
    for(int u = 0; u < GC.V; u++)
        for(s_it it = GB.adj[u].begin(); it != GB.adj[u].end(); it++)
            C.unionSet(u, *it);
    // Add bridges to C
    for(int i = 0; i < GB.bridges.size(); i++) {
        int u = GB.bridges[i].first, v = GB.bridges[i].second,
            uu = C.findSet(u), vv = C.findSet(v);
        if(uu != vv)
            GC.adj[ uu ].insert( vv ), GC.adj[ vv ].insert( uu );
    }
    // Create Tree
    countedTree CT; CT.init(GC.V);
    for(int i = 0; i < GC.V; i++)
        for(s_it it = GC.adj[i].begin(); it != GC.adj[i].end(); it++)
            CT.adjList[i][*it] = 0;
    // Calculate Counts
    CT.U = &C;
    CT.F(C.findSet(0), -1);
    // Use all that to answer the big question...
    for(int u = 0; u < V; u++) {
        long long res = V-1;
        if(GA.art_vertex[u]) {
            res = 0;
            int uu = C.findSet(u), tot = 0;
            set<int> seen;
            seen.insert(uu);
            for(s_it it = GA.adj[u].begin(); it != GA.adj[u].end(); it++) {
                int v = *it, vv = C.findSet(v);
//                cout << u << ' ' << v << ' ' << uu << ' ' << vv << ' ' << endl;
                if(seen.count(vv)) continue;
                seen.insert(vv);
                long long weight = CT.adjList[uu][vv];
//                cout << "------>" << weight << ' ' << res << endl;
                res += weight*(V - tot - weight);
                tot += weight;
            }
//            cout << "---+>" << tot << endl;
            res += V - tot - 1;
//            if(seen.size() == 2) res += V - 1 - tot;
        }
//        cout << u+1 << ' ' << res << endl;
        cout << res << endl;
    }

//    cout << "-----------AP------------" << endl;
//    for(int u = 0; u < V; u++)
//        cout << u << ' ' << GA.art_vertex[u] << endl;
//    cout << "-----------GA------------" << endl;
//    for(int u = 0; u < V; u++)
//        for(s_it it = GA.adj[u].begin(); it != GA.adj[u].end(); it++)
//            cout << u << ' ' << *it << endl;
//    cout << "-----------GB------------" << endl;
//    for(int u = 0; u < V; u++)
//        for(s_it it = GB.adj[u].begin(); it != GB.adj[u].end(); it++)
//            cout << u << ' ' << *it << endl;
//    cout << "-----------GC------------" << endl;
//    for(int u = 0; u < V; u++)
//        for(s_it it = GC.adj[u].begin(); it != GC.adj[u].end(); it++)
//            cout << u << ' ' << *it << endl;
//    cout << "-----------BB------------" << endl;
//    for(int i = 0; i < GB.bridges.size(); i++)
//        cout << GB.bridges[i].first << ' ' << GB.bridges[i].second << endl;
//
    return 0;
}
