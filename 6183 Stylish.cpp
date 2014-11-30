// 6183 Stylish
#include <iostream>
#include <cstdio>
#include <vector>
#include <set>

using namespace std;
vector<string> p, q;
vector< set<int> > r;

bool ok(int R, int C, int S) {
    int ro = 0, rc = 0, co = 0, cc = 0, so = 0, sc = 0;
    for(int i = 0; i < p.size(); i++) {
        int expected = R*(ro-rc) + C*(co-cc) + S*(so-sc), found = 0;
        int j = 0;
        while(j < p[i].length() && p[i][j] == '.')
            j++, found++;
        if(found != expected) return false;
        while(j < p[i].length()) {
            char c = p[i][j];
            if(c == '(') ro++;
            else if(c == ')') rc++;
            else if(c == '{') co++;
            else if(c == '}') cc++;
            else if(c == '[') so++;
            else if(c == ']') sc++;
            j++;
        }
    }
    return true;
}

void calc(int R, int C, int S) {
    int ro = 0, rc = 0, co = 0, cc = 0, so = 0, sc = 0;
    for(int i = 0; i < q.size(); i++) {
        int expected = R*(ro-rc) + C*(co-cc) + S*(so-sc);
        r[i].insert(expected);
        for(int j = 0; j < q[i].length(); j++) {
            char c = q[i][j];
            if(c == '(') ro++;
            else if(c == ')') rc++;
            else if(c == '{') co++;
            else if(c == '}') cc++;
            else if(c == '[') so++;
            else if(c == ']') sc++;
        }
    }
}

int main() {
//    freopen("outlier.in", "r", stdin);
    int n, m;
    while(cin >> n >> m && n && m) {
        p = vector<string>(n), q = vector<string>(m), r = vector<set<int> >(m);
        getline(cin, p[0]);
        for(int i = 0; i < n; i++)
            getline(cin, p[i]);
        for(int i = 0; i < m; i++)
            getline(cin, q[i]),
            r[i].clear();

        for(int R = 1; R <= 20; R++)
            for(int C = 1; C <= 20; C++)
                for(int S = 1; S <= 20; S++)
                    if(ok(R, C, S))
                        calc(R, C, S);

        for(int i = 0; i < m; i++) {
            if(i) cout << ' ';
            if(r[i].size() != 1) cout << -1;
            else cout << *r[i].begin();
        }
        cout << endl;
    }
    return 0;
}
