vector<int>(V,inf);
V[source] = 0;
priority_queue<pii, vector<pii>, greater<pii> > pq; // pair {weight, node}; add initial node
vector<bool> vis(V, false);
pq.push({0,source});
while(!pq.empty()){
    pii node = pq.top(); pq.pop();
    int d = node.first, u = node.second;
    if(d > dist[u]){
        continue;
    }
    for(auto &[v,w]: adj[u]){
        if(d + w < dist[v]){
            dist[v] = d + w;
            pq.push({dist[v],v});
        }
    }
}