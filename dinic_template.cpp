#include <bits/stdc++.h>
using namespace std;
// #define COMMIT
#define ll long long



const ll N = 2e4 + 50;
const ll M = 6 * 1e5 + 5;
const ll INF = 1e18 + 7;

std::vector<ll> g[N];

ll to[M];
ll flow[M];
ll cap[M];
ll was[N];
ll p[N];
ll ptr[N];
ll dist[N];

ll T = 0;

ll s, t;

ll cnt = 1;


void add_edge(ll v, ll to, ll cap){
    g[v].push_back(T);
    ::to[T] = to;
    ::cap[T] = cap;
    T++;
}



ll bfs(){
    queue<ll>q;
    q.push(s);
    // fill(was, was + N, 0);
    fill(p, p + N, -1);
    fill(ptr, ptr + N, 0);
    fill(dist, dist + N, INF);
    was[s] = 1;
    p[s] = s;
    dist[s] = 0;
    while(!q.empty()) {
        ll v = q.front(); q.pop();
        for(auto e : g[v]){
            ll to = ::to[e];

            if(p[to] == -1 && cap[e] > flow[e]){
                // was[to] = 1;
                q.push(to);
                p[to] = v;
                dist[to] = dist[v] + 1;
                if(to == t)
                    break;
            }
        }
    }
    return p[t] != -1;
}



ll dfs(ll v, ll flow = INF){

    // was[v] = cnt;

    if(v == t)
        return flow;

    for(; ptr[v] < g[v].size(); ptr[v]++){
        ll e = g[v][ptr[v]];
        ll to = ::to[e];

        if(::flow[e] < ::cap[e] && dist[to] == dist[v] + 1){
            ll tmp = min(flow, ::cap[e] - ::flow[e]);
            ll res = dfs(to, tmp);
            ::flow[e] += res;
            ::flow[e^1] -= res;
            if(res > 0)
                return res;

        }
    }
    
    return 0;
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


    ll n, m;
    cin >> n >> m;
        s = 2e4+10;
    t = 2e4+20;

    int pass = 1e4 + 1;
    char mp[n][m];
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++)
            cin >> mp[i][j];
    }
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            if(i - 1 >= 0 && mp[i][j] == '.' && mp[i-1][j] == '.'){
                add_edge(i * m + j, (i - 1) * m + j + pass, 1);
                add_edge((i - 1) * m + j + pass, i * m + j, 0);
            }

            if(j - 1 >= 0 && mp[i][j] == '.' && mp[i][j-1] == '.'){
                add_edge(i * m + j, (i) * m + j - 1 + pass, 1);
                add_edge((i) * m + j - 1 + pass, i * m + j, 0);
            }
            if(i + 1 < n && mp[i][j] == '.' && mp[i+1][j] == '.'){
                add_edge(i * m + j, (i + 1) * m + j + pass, 1);
                add_edge((i + 1) * m + j + pass, i * m + j, 0);
            }

            if(j + 1 < m && mp[i][j] == '.' && mp[i][j+1] == '.'){
                add_edge(i * m + j, (i) * m + j + 1 + pass, 1);
                add_edge((i) * m + j + 1 + pass, i * m + j, 0);
            }
        }
    }
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            if(mp[i][j] == '.'){
                add_edge(s, i * m + j, 1);
                add_edge(i * m + j, s, 0);
                   
            }
        }
    }
    int u = 0;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            if(mp[i][j] == '.'){
                add_edge(i * m + j + pass, t, 1);
                add_edge(t,i * m + j + pass,  0);
                u++;
            }
        }
    }
    

    ll flow;
    ll ans = 0;
    while(bfs()){
        // cerr << 1;
        while((flow = dfs(s)) > 0) {
            ans += flow;    
        }

        cnt++;
    }
    // cout << ans;
    if(ans ==  u)
        cout << "Yes";
    else
        cout << "No";

    return 0;
}

