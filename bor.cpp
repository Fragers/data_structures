#include<bits/stdc++.h>
using namespace std;
//#define DEBUG
#define ll long long
// #define MAXN 1e5+5
// #define INF 1e9+7
const int MAXN = 1e5+3; // С‡РёСЃР»Рѕ РІРµСЂС€РёРЅ
const int INF = 1000000000; // РєРѕРЅСЃС‚Р°РЅС‚Р°-Р±РµСЃРєРѕРЅРµС‡РЅРѕСЃС‚СЊ

struct node
{
    int cnt;
    // int adj[26];
    map<int, int> adj;
    node(){
        cnt = 0;
        // for(int i = 0; i < 26; i++)
        //     adj[i] = -1;
    }
};
 
int root = 0;
int last_node = 0;
node t[4000001];
int flag = 1;
void add(string s){
    int cur = 0;
    for(int i = 0; i < s.size(); i++){
        int ch = s[i] - 'a';
        if(t[cur].adj.find(ch) == t[cur].adj.end()){
            last_node += 1;
            t[cur].adj[ch] = last_node;
        }
        cur = t[cur].adj[ch];
    }
    t[cur].cnt += 1;
    if(t[cur].cnt > 1)
        flag = 0;
}

void del(string s){
    int cur = 0;
    for(int i = 0; i < s.size(); i++){
        int ch = s[i] - 'a';
        if(t[cur].adj.find(ch) == t[cur].adj.end()){
            return;
        }
        cur = t[cur].adj[ch];
    }
    if(t[cur].cnt > 0){
        t[cur].cnt -= 1;
    }
}

bool good(string s){
    int cur = 0;
    for(int i = 0; i < s.size(); i++){
        int ch = s[i] - 'a';
        if(t[cur].adj.find(ch) == t[cur].adj.end()){
            return false;
        }
        cur = t[cur].adj[ch];
    }
    if(t[cur].cnt > 0)
        return true;
    return false;
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    #ifdef DEBUG
        freopen("in", "r", stdin);
    #endif

    #ifdef COMMIT
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
        
    #endif
    int n;
    cin >> n;
    int ans = 0;
            string s;
    for(int i = 0; i < n; i++){

        cin >> s;
        add(s);
        ans += flag;
        flag = 1;
    }
    cout << ans;
    return 0;
}
