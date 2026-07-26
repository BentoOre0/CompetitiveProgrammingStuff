sort(edgelist.begin(), edgelist.end(), [&](const auto &a, const auto &b){
    return get<2>(a) < get<2>(b);
});

UnionFind UF = UnionFind(N);
vector<vector<pll> > adj(N);
int total = 0;

for(int i = 0; i < edgelist.size(); i++){
    auto &[u, v, w] = edgelist[i];
    if(UF.find(u) != UF.find(v)){
        UF.unify(u, v);
        total += w;
    }
}