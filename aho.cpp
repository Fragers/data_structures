#include <bits/stdc++.h>

using namespace std;

int link(int x);
int go(int x, int c);

struct node
{
	int par;
	int ch;
	int adj[26];
	int go[26];
	int link;
	int dp;
	int cnt;
	string s;
	bool is_term;
	bool was;
	node(){
		is_term = false;
		par = -1;
		ch= -1;
		dp = -1;
		cnt = 0;
		link = -1;
		for(int i = 0; i < 26; i++)
			adj[i] = go[i] = -1;
		was = false;
	}
};


int last_node = 0;
node t[1000001];


int link(int x){
	if(t[x].link != -1){
		return t[x].link;
	} else if (x == 0 || t[x].par == 0){
		return t[x].link = 0;
	} else {
		return go(link(t[x].par), t[x].ch);
	}
}



int go(int x, int c){
	if(t[x].go[c] != -1){
		return t[x].go[c];
	} else if(t[x].adj[c] != -1){
		return t[x].go[c] = t[x].adj[c];
	} else {
		if(x == 0){
			return t[x].go[c] = 0;
		}
		return t[x].go[c] = go(link(x), c);
	}	
}



int dp(int x){
	if(t[x].dp != -1){
		return t[x].dp;
	} else {
		return t[x].dp = t[x].cnt + (x == 0 ? 0 : dp(link(x)));
	}
}

map<string, int>ans;

void add(string& s){
	int cur = 0;
	for(int i = 0; i < s.length(); i++){
		int ch = s[i] - 'a';
		if(t[cur].adj[ch] == -1){
			last_node += 1;
			t[cur].adj[ch] = last_node;
			t[last_node].par = cur;
			t[last_node].ch = ch;
		}
		cur = t[cur].adj[ch];
	}
	t[cur].s = s;
	t[cur].cnt += 1;
	t[cur].is_term = true;

}

void check(int v){
	while(v != 0){

		if(t[v].was)
			break;
		if(t[v].is_term){
			ans[t[v].s] = 1;
		//	cout << t[v].s << endl;
		}
		t[v].was = true;
		v = link(v);
	}
}

int main(){
	// int n;
	// cin >> n;;
	// for(int i = 0; i < n; i++){

	// 	string s;
	// 	cin >> s;
	// 	add(s);
	// }
	// string T;
	// cin >> T;
	// long long res = 0;
	// int cur = 0;
	// for(int i = 0; i < T.size(); i++){
	// 	cur = go(cur, T[i] - 'a');
	// 	res += dp(cur);
	// }
	// cout << res << '\n';
	string s;
	cin >> s;
	int n;
	cin >> n;
	std::vector<string> v;
	for(int i = 0; i < n; i++){
		string f;
		cin >> f;
		add(f);
		v.push_back(f);
	}
	int cur = 0;
	for(int i = 0; i < s.size(); i++){
		cur = go(cur, s[i] - 'a');
		check(cur);
	}
	for(auto  f : v){
		//cout << f << endl;
		if(ans[f] == 1){
			cout << "Yes" << endl;

		}else
			cout << "No\n";
	}
	return 0;
}
