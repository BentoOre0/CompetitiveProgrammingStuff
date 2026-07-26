#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int,int>;
using pll = pair<long long int, long long int>;
const int inf = numeric_limits<int>::max();
const ll INF = numeric_limits<ll>::max();
const char sp = ' ';
const char nl = '\n';

tuple<int,int,int,int> combine(tuple<int,int,int,int> lval, tuple<int,int,int,int> rval) {
	return {get<0>(lval)+get<0>(rval),get<1>(lval)+get<1>(rval),get<2>(lval)+get<2>(rval),get<3>(lval)+get<3>(rval)};
}
//source cp algorithms, mymapio notes geek for geeks
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

    tuple<int,int,int,int> range_query_rec(int idx, int L, int R, int i, int j) {
        if (L > R || L > j || R < i){
			return identity;
		}
		if(lazy[idx]){
			val[idx] = flip(val[idx]);
			if(L != R){
				lazy[left(idx)] = !lazy[left(idx)];
				lazy[right(idx)] = !lazy[right(idx)];
			}
			lazy[idx] = false;
		}

		if(L >= i && R <= j){
			return val[idx];
		}
        int m = (L + R) / 2;
        return combine(
            range_query_rec(left(idx), L, m, i, j),
            range_query_rec(right(idx), m + 1, R, i, j)
        );
    }

    void range_update_rec(int idx, int L, int R, int i, int j) {
        
		if(lazy[idx]){
			val[idx] = flip(val[idx]);

			if(L != R){
				lazy[left(idx)] = !lazy[left(idx)];
				lazy[right(idx)] = !lazy[right(idx)];
			}

			lazy[idx] = false;
		}
		if (L > R || L > j || R < i){
			return;
		}

		if(L >= i && R <= j){
			val[idx] = flip(val[idx]);

			if(L != R){
				lazy[left(idx)] = !lazy[left(idx)];
				lazy[right(idx)] = !lazy[right(idx)];
			}
			return;
		}
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


class SegmentTree2 {
	private:
		int sz;
		pii identity = {0,0};
		vector<pii> A, val;
		vector<bool> lazy;
	
		int left(int idx) { return 2 * idx; }
		int right(int idx) { return 2 * idx + 1; }
	
		pii combine(pii lval, pii rval) {
			return {lval.first + rval.first, lval.second + rval.second};
		}
		pii flip(pii NODE){
			/*
			S S'

			S'S
			*/
			return {NODE.second, NODE.first};
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
	
		pii range_query_rec(int idx, int L, int R, int i, int j) {
			if (L > R || L > j || R < i){
				return identity;
			}
			if(lazy[idx]){
				val[idx] = flip(val[idx]);
				if(L != R){
					lazy[left(idx)] = !lazy[left(idx)];
					lazy[right(idx)] = !lazy[right(idx)];
				}
				lazy[idx] = false;
			}
	
			if(L >= i && R <= j){
				return val[idx];
			}
			int m = (L + R) / 2;
			return combine(
				range_query_rec(left(idx), L, m, i, j),
				range_query_rec(right(idx), m + 1, R, i, j)
			);
		}
	
		void range_update_rec(int idx, int L, int R, int i, int j) {
			
			if(lazy[idx]){
				val[idx] = flip(val[idx]);
	
				if(L != R){
					lazy[left(idx)] = !lazy[left(idx)];
					lazy[right(idx)] = !lazy[right(idx)];
				}
	
				lazy[idx] = false;
			}
			if (L > R || L > j || R < i){
				return;
			}
	
			if(L >= i && R <= j){
				val[idx] = flip(val[idx]);
	
				if(L != R){
					lazy[left(idx)] = !lazy[left(idx)];
					lazy[right(idx)] = !lazy[right(idx)];
				}
				return;
			}
			int m = (L + R) / 2;
			range_update_rec(left(idx), L, m, i, min(j, m));
			range_update_rec(right(idx), m + 1, R, max(i, m + 1), j);
			val[idx] = combine(val[left(idx)], val[right(idx)]);    
		}
	
	public:
		SegmentTree2(int n)
			: A(n), val(4 * n), lazy(4 * n, false),
			  sz(n) {}
		SegmentTree2(const vector<pii> &L) : SegmentTree2(L.size()) {
			A = L;
			build_rec(1, 0, sz - 1);
		}
	
		pii range_query(int i, int j) {
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
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
	comp['A'] = 'T';
	comp['T'] = 'A';
	comp['G'] = 'C';
	comp['C'] = 'G';
    string s;
	
	cin >> s;
	while(s.size() < 200000){
		s += complement(s);
	}
	vector<pii> compressions = {{1,0}};
	vector<pii> temp;
	while(compressions.size() < 5000){
		temp = compressions;
		for(int i = 0; i < temp.size(); i++){
			if(temp[i] == make_pair(1,0)){
				compressions.push_back({0,1});
			} else {
				compressions.push_back({1,0});
			}
		}
	}
	/*
	1,0 standard SegTree
	0,1 flipped SegTree
	*/
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
	SegmentTree2 BLOCKS = SegmentTree2(compressions);
	SegmentTree Classic = SegmentTree(thewholemothafuckinthing);
	SegmentTree Flipperino = SegmentTree(thewholemothafuckinthing);
	Flipperino.range_update(0,s.size() - 1);
	int q;
	cin >> q;
	for(int i = 0; i < q; i++){
		char query; int I,J;
		cin >> query >> I >> J;
		I--;
		J--;
		if(query == '?'){
			int I_kth = I / s.size();
			int I_rem = I % s.size();
			int J_kth = J / s.size();
			int J_rem = J % s.size();
			
			tuple<int,int,int,int> Ir = {0,0,0,0}, Jr = {0,0,0,0}, BLKS = {0,0,0,0}, output = {0,0,0,0};


			if(I_kth == J_kth){
				//same block
				pii type = BLOCKS.range_query(I_kth,I_kth);
				if(type == make_pair(1,0)){
					output = Classic.range_query(I_rem,J_rem);
				} else {
					output = Flipperino.range_query(I_rem,J_rem);
				}
			} else {
				//sqrt decomposition type
				pii typeI = BLOCKS.range_query(I_kth,I_kth);
				pii typeJ = BLOCKS.range_query(J_kth,J_kth);
				if(typeI == make_pair(1,0)){
					Ir = Classic.range_query(I_rem,s.size() - 1);
				} else {
					Ir = Flipperino.range_query(I_rem,s.size() - 1);
				}

				if(typeJ == make_pair(1,0)){
					Jr = Classic.range_query(0,J_rem);
				} else {
					Jr = Flipperino.range_query(0,J_rem);
				}
				auto [c,f] = BLOCKS.range_query(I_kth+1,J_kth - 1);

				tuple<int,int,int,int> Cl = Classic.range_query(0,s.size() - 1);
				tuple<int,int,int,int> Fl = Flipperino.range_query(0,s.size() - 1);
				Cl = {get<0>(Cl)*c,get<1>(Cl)*c,get<2>(Cl)*c,get<3>(Cl)*c};
				Fl = {get<0>(Fl)*f,get<1>(Fl)*f,get<2>(Fl)*f,get<3>(Fl)*f};
				BLKS = combine(Cl,Fl);
				output = combine(BLKS,Ir);
				output = combine(output,Jr);		
			}

			// auto temp = ST.range_query(I,J);

			cout << get<0>(output) << sp << get<1>(output) << sp << get<2>(output) << sp << get<3>(output) << nl;
		} else {
			cout << "I WAS NOT MADE FOR THIS :(" << nl;
			return 0;
			// ST.range_update(I,J);
		}
		
	}

	
	
	
}
