//ASC36A2
#include <iostream>
#include <cstdio>
#include <cassert>
#include <cstring>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

int n, N, wire[1000010][3], wireColor[1000010], socketWire[1000010], socketPair[1000010],
    socketAss[1000010], wireSocket[1000010], socketColor[1000010], num_SCC[1000010], SCC_pair[1000010], sol[1000010];

int idx(int i) {
    return (N+i)%N;
}

class graph {
    public:
    vector< vector<int> > adjList, SCC;
    vector<int> dfs_num, dfs_low, dfs_stack, visited, tsort;
    int dfs_count, V;
    graph(int Vert) {
        V = Vert;
        adjList.assign(V, vector<int>());
    }

    void connect(int a, int b) {
        adjList[a].push_back(b);
    }

    void tarjanSCC(int u) {
        visited[u] = 1;
        dfs_num[u] = dfs_low[u] = ++dfs_count;
        dfs_stack.push_back(u);

        for(int j = 0; j < adjList[u].size(); j++) {
            int v = adjList[u][j];
            if(!dfs_num[v])
                tarjanSCC(v);
            if(visited[v])
                dfs_low[u] = min(dfs_low[u], dfs_low[v]);
        }
        if(dfs_num[u] == dfs_low[u]) {
            SCC.push_back(vector<int>());
            while(!dfs_stack.empty()) {
                int v = dfs_stack.back(); dfs_stack.pop_back();
                visited[v] = 0;
                SCC[SCC.size()-1].push_back(v);
                if(u == v) break;
            }
        }
    }

    vector< vector<int> > getSCC() {
        if(SCC.size() != 0) return SCC;
        dfs_num.assign(V, 0);
        dfs_low.assign(V, 0);
        visited.assign(V, 0);
        dfs_count = 0;
        for(int i = 0; i < V; i++)
            if(dfs_num[i] == 0)
                tarjanSCC(i);
        return SCC;
    }

    graph condense() {
        graph G = graph(SCC.size());
        for(int i = 0; i < SCC.size(); i++)
            for(int j = 0; j < SCC[i].size(); j++) {
                int u = SCC[i][j];
                for(int k = 0; k < adjList[u].size(); k++) {
                    int v = adjList[u][k];
                    if(num_SCC[v] != i)
                        G.connect(i, num_SCC[v]);
                }
            }
        return G;
    }

    graph reverse() {
        graph G = graph(V);
        for(int u = 0; u < V; u++)
            for(int j = 0; j < adjList[u].size(); j++)
                G.connect(adjList[u][j], u);
        return G;
    }

    void toposortDFS(int u) {
        dfs_num[u] = ++dfs_count;
        for(int j = 0; j < adjList[u].size(); j++) {
            int v = adjList[u][j];
            if(!dfs_num[v])
                toposortDFS(v);
        }
        tsort.push_back(u);
    }

    vector<int> toposort() {
        tsort.clear();
        dfs_num.assign(V, 0);
        dfs_count = 0;
        for(int i = 0; i < V; i++)
            if(!dfs_num[i])
                toposortDFS(i);
        std::reverse(tsort.begin(), tsort.end());
        return tsort;
    }
};

bool analyzeSCC(vector< vector<int> > &SCC) {
    for(int i = 0; i < SCC.size(); i++) {
        for(int j = 0; j < SCC[i].size(); j++)
            num_SCC[ SCC[i][j] ] = i;
    }

    for(int i = 0; i < SCC.size(); i++) {
        for(int j = 0; j < SCC[i].size(); j++) {
            if(j)// cout << SCC_pair[i] << ' ' << num_SCC[ socketPair[SCC[i][j]] ] << endl,
                assert(SCC_pair[i] == num_SCC[ socketPair[SCC[i][j]] ]);
            SCC_pair[i] = num_SCC[ socketPair[SCC[i][j]] ];

        }
    }

    for(int i = 0; i < N; i++)
        if(num_SCC[i] == num_SCC[socketPair[i]])
            return false;
    return true;
}

void applySolution(graph &G, int u, int solution) {
    sol[u] = solution;
    for(int i = 0; i < G.adjList[u].size(); i++) {
        int v = G.adjList[u][i];
        if(!sol[v])
            applySolution(G, v, solution);
        assert(sol[v] == sol[u]);
    }
}

void solve2SAT(graph &G) {
    vector<int> tOrder = G.toposort();
    graph GG = G.reverse();
    for(int i = 0; i < tOrder.size(); i++) {
        if(!sol[ tOrder[i] ])
            applySolution(GG, tOrder[i], 2),
            applySolution(G, SCC_pair[ tOrder[i] ], 1);
    }

    for(int i = 0; i < N; i++)
        if(sol[ num_SCC[i] ] == 1)
            wireSocket[ socketWire[i] ] = i;

}

int main() {
    freopen("chip.in", "r", stdin);
    freopen("chip.out", "w", stdout);

//    freopen("chip.2.in", "r", stdin);
    while(cin >> n) {
        memset(socketAss, 0, sizeof socketAss);
        memset(wire, 0, sizeof wire);
        memset(sol, 0, sizeof sol);
        memset(num_SCC, 0, sizeof num_SCC);
        memset(wireSocket, -1, sizeof wireSocket);
        map<int, int> colorMap;
        int numColors = 0;

        N = 2*n;
        for(int i = 0; i < n; i++) {
            cin >> wireColor[i];
            if(colorMap.count(wireColor[i]) == 0)
                wireColor[i] = colorMap[wireColor[i]] = numColors++;
            else
                wireColor[i] = colorMap[wireColor[i]];
        }
        vector<int> colorSockets[numColors];

        for(int i = 0; i < N; i++)
            cin >> socketWire[i],
            socketWire[i]--,
            wire[ socketWire[i] ][ ++wire[ socketWire[i] ][0] ] = i,
            socketColor[i] = wireColor[ socketWire[i] ],
            colorSockets[ socketColor[i] ].push_back(i);

        for(int i = 0; i < n; i++) {
            socketPair[ wire[i][1] ] = wire[i][2],
            socketPair[ wire[i][2] ] = wire[i][1];
        }

        // check here
        graph G(N);
        // 'a v 'b = a -> 'b = b -> 'a
        for(int i = 0; i < N; i++)
            if(socketColor[i] == socketColor[idx(i+1)])
                G.connect(i, socketPair[idx(i+1)]),
                G.connect(idx(i+1), socketPair[i]);

        vector< vector<int> > SCC = G.getSCC();
        bool ok = analyzeSCC(SCC);

        if(ok) {
            cout << "YES" << endl;
            graph GG = G.condense();
            solve2SAT(GG);
            for(int i = 0; i < n; i++) {
                if(i) cout << ' ';
                assert(wireSocket[i] >= 0);
                cout << wireSocket[i]+1;
            }
            cout << endl;
        } else {
            cout << "NO" << endl;
        }
    }

    return 0;
}
