//10603 - Fill
#include <iostream>
#include <cstdio>
#include <queue>
#include <cstring>
#include <map>

using namespace std;
bool vis[210][210][210];
int dist[210][210][210], resa, resb, d;

void stuff(int val, int sum) {
    if(val <= d) {
        if(resb > d) resb = 0;
        if(val > resb)
            resb = val, resa = sum;
        else if(val == resb)
            resa = min(resa, sum);
    }
}

typedef pair<int, int> ii;
typedef pair<int, ii> iii;
typedef pair<int, iii> STATE;

vector<int> stv(STATE st) {
    vector<int> res(4, 0);
    res[0] = st.first;
    res[1] = st.second.first;
    res[2] = st.second.second.first;
    res[3] = st.second.second.second;
    return res;
}

STATE vst(vector<int> v) {
    return STATE(v[0], iii(v[1], ii(v[2], v[3])));
}

int gcd(int a, int b) {
    return b == 0 ? a : gcd(b, a%b);
}

map< vector<int>, ii > dumbShit;

int main() {
//    freopen("10603 - Fill.in", "r", stdin);
    int T;
    scanf("%d", &T);
//    cin >> T;
    while(T--) {
        int a, b, c;
        scanf("%d %d %d %d", &a, &b, &c, &d);
//        cin >> a >> b >> c >> d;
        vector<int> mem(4, 0);
        mem[0] = a, mem[1] = b, mem[2] = c, mem[3] = d;
//        if(c <= d) {
//            cout << 0 << ' ' << c << endl;
//            continue;
//        } else if(dumbShit.count(mem)) {
//            cout << dumbShit[mem].first << ' ' << dumbShit[mem].second << endl;
//            continue;
//        } else {
//            while(d%gcd(gcd(a, b), c))
//                d--;
//        }
        int MX[4];
        MX[1] = a, MX[2] = b, MX[3] = c;

        vector<int> state(4, 0);
        state[0] = 0, state[3] = c;
        priority_queue< STATE > dijkstra;
        dijkstra.push(vst(state));

        for(int i = 0; i < a; i++)
            for(int j = 0; j < b; j++)
                for(int k = 0; k < c; k++)
                    vis[i][j][k] = false;
//        memset(vis, false, sizeof vis);
//        memset(dist, 0, sizeof dist);

        vis[0][0][c] = true;
        dist[0][0][c] = 0;

        resa = 0, resb = c;
        int steps = 0;
        while(!dijkstra.empty()) {
            state = stv(dijkstra.top());
            dijkstra.pop();
            int A = state[1], B = state[2], C = state[3], D = -state[0];
            if(vis[A][B][C] && D != dist[A][B][C]) continue;
//            cout << A << ' ' << B << ' ' << C << ' ' << D << endl;

            stuff(A, D);
            stuff(B, D);
            stuff(C, D);
            if(A == d || B == d || C == d) break;
            steps++;

            for(int i = 1; i < 4; i++)
                for(int j = 1; j < 4; j++) {
                    int allowed = min(MX[j] - state[j], state[i]);
                    if(allowed && i != j) {
                        vector<int> nstate = state;
                        nstate[0] = -(D+allowed);
                        nstate[i] -= allowed;
                        nstate[j] += allowed;
                        int AA = nstate[1], BB = nstate[2], CC = nstate[3];
                        if(vis[AA][BB][CC] && dist[AA][BB][CC] <= -nstate[0])
                            continue;
                        vis[AA][BB][CC] = true;
                        dist[AA][BB][CC] = -nstate[0];
                        dijkstra.push(vst(nstate));
                    }
                }
        }
//        cout << steps << endl;
//        dumbShit[ mem ] = ii(resa, resb);
        printf("%d %d\n", resa ,resb);
//        cout << resa << ' ' << resb << endl;
    }
    return 0;
}
