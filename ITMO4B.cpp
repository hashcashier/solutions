#include <cstdio>
#include <cstring>
#include <iostream>
#include <sstream>
#include <map>
#include <set>

using namespace std;

int N, G, U;
map<string, int> gate, typemap;
int in[50][2], out[50], type[50];

int mem[1<<8][50][50][10];
int F(int inp, int i, int g, int f) {
    int &res = mem[inp][i][g][f], tp = type[i];

    if(res != -1)
        return res;

    if(i == g && f < 2)
        return res = f;

    if(tp == 0)
        res = (inp & (1<<i)) > 0;
    else if(tp == 1) {
        res = F(inp, in[i][0], g, f) & F(inp, in[i][1], g, f);
    } else if(tp == 2) {
        res = F(inp, in[i][0], g, f) ^ 1;
    } else if(tp == 3) {
        res = F(inp, in[i][0], g, f) | F(inp, in[i][1], g, f);
    } else if(tp == 4) {
        res = F(inp, in[i][0], g, f) ^ F(inp, in[i][1], g, f);
    } else if(tp == 5) {
        res = F(inp, in[i][0], g, f);
    }

    if(i == g && f == 2)
        res = 1 - res;
    return res;
}

void precomp() {
    for(int i = 1; i < 20; i++) {
        ostringstream iss;
        iss << 'g' << i;
        gate[iss.str()] = 7+i;
    }
    for(int i = 1; i < 9; i++) {
        ostringstream iss;
        iss << 'i' << i;
        gate[iss.str()] = i-1;
    }

    for(int i = 27; i < 50; i++)
        type[i] = 5;

    typemap["a"] = 1;
    typemap["n"] = 2;
    typemap["o"] = 3;
    typemap["x"] = 4;
}

string getmsg(int g, int f) {
    if(f == 3) return "No faults detected";
    ostringstream msg;
    msg << "Gate " << g+1 << " is failing; output ";

    if(f == 0) msg << "stuck at 0";
    else if(f == 1) msg << "stuck at 1";
    else if(f == 2) msg << "inverted";
    return msg.str();
}

int main() {
    freopen("bad.in", "r", stdin);
//    freopen("bad.out", "w", stdout);
    int cse = 1;
    precomp();

    while(cin >> N >> G >> U && (N || G || U)) {
        cout << "Case " << cse++ << ": ";

        for(int i = 0; i < G; i++) {
            int gateNode = 8 + i;
            string t, x, y;
            cin >> t;
            type[gateNode] = typemap[t];

            if(t != "n") {
                cin >> x >> y;
                in[gateNode][0] = gate[x];
                in[gateNode][1] = gate[y];
            } else {
                cin >> x;
                in[gateNode][0] = gate[x];
            }
        }

        for(int i = 0; i < U; i++) {
            int outNode = 27 + i, x;
            cin >> x;
            in[outNode][0] = 7 + x;
        }

        int B;
        cin >> B;
        set<string> result, tmp;
        for(int g = 0; g < G; g++)
            for(int f = 0; f < 4; f++)
                result.insert(getmsg(g, f));

        memset(mem, -1, sizeof mem);
        for(int i = 0; i < B; i++) {
            int inp = 0, x;
            for(int j = 0; j < N; j++) {
                cin >> x;
                inp |= x<<j;
            }
//            cout << inp << endl;

            int expected[U];
            for(int j = 0; j < U; j++)
                cin >> expected[j];

            tmp.clear();
            for(int g = 0; g < G; g++) {
                for(int f = 0; f < 4; f++) {
                    bool possible = true;
                    for(int u = 0; u < U && possible; u++)
                        if(F(inp, 27 + u, 8 + g, f) != expected[u])
                            possible = false;

                    if(possible) {
                        string msg = getmsg(g, f);
                        if(result.count(msg))
                            tmp.insert(msg);
                    }
                }
            }

            result = tmp;
        }

        if(result.count("No faults detected"))
            cout << "No faults detected" << endl;
        else if(result.size() == 1)
            cout << *(result.begin()) << endl;
        else
            cout << "Unable to totally classify the failure" << endl;// << ' ' << result.size() << endl;
    }
}
