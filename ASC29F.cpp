//ASC29F
#include <iostream>
#include <cstdio>
#include <vector>
#include <string>
#include <set>
#include <map>

using namespace std;

typedef long long LL;

string T, P;
vector<int> b, res;
char f[500];
int g[500], h[500];

bool inRange(int i, int j, int p) {
    return i-j <= p && p <= i;
}

bool equals(int i, int j) {
    char a = T[i], b = P[j];
    if(f[a] == b && inRange(i, j, g[a])) {
        return true;
    } else if(!inRange(i, j, g[a]) && !inRange(i, j, h[b])) {
        f[a] = b;
        g[a] = h[b] = i;
        return true;
    }
    return false;
}

void kmpPreprocess() {
    b.assign(P.length(), -1);
    int i = 0, j = -1;
    while (i < P.length()) {
        while (j >= 0 && P[i] != P[j]) j = b[j];
        i++;
        j++;
        b[i] = j;
    }
    for(int i = 0; i < 500; i++)
        g[i] = h[i] = T.length()+10;
}

void match() {
    int i = 0, j = 0;
    for(int i = 0; i < T.length(); i++) {
        while(j >= 0 && !equals(i, j)){
            j = b[j];
        }
        j++;
        if(j == P.length()) {
            res.push_back(i-j+1);
            j = b[j];
        }
    }
}

string modify(string S) {
    set<char> seen, unq;
    for(int i = 0; i < S.length(); i++)
        if(seen.count(S[i]))
            unq.erase(S[i]);
        else
            seen.insert(S[i]),
            unq.insert(S[i]);
    map<char, char> mem;
    for(int i = 0, j = 1; i < S.length(); i++)
        if(unq.count(S[i]))
            S[i] = 0;
        else if(mem.count(S[i]))
            S[i] = mem[ S[i] ];
        else
            S[i] = mem[ S[i] ] = j++;
    return S;
}

int main() {
    freopen("substring.in", "r", stdin);
//    freopen("substring.out", "w", stdout);
    cin >> T >> P;
//    P = modify(P);
    kmpPreprocess();
    match();
    cout << res.size() << endl;
    if(res.size()) {
        for(int i = 0; i < res.size(); i++) {
            if(i) cout << ' ';
            cout << res[i] + 1;
        }
        cout << endl;
    }
    return 0;
}
