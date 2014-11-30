//5095 - Transportation
#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>

using namespace std;

typedef pair<int, int> ii;
typedef pair<ii, ii> dii;

int N, M, K;
struct graph {
    vector< vector< pair<ii, ii> *> > adjList;
    vector< vector< int *> > adjListCost;
    vector< pair<ii, ii> > edge;
    vector<int> edgeCost, dist, p;
    int V;

    graph(int n) {
        V = n;
        adjList.assign(n, vector<dii*>());
        adjListCost.assign(n, vector<int *>());
    }

    void connect(int a, int b, int cost, int cap) {
        edge.push_back(make_pair(ii(a,b),ii(cap, 0)));
        edgeCost.push_back(cost);

        adjList[a].push_back(&edge[edge.size()-1]);
        adjListCost[a].push_back(&edgeCost[edge.size()-1]);
        adjList[b].push_back(&edge[edge.size()-1]);
        adjListCost[b].push_back(&edgeCost[edge.size()-1]);
    }

//    bool Dijkstra(int source, int target) {
//        dist.assign(V, INF);
//        p.assign(V, -1);
//
//        dist[source] = 0;
//        priority_queue< ii > Q;
//        Q.push( ii(0, source) );
//        while(!Q.empty()) {
//            int u = Q.top().second, D = -Q.top().first;
//            Q.pop();
//
//            if(D != dist[u]) continue;
//            for(int j = 0; j < adjList[u].size(); j++) {
//                int v = adjList[u][j].first, w = adjList[u][j].second;
//                if(res[u][v] && dist[u] + w < dist[v]) {
//                    p[v] = u, dist[v] = dist[u] + w;
//                    Q.push( ii(-dist[v], v) );
//                }
//            }
//        }
//
//        p[source] = -1;
//        return p[target] != -1;
//    }

    int maxFlow(int s, int t) {

        return 0;
    }

    int maxFlowCost() {

        return 0;
    }
};

int main() {
    while(cin >> N >> M >> K) {
        graph G(N+2);
        G.connect(0, 1, 0, K);
        G.connect(N, N+1, 0, K);
        for(int i = 0; i < M; i++) {
            int a, b, c, d;
            cin >> a >> b >> c >> d;
            G.connect(a, b, c, d);
        }

        if(G.maxFlow(0, N+1) == K)
            cout << G.maxFlowCost() << endl;
        else
            cout << -1 << endl;
    }
}
