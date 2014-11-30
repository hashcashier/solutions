#include <iostream>
#include <cstdio>

#define MAXNUM 1000001

using namespace std;

int N, L, R, num, res[MAXNUM], pos, last, dir;
string state;

void savepos(int i) {
    res[num] = i;
}

void stateswp(int i, int j) {
    char t = state[i];
    state[i] = state[j];
    state[j] = t;
    savepos(j);
}

void goL() {
    stateswp(pos, pos-1);
    pos--;
    last = 0;
}

void goR() {
    stateswp(pos, pos+1);
    pos++;
    last = 1;
}

void goJL() {
    stateswp(pos, pos-2);
    pos -= 2;
    last = 2;
}

void goJR() {
    stateswp(pos, pos+2);
    pos += 2;
    last = 3;
}

bool canL() {
    return last != 1 && pos > L + 1;
}

bool canR() {
    return last != 0 && pos < R - 1;
}

bool canJL() {
    return last != 3 && pos > L + 2 && state[pos-1] != state[pos-2];
}

bool canJR() {
    return last != 2 && pos < R - 2 && state[pos+1] != state[pos+2];
}

int main() {
    freopen("frogs.in", "r", stdin);
    cin >> N;
    L = -1, R = 2*N + 1;
    string W(N, 'W'), B(N, 'B');
    state = W + "X" + B;
    pos = N;

    dir = 0;
    last = -1;
    for(num = 0; num < MAXNUM && L + 1 != R - 1; num++) {
//        cout << L << ' ' << R << endl;
//        cout << state << endl;
        if(dir == 1) {
            if(canJL())
                goJL();
            else if(canL())
                goL(), dir = 1 - dir;
            else
                goR(), dir = 1 - dir;
        } else {
            if(canJR())
                goJR();
            else if(canR())
                goR(), dir = 1 - dir;
            else
                goL(), dir = 1 - dir;
        }

        if(state[L+1] == 'B' && state[R-1] == 'W')
            L++, R--;
    }

    if(num >= MAXNUM) num = -1;
    cout << num << endl;
    for(int i = 0; i < num; i++)
        if(i)
            cout << ' ' << res[i];
        else
            cout << res[i];
    if(num > 0)
        cout << endl;
}
