class UnionFind {
  private:
        int sz;
        vector<int> id;
        vector<int> ht;

  public:
        UnionFind(int size){
            sz = size;
            id.resize(size);
            ht.resize(size);
            for(int k = 0; k < sz; k++){
                id[k] = k;
                ht[k] = 0;
            }
        }

    int find(int i){
        int ptr = i;
        while(id[ptr] != ptr) {
            id[ptr] = id[id[ptr]];
            ptr = id[ptr];
        }
        return ptr;
    }
   
    void join(int i, int j){
        int ri = find(i), rj = find(j);
        if(ri == rj){
            return;
        }
        if(ht[rj] > ht[ri]){
            id[ri] = rj;
        } else if(ht[ri] > ht[rj]){
            id[rj] = ri;
        } else {
            id[ri] = rj;
            ht[rj]++;
        }
    }
};