#include <bits/stdc++.h>
using namespace std;
#define size_t int

int n, k;
vector < vector<int> > g(4002);
vector < vector<int> > g_l(4002);
vector < vector<int> > g_r(4002);

vector<int> mt;
vector<char> used;
 
bool try_kuhn (int v) {
	if (used[v])  return false;
	used[v] = true;
	for (size_t i=0; i<g[v].size(); ++i) {
		int to = g[v][i];
		if (mt[to] == -1 || try_kuhn (mt[to])) {
			//cout << v << ' ' << to << std::endl;
			mt[to] = v;
			return true;
		}
	}
	return false;
}
set<int>l;
set<int>r;
set<int>se;
set<int>l_pair;
set<int>r_pair;
int was_l[4002];
int was_r[4002];

void dfs(int v, int state){
	if(state == 0){
		if(was_l[v])
			return;
		was_l[v] = true;
			l.erase(v);
		for(auto to: g_l[v]){
			dfs(to, (state + 1) % 2);
		}
	}
	if(state == 1){

		if(was_r[v])
			return;
		was_r[v] = true;
			r.insert(v);

		for(auto to: g_r[v]){
			dfs(to, (state + 1) % 2);
		}
	}
}

int main() {
	cin >> n >> k;

	for(int i = 0; i < n; i++){
		int val;
		cin >> val;
		for(int j = 0; j < val; j++){
			int u;
			cin >> u;
			--u;
			g[i].push_back(u);
		}
		se.insert(i);
		l.insert(i);
	}

	mt.assign(k, -1);
	for(int i = 0; i < n; i++){
		int val;
		cin >> val;
		if(val != 0){
			val--;
			mt[val] = i;
			se.erase(i);		
		}
	}
	for(int i = 0; i < n; i++){
		for(auto to: g[i]){
			if(mt[to] == i){
				g_r[to].push_back(i);
			}else{
				g_l[i].push_back(to);
			}
		}
	}
	for(auto to: se){
			dfs(to, 0);
	}
	cout << l.size() + r.size() << endl;
	cout << l.size() << ' ';
	for(auto to : l){
		cout << to + 1<< ' ';
	}
	cout << endl;
		cout << r.size() << ' ';
	for(auto to : r){
		cout << to + 1 << ' ';
	}
	cout << endl;
}
