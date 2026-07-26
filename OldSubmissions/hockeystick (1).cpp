#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int,int>;
using pll = pair<long long int, long long int>;
const int inf = numeric_limits<int>::max();
const ll INF = numeric_limits<ll>::max();
const char sp = ' ';
const char nl = '\n';

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int T;
	cin >> T;
	while(T--){
		int n, k;
		cin >> n >> k;
		vector<int> sticks;
		int temp;
		vector<vector<vector<int> > > dp(2, vector<vector<int> >(k+1,vector<int>(2, -inf)));
		for(int i = 0; i < n; i++){
			cin >> temp;
			sticks.push_back(temp);
		}
		int point = 1;
		int mine = 0;
		dp[mine][0][0] = 0;
		sort(sticks.rbegin(), sticks.rend());
		for(int i = 0; i < sticks.size(); i++){
			for(int L = 0; L <= k; L++){
				for(int hasgap = 0; hasgap < 2; hasgap++){
					dp[point][L][hasgap] = -inf;
				}
			}
			for(int L = 0; L <= k; L++){
				for(int hasgap = 0; hasgap < 2; hasgap++){
					if(dp[mine][L][hasgap] == -inf){
						continue;
					}
					dp[point][L][hasgap] = max(dp[mine][L][hasgap], dp[point][L][hasgap]);
					if(hasgap){
						if(i > 0){
							int freespace = sticks[i-1] - 1;
							int cost = max(sticks[i] - freespace, 1);
							// ans = max(ans,sticks[i] + 1 + f(i + 1, N - cost, 0, sticks));
							if(L + cost <= k){
								dp[point][L + cost][0] = max(dp[point][L + cost][0], dp[mine][L][1] + sticks[i] + 1);
							}
							
						}
					} else {
						// ans = max(ans,f(i + 1, N, 0, sticks));
						// ans = max(ans,sticks[i] + 1 + f(i + 1, N - sticks[i], 1, sticks));
						if(L + sticks[i] <= k){
							dp[point][L + sticks[i]][1] = max(dp[mine][L][0] + sticks[i] + 1, dp[point][L + sticks[i]][1]);
						}
					}
				}
			}
			swap(mine,point);
		}
		int rt = 0;
		for(int i = 1; i <= k; i++){
			rt = max(dp[mine][i][0], rt);
			rt = max(dp[mine][i][1], rt);
			cout << rt << sp << 0 << nl;
		}

	}
}