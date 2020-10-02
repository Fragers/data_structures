#include <bits/stdc++.h>

using namespace std;

struct segment_tree {
	int n;
	std::vector<int> sum;
	segment_tree(const std::vector<int>& values){
		n = values.size();
		sum.resize(4 * n);
		build(1, 0, n, values);
	}

	void build(int v, int l, int r, const std::vector<int>& values){ // [l, r)
		if(l == r - 1){
			sum[v] = values[l];
		} else{
			int m = (l + r) / 2;
			
			build(2 * v, l, m, values);
			build(2 * v + 1, m, r, values);
			sum[v] = sum[2 * v] + sum[2 * v + 1]; 
		}
	}

	int get_sum(int lq, int rq, int v, int l, int r){
		if(r <= lq || rq <= l)
			return 0;

		if(lq <= l && r <= rq){
			return sum[v];
		}
		int m = (l + r) / 2;
		return get_sum(lq, rq, 2 * v, l, m) + get_sum(lq, rq, 2 * v + 1, m, r);
	}

	void update(int i, int x, int v, int l, int r) {
		if(l == r - 1) {
			sum[v] = x;
		} else {
			int m = (l + r) / 2;
			if(i < m){
				update(i, x, 2 * v, l, m);
			} else {
				update(i, x, 2 * v + 1, m , r);
			}
			sum[v] = sum[2 * v] + sum[2 * v + 1]; 
		}
	}
};

int main(){

	int n;
	cin >> n;
	std::vector<int> v(n);

	for(auto& i : v){
		cin >> i;
	}
	segment_tree t(v);
	int q;
	cin >> q;
	for(int i = 0; i < q; ++i) {
		int qr, l, r;
		cin >> qr;
		if(qr == 1) {
			cin >> l >> r;
			cout << t.get_sum(l - 1, r, 1, 0, n) << endl;
		} else{
			int idx, x;
			cin >> idx >> x;
			t.update(idx - 1, x, 1, 0, n);
		}
	}

}
