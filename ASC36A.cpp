//ASC36A
#include <iostream>
#include <cstdio>
#include <cstring>
#include <queue>
#include <stack>
#include <set>
#include <map>
#include <cassert>


using namespace std;

int n, N, wire[1000010][3], wireColor[1000010], socketWire[1000010], socketPair[1000010],
    socketAss[1000010], wireSocket[1000010], socketColor[1000010];
set<int> avail;
stack<int> dfs[100010];

int idx(int i) {
    return (N+i)%N;
}

bool BFS(int i, int betenganDepth) {
    if(wireSocket[socketWire[i]] != -1)
        return true;

    queue<int> Q, seen;
    Q.push(i);
    socketAss[i] = 1;
    bool ok = true;
    while(!Q.empty() && ok) {
        int u = Q.front(); Q.pop();
        seen.push(u);

        for(int j = -1; ok && j < 2; j += 2) {
            int v = idx(u+j);
            if(socketColor[u] != socketColor[v])
                continue;
            else if(socketAss[v])
                ok = false;
            else if(!socketAss[socketPair[v]])
                socketAss[socketPair[v]] = 1, Q.push(socketPair[v]);

//            assert(wireSocket[socketWire[v]] == -1);
        }
    }
    while(!seen.empty()) {
        int u = seen.front(); seen.pop();
        if(!ok)
            socketAss[u] = 0;
        else
            wireSocket[socketWire[u]] = u, avail.erase(u), avail.erase(socketPair[u]), dfs[betenganDepth].push(u);
    }

    return ok;
}

void refresh(int betenganDepth) {
    while(!dfs[betenganDepth].empty()) {
        int u = dfs[betenganDepth].top(); dfs[betenganDepth].pop();
        avail.insert(u);
        avail.insert(socketPair[u]);
        socketAss[u] = 0;
        wireSocket[socketWire[u]] = -1;
    }
}

int DFS(int, int);

bool falafel(int i, int betenganDepth) {
    int choice = DFS(i, betenganDepth);
    if(choice) {
        refresh(betenganDepth);
        if(choice < 2 && !DFS(socketPair[i], betenganDepth))
            refresh(betenganDepth);
        return false;
    }
    return true;
}

int DFS(int i, int betenganDepth) {
    bool ok = BFS(i, betenganDepth);
    int res = 1;
    if(!ok)
        ok = BFS(socketPair[i], betenganDepth),
        res = 2;

    if(ok && avail.size())
        ok = falafel(*(avail.begin()), betenganDepth+1);

    return ok ? 0 : res;
}

int main() {
    freopen("chip.in", "r", stdin);
    freopen("chip.out", "w", stdout);
    cin >> n;

//    freopen("chip.2.in", "r", stdin);
//    while(cin >> n) {
//        memset(socketAss, 0, sizeof socketAss);
//        memset(wire, 0, sizeof wire);
        memset(wireSocket, -1, sizeof wireSocket);
        avail.clear();
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

        bool ok = true;
        for(int i = 0; ok && i < numColors; i++) {
            avail = set<int>(colorSockets[i].begin(), colorSockets[i].end());
            ok &= falafel(*(avail.begin()), 0);
        }

        if(ok) {
            cout << "YES" << endl;
            for(int i = 0; i < n; i++) {
                if(i) cout << ' ';
    //            assert(wireSocket[i] >= 0);
                cout << wireSocket[i]+1;
            }
            cout << endl;
        } else {
            cout << "NO" << endl;
        }

//    }

    return 0;
}
