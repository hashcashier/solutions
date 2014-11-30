//Subway tree systems
#include <iostream>
#include <cstdio>
#include <cstring>
#include <stack>

using namespace std;

string travs[2];
short other[2][3010], n, m;
//bool vis[3010][3010], sol[3010][3010];
bool taken[3000];

bool calcSegs(int str) {
    stack<short> stk;
    for(int i = 0; i < n; i++) {
        if(travs[str][i] == '0') {
            stk.push(i);
        } else {
            if(stk.empty())
                return false;
            int idx = stk.top();
            stk.pop();
            other[str][i] = idx;
            other[str][idx] = i;
        }
    }
    return stk.empty();
}

bool match(int A, int B);

bool solve(int i, int j) {
    return match(i, j);
//    if(vis[i][j])
//        return sol[i][j];
//    vis[i][j] = true;
//    return sol[i][j] = match(i, j);
}

void rst(int idx) {
    for(int i = idx; i < n; i++) {
        if(other[1][i] < i)
            break;
        taken[i] = false;
        i = other[1][i];
    }
}

bool match(int A, int B) {
    for(int i = A; i < n; i++) {
        if(other[0][i] < i)
            break;

        bool matched = false;
        for(int j = B; !matched && j < n; j++) {
            if(other[1][j] < j)
                break;

            if(!taken[j]&& solve(i+1, j+1))
                taken[j] = matched = true;

            j = other[1][j];
        }

        if(!matched) {
            rst(B);
            return false;
        }
        i = other[0][i];
    }

    for(int i = B; i < n; i++) {
        if(other[1][i] < i)
            break;

        if(!taken[i]) {
            rst(B);
            return false;
        }

        i = other[1][i];
    }
    rst(B);
    return true;
}

int main() {
//    freopen("Subway tree systems.in", "r", stdin);
    int T;
    cin >> T;
    while(T--) {
        cin >> travs[0];
        n = travs[0].length();
        bool res = calcSegs(0);
        travs[0] = "";

        cin >> travs[1];
        m = travs[1].length();
        res = res && calcSegs(1);
        travs[1] = "";

        if(res && n == m && (n%2) == 0) {
//            memset(vis, false, sizeof vis);
            res = match(0, 0);
        }

        cout << (res ? "same" : "different") << endl;
    }
}
