//ASC24F
#include <iostream>
#include <cstdio>
#include <string>

using namespace std;

string enc[500], encoding[20], text, code;
int N, M, encodings;

bool F(int a, int b) {
    if(a == N && b == M) return true;
    else if(a >= N || b >= M) return false;

    char cur = text[a];

    if(enc[cur] != "") {
        string encoded = code.substr(b, enc[cur].length());
        if(encoded != enc[cur]) return false;
        return F(a+1, b+enc[cur].length());
    } else {
        string encoded = "";
        bool pref = true;
        for(int i = 0; pref && i < 10 && b + i < M; i++) {
            encoded += code[b + i];
            bool prefix = false;

            for(int j = 0; pref && !prefix && j < encodings; j++)
                if(encoding[j].length() <= i+1 && encoded.find(encoding[j]) == 0) pref = false;
                else if(encoding[j].length() >= i+1 && encoding[j].find(encoded) == 0) prefix = true;

            if(pref && !prefix) {
                enc[cur] = encoding[encodings++] = encoded;
                if(F(a+1, b+i+1))
                    return true;
                enc[cur] = encoding[--encodings] = "";
            }
        }
        return false;
    }
}

int main() {
    freopen("prefix.in", "r", stdin);
    freopen("prefix.out", "w", stdout);

    cin >> text >> code;
    N = text.length(), M = code.length();

    F(0, 0);
    for(int i = 0; i < 500; i++)
        if(enc[i] != "")
            cout << char(i) << ' ' << enc[i] << endl;
}
