#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<long long, long long>;
const ll INF = numeric_limits<ll>::max();
const int inf = numeric_limits<int>::max();
const double dinf = numeric_limits<double>::max();
const char nl = '\n', sp = ' ';

vector<int> dy = {0,0,1,-1};
vector<int> dx = {1,-1,0,0};
map<string,unordered_set<int> > masks;
map<string,string> translate;

ll DFS(int i, int j, int ccs, vector<vector<bool> > &vis, vector<vector<string> > &grid){
    vis[i][j] = true;
    ll total = stoi(grid[i][j]);
    grid[i][j] = to_string(ccs); //mark this region as this one
    for(int k = 0; k < 4; k++){
        if(!vis[i + dx[k]][j + dy[k]]){
            total += DFS(i + dx[k], j + dy[k], ccs, vis, grid);
        }
    }
    return total;
}

void _dfs(int i, int j, vector<vector<bool> > &vis2, vector<vector<string> > &update){
    vis2[i][j] = true;
    update[i][j] = "#";
    for(int k = 0; k < 4; k++){
        if(i + dx[k] >= 0 && i + dx[k] < update.size()){
            if(j + dy[k] >= 0 && j + dy[k] < update[0].size()){
                if(!vis2[i + dx[k]][j + dy[k]] && update[i + dx[k]][j + dy[k]] != "#"){
                    _dfs(i + dx[k],j + dy[k], vis2, update);
                }
            }
        }
    }
}

bool is_number(const string &s){
    auto it = s.begin();
    while(it != s.end() && isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}
bool issubstring(string wall, string tocheck){
    char c = wall[0];
    for(char e: tocheck){
        if(e == c){
            return true;
        }
    }
    return false;
}

void paint(int i, int j, string adj, vector<vector<bool> > &vis2, vector<vector<string> > &grid){
    vis2[i][j] = true;
    if(is_number(grid[i][j])){
        int num = stoi(grid[i][j]);
        masks[adj].insert(num);
    }
    for(int k = 0; k < 4; k++){
        if(!vis2[i + dx[k]][j + dy[k]]){
            paint(i + dx[k], j + dy[k],adj,vis2,grid);   
        }
    }
}

unordered_set<int> intersection(const unordered_set<int> &a,const  unordered_set<int> &b){
    unordered_set<int> rs;
    if(a.size() < b.size()){
        for(int elem: a){
            if(b.count(elem)){
                rs.insert(elem);
            }
        }
    } else {
        for(int elem: b){
            if(a.count(elem)){
                rs.insert(elem);
            }
        }
    }
    return rs;
}

unordered_set<int> complement(const unordered_set<int> &a){
    unordered_set<int> rs;
    for(int elem: masks["U"]){
        if(!a.count(elem)){
            rs.insert(elem);
        }
    }
    return rs;
}

unordered_set<int> unify(const unordered_set<int> &a,const unordered_set<int> &b){
    unordered_set<int> rs;
    for(int elem: b){
        rs.insert(elem);
    }
    for(int elem: a){
        rs.insert(elem);
    }
    return rs;
}


unordered_set<int> RQ(vector<string>& query, int s, int e){
    for(int q = s; q <= e; q++){
        if(query[q] == "OR"){
            auto rs1 = RQ(query,s,q-1);
            auto rs2 = RQ(query,q+1,e);
            return unify(rs1,rs2);
        }
    }
    for(int q = s; q <= e; q++){
        if(query[q] == "but"){
            auto rs1 = RQ(query,s,q-1);
            auto rs2 = RQ(query,q+1,e);
            return intersection(rs1,rs2);
        }
    }
    for(int q = s; q <= e; q++){
        if(query[q] == "not"){
            auto rs1 = RQ(query,q+1,q+1);
            return complement(rs1);
        }
    }
    return masks[translate[query[s]]];
}


int main() {
    int a, r, c, q;
    cin >> a >> r >> c >> q;
    vector<ll> cc;
    string s; string s1;
    for(int i = 0; i < a; i++){
        cin >> s >> s1;
        translate[s1] = s;
        masks[s] = {};
    }
    /*
    
    IDEA
    
    10 DIFFERENT ADJECTIVES

    2^10 OVERLAPS MAXIMUM

    EXPRESS INITIAL REGIONS AS BITMASKS

    THEN EVALUATE USING CC
    */
    vector<vector<string> > grid(r + 2, vector<string>(c + 2,"#"));
    int ccs = 0;
    
    
    vector<vector<bool> > vis(r + 2, vector<bool>(c + 2, true));
    for(int i = 1; i <= r; i++){
        for(int j = 1; j <= c; j++){
            cin >> s1;
            if(s1.size() == 1){
                if(s1[0] >= '0' && s1[0] <= '9'){
                    vis[i][j] = false;
                }
            }
            grid[i][j] = s1;
        }
    }

    /*
    CC(i) => TOTAL OF WHAT?
    */
    for(int i = 1; i <= r; i++){
        for(int j = 1; j <= c; j++){
            if(!vis[i][j]){
                ll answer = DFS(i,j,ccs,vis,grid);
                cc.push_back(answer);
                ccs++;
            }
        }
    }
    // for(int i = 1; i <= r; i++){
    //     for(int j = 1; j <= c; j++){
    //         cout << grid[i][j] << sp;
    //     }
    //     cout << nl;
    // }
    // for(int i = 0; i < cc.size(); i++){
    //     cout << i << sp << cc[i]<< nl;
    // }
    masks["U"] = {};
    for(int i = 0; i < ccs; i++){
        masks["U"].insert(i);       
    }
    for(auto &[adj,bm]:masks){
        vector<vector<string> > update(r + 2, vector<string>(c + 2,"."));
        vector<vector<bool> > vis2(r + 2, vector<bool>(c + 2, false));
        for(int i = 1; i <= r; i++){
            for(int j = 1; j <= c; j++){
                if(is_number(grid[i][j])){
                    update[i][j] = grid[i][j];
                } else if(issubstring(adj,grid[i][j])){
                    update[i][j] = "#";
                    vis[i][j] = true;
                } else {
                    update[i][j] = "."; //I CAN MOVE PASTTHESE
                }
            }
        }
        _dfs(0,0,vis2,update);
        // cout << nl;
        for(int i = 1; i <= r; i++){
            for(int j = 1; j <= c; j++){
                if(!vis2[i][j]){
                    paint(i,j,adj,vis2,update);
                }   
            }
        }
        // cout << adj << sp << masks[adj] << nl;
    }
    // for(auto &[adj,bm]:masks){
    //     cout << adj << sp << bm << nl;
    // }

    
    cin.ignore();
    string retval;
    for(int i = 0; i < q; i++){
        vector<string>Q;
        getline(cin,retval);
        // cout << retval << nl;
        retval += " ";
        string kaka = "";
        for(char c: retval){
            if(c == ' '){
                Q.push_back(kaka);
                kaka = "";
            } else {
                kaka += c;
            }
        }
        unordered_set<int> answer = RQ(Q,0,Q.size() - 1);
        // cout << answer << nl;
        ll total = 0;
        for(int elem: answer){
            total += cc[elem];
        }
        cout << total << nl;
    }

}
