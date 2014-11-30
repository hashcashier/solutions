//6680 - Join the Conversation
#include <cstdio>
#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include <set>

using namespace std;

bool isAuthor(string token) {
    if(token[0] != '@' || token.length()-1 > 20)
        return false;
    for(int i = 0; i < token.size(); i++)
        if(token[i] == ':' || token[i] == ' ')
            return false;
    return true;
}

int main() {
//    freopen("6680 - Join the Conversation.in", "r", stdin);
    int longest[50010], last[50010], prev[50010];
    string lines[50010], line, mentions[160];
    int n;
    while(cin >> n && n) {
        map<string, int> authIdx;

        for(int i = 0; i < n; i++) {
            getline(cin, line);
            while(line.length() == 0)
                getline(cin, line);
            lines[i] = line;
        }

        int res = 0, residx = -1;
        for(int i = 0; i < n; i++) {
            int pos = lines[i].find(": ");
            if(pos == string::npos)
                continue;

            string first = lines[i].substr(0, pos), second = lines[i].substr(pos + 2);
            istringstream fiss(first), siss(second);
            string author, token;
            bool authed = false;
            while(fiss >> token && !authed)
                if(isAuthor(token))
                    authed = true, author = token;

            if(!authed)
                continue;

            int authorIdx = authIdx.count(author) ? authIdx[author] : -1;
            if(authorIdx == -1) {
                authIdx[author] = authIdx.size();
                authorIdx = authIdx.size();
                longest[authorIdx] = 1, last[authorIdx] = i;
            }

            int M = 0;
            while(siss >> token)
                if(isAuthor(token) && token != author)
                    mentions[M++] = token;

            int maxlen = 1, lastlen = -1;
            for(int j = 0; j < M; j++) {
                int mentidx = authIdx.count(mentions[j]) ? authIdx[mentions[j]] : -1;
                if(mentidx == -1)
                    continue;

                if(longest[mentidx] + 1 > maxlen)
                    maxlen = longest[mentidx] + 1, lastlen = last[mentidx];
            }

            prev[i] = lastlen;

            if(maxlen > longest[authorIdx])
                longest[authorIdx] = maxlen, last[authorIdx] = i;

            if(maxlen > res)
                residx = i, res = maxlen;

        }

        int rev[res], i = 1;
        cout << res << endl;
        while(residx != -1) {
            rev[res - i++] = residx + 1;
            residx = prev[residx];
        }
        cout << rev[0];
        for(int j = 1; j < res; j++)
            cout << ' ' << rev[j];
        cout << endl;
    }
}
