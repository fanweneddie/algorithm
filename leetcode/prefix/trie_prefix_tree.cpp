/*
Problem: https://leetcode-cn.com/problems/implement-trie-prefix-tree/
*/

class Trie {
public:
    Trie() {
        children.resize(26);
        for (auto &child : children) {
            child = nullptr;
        }
        is_end = false;
    }

    ~Trie() {
        for (auto &child : children) {
            delete child;
        }
    }
    
    void insert(string word) {
        Trie* node = this;
        for (auto ch : word) {
            int index = ch - 'a';
            if (!node->children[index]) {
                node->children[index] = new Trie();
            }
            node = node->children[index];
        }
        node->setEnd();
    }
    
    bool search(string word) {
        Trie* node = this;
        for (auto ch : word) {
            int index = ch - 'a';
            if (!node->children[index]) {
                return false;
            }
            node = node->children[index];
        }
        return node->getIsEnd();
    }
    
    bool startsWith(string prefix) {
        Trie* node = this;
        for (auto ch : prefix) {
            int index = ch - 'a';
            if (!node->children[index]) {
                return false;
            }
            node = node->children[index];
        }
        return true;
    }

    bool getIsEnd() const {
        return is_end;
    }

    void setEnd() {
        is_end = true;
    }

private:
    // 26 children
    vector<Trie*> children;
    // whether this node is the end of a word
    bool is_end;
};

/**
 * Your Trie object will be instantiated and called as such:
 * Trie* obj = new Trie();
 * obj->insert(word);
 * bool param_2 = obj->search(word);
 * bool param_3 = obj->startsWith(prefix);
 */
