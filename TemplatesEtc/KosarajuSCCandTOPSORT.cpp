vector<int> DFSBK;
void RPSO(int u, vector<vector<int> > &G, vector<bool> &vis){
    vis[u] = true;
    for(int v: G[u]){
        if(!vis[v]){
            RPSO(v, G, vis);
        }
    }
    DFSBK.push_back(u);
}

void stndrCC(vector<vector<int> > &G, vector<bool> &vis, int node, vector<int> &temp){
    vis[node] = true;
    temp.push_back(node);
    for(int neigh: G[node]){
        if(!vis[neigh]){
            stndrdCC(G, vis, neigh, temp);
        }
    }
}

int main(){
    //Get G and create vis, assume this is 1 graph that is connected not multiple graphs that aren't connected.
    RPSO(0, G, vis);
    reverse(DFSBK.begin(), DFSBK.end()); //TopSort
    vector<vector<int> > SCC;
    //reset vis to all false;
    G_rev = reverse(G);
    for(int u: DFSBK){
        if(!vis[u]){
            vector<int> temp;
            stndrdCC(G_rev, vis, u, temp);
            SCC.push_back(temp);
        }
    }
}
