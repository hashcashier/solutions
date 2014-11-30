//10018 - Reverse and Add
#include <iostream>
#include <sstream>
#include <cstdio>

using namespace std;

bool pali(string s) {
    int l = s.length();
    for(int i = 0; i < l; i++) {
        if(s[i] != s[l-i-1])
            return false;

    }
    return true;
}

int main() {
    int T;
    cin >> T;
    while(T--) {
        string num;
        cin >> num;
        int iter = 0;
        while(!pali(num)) {
            iter++;
            istringstream iss(num);
            long long nn, ten = 1;
            iss >> nn;
            for(int i = 0; i < num.length(); i++) {
                nn += int(num[i]-'0') * ten;
                ten *= 10;
            }
            ostringstream oss;
            oss << nn;
            num = oss.str();
        }
        cout << iter << ' ' << num << endl;
    }
    return 0;
}
