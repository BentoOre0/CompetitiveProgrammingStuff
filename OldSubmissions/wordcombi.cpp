#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int,int>;
using pll = pair<long long int, long long int>;
const int inf = numeric_limits<int>::max();
const ll INF = numeric_limits<ll>::max();
const char sp = ' ';
const char nl = '\n';
 
struct Trie{
    private:
        bool isvalidword;
        vector<Trie*> childlist;
    public:
        Trie(){
            isvalidword = false;
            childlist = vector<Trie*>(26,nullptr);
        }
        Trie* getchild(int id){
            return childlist[id];
        }
        bool isreal(){
            return isvalidword;
        }
        void insertword(string word, int index_start, int index_end){
            // cout << word << sp << index_start << sp << index_end << nl;
            if(index_end == index_start){
                isvalidword = true;
                return;
            }
            char value = word[index_start];
            int id = value - 'a';
            if(childlist[id] == nullptr){
                childlist[id] = new Trie();
            }
            childlist[id]->insertword(word, index_start + 1, index_end);
        }

        bool checkword(string word, int index_start, int index_end){
            if(index_start == index_end){
                return isvalidword;
            }
            char value = word[index_start];
            int id = value - 'a';
            if(childlist[id] == nullptr){
                return false;
            } else {
                childlist[id]->checkword(word, index_start+1,index_end);
            }
        }
        
};



int main(){
 
    ll MOD = 1e9+7;
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string s;
    cin >> s;
    int k;
    cin >> k;
    vector<ll> dp((s.size() + 1),0);
    unordered_set<string> hash;
    string sq;
    Trie root = Trie();
    for(int i = 0; i < k; i++){
        cin >> sq;
        hash.insert(sq);
        reverse(sq.begin(), sq.end());
        root.insertword(sq,0,sq.size());
    }
    dp[0] = 1;
    for(int i = 1; i <= s.size(); i++){
        Trie currentnode = root;
        string temp = "";
        for(int j = i - 1; j >= 0; j--){
            char value = s[j];
            int id = s[j] - 'a';
            if(currentnode.getchild(id) == nullptr){
                break;
            }
            currentnode = *currentnode.getchild(id);
            if(currentnode.isreal()){
                dp[i] += dp[j];
                dp[i] %= MOD;
            }
        }
    }
    cout << dp[s.size()] << nl;
}
