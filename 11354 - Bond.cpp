//11354 - Bond
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

typedef pair<int, int> ii;
typedef pair<int, ii> iii;

class graph {
    public:
    vector< vector<ii> > adjList;
    vector<iii> edgeList;
    graph(int V) {
        adjList.assign(V, vector<ii>());
    }
    void connect(int a, int b, int c) {
        adjList[a].push_back(ii(b, c));
        adjList[b].push_back(ii(a, c));
        edgeList.push_back(iii(c, ii(a,b)));
    }
    graph MST() {
        return graph(0);
    }
};

int main() {
    int N, M;
    while(cin >> N >> M) {
        graph G(N);
        for(int i = 0; i < M; i++) {
            int a, b, c;
            cin >> a >> b >> c;
            G.connect(a, b, c);
        }
        graph GG = G.MST();

    }
}
