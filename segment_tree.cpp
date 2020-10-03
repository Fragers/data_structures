#include <bits/stdc++.h>

using namespace std;

const long long minN = 1e9 + 50;
const long long maxN = -1e9 + 40;


struct segment_tree {
	long long n;
	std::vector<long long> sum;
	std::vector<long long> max_arr;
	std::vector<long long> min_arr;
	
	segment_tree(const std::vector<long long>& values){
		n = values.size();
		sum.assign(4 * n, 0);
		//min_arr.resize(4 * n);
		min_arr.assign(4 * n, minN);
		//max_arr.resize(4 * n);
		max_arr.assign(4 * n, maxN);
		build(1, 0, n, values);
	}

	void build(long long v, long long l, long long r, const std::vector<long long>& values){ // [l, r)
		if(l == r - 1){
			sum[v] = values[l];
			max_arr[v] = values[l];
			min_arr[v] = values[l];
			
		} else{
			long long m = (l + r) / 2;
			
			build(2 * v, l, m, values);
			build(2 * v + 1, m, r, values);
			sum[v] = sum[2 * v] + sum[2 * v + 1]; 
			max_arr[v] = max(max_arr[2 * v], max_arr[2 * v + 1]);
			min_arr[v] = min(min_arr[2 * v], min_arr[2 * v + 1]);
				
		}
	}

	long long get_sum(long long lq, long long rq, long long v, long long l, long long r){
		if(r <= lq || rq <= l)
			return 0;

		if(lq <= l && r <= rq){
			return sum[v];
		}
		long long m = (l + r) / 2;
		return get_sum(lq, rq, 2 * v, l, m) + get_sum(lq, rq, 2 * v + 1, m, r);
	}


	long long get_max(long long lq, long long rq, long long v, long long l, long long r){
		if(r <= lq || rq <= l)
			return maxN;

		if(lq <= l && r <= rq){
			return max_arr[v];
		}
		long long m = (l + r) / 2;
		return max(get_max(lq, rq, 2 * v, l, m), get_max(lq, rq, 2 * v + 1, m, r));
	}

	long long get_min(long long lq, long long rq, long long v, long long l, long long r){
		if(r <= lq || rq <= l)
			return minN;

		if(lq <= l && r <= rq){
			return min_arr[v];
		}
		long long m = (l + r) / 2;
		return min(get_min(lq, rq, 2 * v, l, m), get_min(lq, rq, 2 * v + 1, m, r));
	}

	void update(long long i, long long x, long long v, long long l, long long r) {
		if(l == r - 1) {
			sum[v] = x;
			min_arr[v] = x;
			max_arr[v] = x;
		} else {
			long long m = (l + r) / 2;
			if(i < m){
				update(i, x, 2 * v, l, m);
			} else {
				update(i, x, 2 * v + 1, m , r);
			}
			sum[v] = sum[2 * v] + sum[2 * v + 1]; 
			min_arr[v] = min(min_arr[2 * v], min_arr[2 * v + 1]);
			max_arr[v] = max(max_arr[2 * v], max_arr[2 * v + 1]);
				
		}
	}
};

int main(){
//	freopen("in", "r", stdin);
	long long n = 1e6;
//	cin >> n;
	std::vector<long long> v(n + 1);
	int o = 0;
	for(long long i = 1; i < n; i++){
		v[i - 1] = (i * i) % 12345 + (i * i * i) % 23456;
		if(v[i - 1] < 0)
			o++;
	}
	//cout << o;
	//cout << v[1e5] << ' ' << v[1e5 - 1];

	segment_tree t(v);
	long long q;
	cin >> q;
	// t.update(0, 1000000, 1, 0, n);
	//cout << t.get_max(1e5-1, 1e5, 1, 0, n) << endl;

	// cout << t.get_min(1e5 - 2, 1e5, 1, 1e5 - 2, 1e5) << endl;

	for(long long i = 0; i < q; i++){
		long long f, s;
		cin >>f >> s;
		if(f > 0){
			cout << t.get_max(f - 1, s, 1, 0, n) - t.get_min(f - 1, s, 1, 0, n) << endl;
		}else {
			f = -f;
			t.update(f - 1, s, 1, 0, n);
		}
	}
}
