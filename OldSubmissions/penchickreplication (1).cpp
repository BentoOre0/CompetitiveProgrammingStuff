#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int inf = numeric_limits<int>::max();
const ll INF = numeric_limits<ll>::max();
const char sp = ' ';
const char nl = '\n';

class SegmentTree {
private:
    int sz;
    tuple<int,int,int,int> identity = {0,0,0,0};
    vector<tuple<int,int,int,int> > A, val;
	vector<bool> lazy;

    int left(int idx) { return 2 * idx; }
    int right(int idx) { return 2 * idx + 1; }

    tuple<int,int,int,int> combine(tuple<int,int,int,int> lval, tuple<int,int,int,int> rval) {
        return {get<0>(lval)+get<0>(rval),get<1>(lval)+get<1>(rval),get<2>(lval)+get<2>(rval),get<3>(lval)+get<3>(rval)};
    }
	tuple<int,int,int,int> flip(tuple<int,int,int,int> NODE){
		/*
		G C A T

		C G T A
		*/
		return {get<1>(NODE),get<0>(NODE),get<3>(NODE),get<2>(NODE)};
	}
    void propagate(int idx, int L, int R) {
        if (lazy[idx]) {
            if (L != R) {
                int m = (L + R) / 2;
				val[left(idx)] = flip(val[left(idx)]);

				val[right(idx)] = flip(val[right(idx)]);
                lazy[left(idx)] = true;
                lazy[right(idx)] = true;
            }
            lazy[idx] = false;
        }
    }

    void build_rec(int idx, int L, int R) {
        if (L == R) {
            val[idx] = A[L];
            return;
        }
        int m = (L + R) / 2;
        build_rec(left(idx), L, m);
        build_rec(right(idx), m + 1, R);
        val[idx] = combine(val[left(idx)], val[right(idx)]);
    }

    void point_update_rec(int idx, int L, int R, int i) {
        if (L == R) {
            A[i] = flip(A[i]);
            val[idx] = flip(val[idx]);
            return;
        }
        propagate(idx, L, R);
        int m = (L + R) / 2;
        if (i <= m)
            point_update_rec(left(idx), L, m, i);
        else
            point_update_rec(right(idx), m + 1, R, i);
        val[idx] = combine(val[left(idx)], val[right(idx)]);
    }

    tuple<int,int,int,int> range_query_rec(int idx, int L, int R, int i, int j) {
        if (i > j)
            return identity;
        if (L == i && R == j)
            return val[idx];
        propagate(idx, L, R);
        int m = (L + R) / 2;
        return combine(
            range_query_rec(left(idx), L, m, i, min(j, m)),
            range_query_rec(right(idx), m + 1, R, max(i, m + 1), j)
        );
    }

    void range_update_rec(int idx, int L, int R, int i, int j) {
        if (i > j)
            return;
        if (L == i && R == j) {
			val[idx] = flip(val[idx]);
            lazy[idx] = true;
            return;
        }
        propagate(idx, L, R);
        int m = (L + R) / 2;
        range_update_rec(left(idx), L, m, i, min(j, m));
        range_update_rec(right(idx), m + 1, R, max(i, m + 1), j);
        val[idx] = combine(val[left(idx)], val[right(idx)]);
    }

public:
    SegmentTree(int n)
        : A(n), val(4 * n), lazy(4 * n, false),
          sz(n) {}
    SegmentTree(const vector<tuple<int,int,int,int> > &L) : SegmentTree(L.size()) {
        A = L;
        build_rec(1, 0, sz - 1);
    }

    tuple<int,int,int,int> range_query(int i, int j) {
        return range_query_rec(1, 0, sz - 1, i, j);
    }

    void range_update(int i, int j) {
        range_update_rec(1, 0, sz - 1, i, j);
    }
};

 
map<char,char> comp;
string complement(string s){
	string temp = "";
	for(char c: s){
		temp += comp[c];
	}
	return temp;
}

void printshit(SegmentTree ST, int N){
	for(int i = 0; i < N; i++){
		auto tup = ST.range_query(i,i);
		cout << get<0>(tup) << sp;
	}
	cout << nl;
	for(int i = 0; i < N; i++){
		auto tup = ST.range_query(i,i);
		cout << get<1>(tup) << sp;
	}
	cout << nl;
	for(int i = 0; i < N; i++){
		auto tup = ST.range_query(i,i);
		cout << get<2>(tup) << sp;
	}
	cout << nl;
	for(int i = 0; i < N; i++){
		auto tup = ST.range_query(i,i);
		cout << get<3>(tup) << sp;
	}
	cout << nl;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
	comp['A'] = 'T';
	comp['T'] = 'A';
	comp['G'] = 'C';
	comp['C'] = 'G';
    string s;
	
	cin >> s;
	string ogs = s;
	while(s.size() < 200000){
		s += complement(s);
	}
	s = s.substr(0,200000);

	vector<tuple<int,int,int,int> > thewholemothafuckinthing;
	for(char c: s){
		if(c == 'G'){
			thewholemothafuckinthing.push_back({1,0,0,0});
		} else if(c == 'C'){
			thewholemothafuckinthing.push_back({0,1,0,0});
		} else if(c == 'A'){
			thewholemothafuckinthing.push_back({0,0,1,0});
		} else {
			thewholemothafuckinthing.push_back({0,0,0,1});
		}
	}
	SegmentTree ST = SegmentTree(thewholemothafuckinthing);

	int q;
	cin >> q;
	for(int i = 0; i < q; i++){
		char query; int I,J;
		cin >> query >> I >> J;
		I--;
		J--;
		if(query == '?'){
			auto temp = ST.range_query(I,J);
			cout << get<0>(temp) << sp << get<1>(temp) << sp << get<2>(temp) << sp << get<3>(temp) << nl;
		} else {
			ST.range_update(I,J);
		}
		
	}

	
	
	
}
