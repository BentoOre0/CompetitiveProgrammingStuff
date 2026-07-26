struct Trie{

    /*
    Notes
    checking 0th character on string
    Let idx 0 be the empty string.
    1 indexed :(
    
    */
    private:
        bool isvalidword;
        vector<Trie*> childlist;
    public:
        Trie(){
            isvalidword = false;
            childlist = vector<Trie*>(26,nullptr);
        }
        void insertword(string word, int index_start, int index_end){
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

