//10054 - The Necklace
#include <iostream>
#include <cstdio>
#include <vector>
#include <list>

using namespace std;

class graph {
    public:
    vector< vector<int> > adjList;
    list<int> cyc;

    graph(int V) {
        adjList.assign(V, vector<int>());
    }

    void connect(int a, int b) {
        adjList[a].push_back(b);
        adjList[b].push_back(a);
    }

    bool eulerian() {
        for(int i = 0; i < adjList.size(); i++)
            if(adjList[i].size()%2)
                return false;
        return true;
    }

    vector<int> eulerCycle(int start) {
        cyc.clear();
        EulerTour(cyc.begin(), start);
        return vector<int>(cyc.begin(), cyc.end());
    }

    void EulerTour(list<int>::iterator i, int u) {
        for(int j = 0; j < adjList[u].size(); j++) {
            int &v = adjList[u][j];
            if(v > 0) {
                int tmp = v;
                v = 0;
                for(int k = 0; k < adjList[tmp].size(); k++) {
                    int &uu = adjList[tmp][k];
                    if(uu == u) {
                        uu = 0;
                        k = 1000;
                    }
                }
                EulerTour(cyc.insert(i, u), tmp);
            }
        }
    }
};

int main() {
    int T;
    cin >> T;
    for(int cse = 0; cse < T; cse++) {
        if(cse) cout << endl;
        cout << "Case #" << cse+1 << endl;
        int N, a, b;
        graph G(51);
        cin >> N;
        for(int i = 0; i < N; i++) {
            cin >> a >> b;
            G.connect(a, b);
        }

        bool ok = G.eulerian();
        if(ok) {
            vector<int> res = G.eulerCycle(a);
            for(int i = 0; i < res.size(); i++)
                cout << a << ' ' << res[i] << endl,
                a = res[i];
        } else {
            cout << "some beads may be lost" << endl;
        }

    }
    return 0;
}
