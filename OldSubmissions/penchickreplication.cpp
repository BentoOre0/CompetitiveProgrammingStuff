#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int,int>;
using pll = pair<long long int, long long int>;
const int inf = numeric_limits<int>::max();
const ll INF = numeric_limits<ll>::max();
const char sp = ' ';
const char nl = '\n';

ll backtrack(int sid, int length, int remainingspace, int k, vector<ll> &sticks){
	if(length >= k){
		return -INF;
	} else if(sid == sticks.size()){
		return 0;
	} else {
		ll ans = 0;
		cout << ans << nl;
		ans = max(backtrack(sid + 1, length, remainingspace, k, sticks), ans); //skip
		if(remainingspace >= sticks[sid]){
			ans = max(backtrack(sid + 1, length + 1,0,k,sticks) + (sticks[sid] + 1), ans);
		} else {
			ans = max(backtrack(sid + 1, length + sticks[sid] - remainingspace, 0, k, sticks) + (sticks[sid] + 1), ans);
		}
		return ans;
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int T;
	cin >> T;
	while(T--){
		int n, k;
		cin >> n >> k;

		// vector<vector<ll> > dp(n, vector<ll> (k, -1));
		vector<ll> sticks;
		ll temp;
		for(int i = 0; i < n; i++){
			cin >> temp;
			sticks.push_back(temp);
		}
		sort(sticks.begin(), sticks.end());
		for(int i = 1; i <= k; i++){
			cout << backtrack(0,0,0,k,sticks) << sp << 0 << nl;
			break;
		}
		/*
		back track solution
		proof by ac if starting smallest is best case before going full dp
		*/
		// f(0,0,0)

	}
}