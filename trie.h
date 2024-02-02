#include <iostream>
#include <string>
#include <vector>
#include <utility>
using namespace std;


template <class T>
class Trie {    
private:
    // Define TrieNode for the first phase (Trie)
    /* DO NOT CHANGE */
    struct TrieNode {
        static const int ALPHABET_SIZE = 128;
        TrieNode* children[ALPHABET_SIZE];
        char keyChar;
        bool isEndOfKey;
        T* data;

        TrieNode(char c) : keyChar(c), isEndOfKey(false), data(NULL) {

                for (int i = 0; i< ALPHABET_SIZE; i++) {
                children[i] = NULL;
                
            }
            
            }
    };

    TrieNode* root;

public: // Do not change.

    Trie(); 
    ~Trie();
    
    Trie& insert(const string& username); 
    void remove(std::string username);
    T* search(std::string username); 
    void findStartingWith(std::string prefix, std::vector<T*> &results); 
    void wildcardSearch(const std::string &wildcardKey, std::vector<T*> &results); 
    void print(); 

private: // you may add your own utility member functions here.
    void print(const std::string& primaryKey); // Do not change this line.
    void printTrie(TrieNode* node, const std::string& currentKey); // Do not change this line.
    void deleteTrieNode(TrieNode* node);
    void startHelper(TrieNode* node, vector<T*> &results);
    void wildcardSearchHelper(const std::string &wildcardKey, std::vector<T*> &results, int currindex, TrieNode* node);
};
/* DO NOT CHANGE */
template <class T>
Trie<T>::Trie() : root(new TrieNode('\0')) {}

template <class T>
Trie<T>::~Trie() {
    /* IMPLEMENT THIS */
    deleteTrieNode(root);
}

template <class T>
Trie<T>& Trie<T>::insert(const string& key) {
    /* IMPLEMENT THIS */
    int flag;
    char current;
    TrieNode* currentNode=root;

    if(root==NULL){
        root=new TrieNode('\0');
    }

    
    
    for(int i=0;i<key.length();i++){
        current=key[i];
        flag=0;
        
        for(int j=0; j<128; j++){
            if(currentNode->children[j]!=NULL){
                if(currentNode->children[j]->keyChar==current){
                    flag=1;
                    break;
                }
            }
        }
        
        if(flag==0){//eşleşme bulamadık, yeni node ekliyoruz
            currentNode->children[current] = new TrieNode(current);
        }
        
        currentNode=currentNode->children[current];
    }
    
    currentNode->isEndOfKey=true;

    currentNode->data = new T(key);
    
    return *this;
}



template <class T>
T* Trie<T>::search(std::string username) {
    /* IMPLEMENT THIS */
    
    char currentchar;
    TrieNode* currentnode = root;
    
    if(currentnode==NULL){
        return NULL;
    }
    
    for(int i=0;i<username.length();i++){
        currentchar=username[i];
        
        if(currentnode->children[currentchar]!=NULL){
            currentnode=currentnode->children[currentchar];
        }
        else{
            return NULL;
        }
    }
    
    if (currentnode->isEndOfKey) {
        return currentnode->data;
    }
    else{
        return NULL;
    }


}

template <class T>
void Trie<T>::remove(std::string username) {

    
    char currentchar;
    TrieNode* currentnode = root;
    
    if(currentnode==NULL){
        return;
    }
    
    for(int i=0;i<username.length();i++){
        currentchar=username[i];
        
        if(currentnode->children[currentchar]!=NULL){
            currentnode=currentnode->children[currentchar];
        }
        else{
            return;
        }
    }
    
    if (currentnode->isEndOfKey) {
        currentnode->isEndOfKey=false;
    }
    else{
        return;
    }
}


template <class T>
void Trie<T>::findStartingWith(string prefix, vector<T*> &results) {
    TrieNode* current = root;
    char c;
    int flag=1;

    for(int i=0;i<prefix.length();i++){
        c=prefix[i];
        if (current->children[c]==NULL) {
            flag=0;
        }
        else{
            current = current->children[c];
        }
    }
    if(flag){//devamında her yerde travers et
        startHelper(current, results);
    }
}

template <class T>
void Trie<T>::startHelper(TrieNode* node,  vector<T*> &results) {
    if (node!=NULL){
        for (int i=0; i<128; i++) {
            startHelper(node->children[i], results);
        }
        if (node->isEndOfKey==true) {
            results.push_back(node->data);
        }
    }
    
}

template <class T>
void Trie<T>::wildcardSearch(const std::string &wildcardKey, std::vector<T*> &results) {
    wildcardSearchHelper(wildcardKey,results,0 ,root);
}
template <class T>
void Trie<T>::wildcardSearchHelper(const std::string &wildcardKey, std::vector<T*> &results,int currindex, TrieNode* node) {
    if (node!=NULL){
        if (currindex == wildcardKey.size() && node->isEndOfKey==true){
            results.push_back(node->data);
        }
        else if (wildcardKey[currindex] == '?') {
            for (int i=0;i<128;i++){
                wildcardSearchHelper(wildcardKey,results ,currindex+1 ,node->children[i]);
            }
        } 
        else if (wildcardKey[currindex] == '*') {
            for (int i=0;i<128;i++){
                wildcardSearchHelper(wildcardKey,results,currindex,node->children[i]);
            }
            wildcardSearchHelper(wildcardKey, results, currindex+1, node); 
        } 
        else {
            wildcardSearchHelper(wildcardKey,results, currindex+1, node->children[wildcardKey[currindex]]);
        }
    }
}

/* DO NOT CHANGE */
template<class T>
void Trie<T>::print() {
    print("");
}
/* DO NOT CHANGE */
template <class T>
void Trie<T>::print(const std::string& primaryKey) {
    if (primaryKey.empty()) {
        // Print the entire tree.
        printTrie(root, "");
    } else {
        // Print specific keys.
        TrieNode* primaryNode = root;
        for (int i = 0; i < primaryKey.length(); i++) {
            
            int index = primaryKey[i];
            if (!primaryNode->children[index]) {
                std::cout << "{}" << std::endl; // Primary key not found, nothing to print.
                return ;
            }
            primaryNode = primaryNode->children[index];
        }

        }
    }
/* DO NOT CHANGE */
template <class T>
void Trie<T>::printTrie(TrieNode* node, const std::string& currentKey) {
    if (!node) {
        return;
    }
    if (node->isEndOfKey) {
        std::cout << currentKey <<std::endl;
        std::cout << "Watched Movies:" << std::endl;
        if(node->data) {
            node->data->printMovies();
        }
    }
    for (int i = 0; i < 128; ++i) {
        if (node->children[i]) {
            printTrie(node->children[i], currentKey + static_cast<char>(i));
        }
    }
}
/////////////////////////////////////////////////////////////////
template <class T>
void Trie<T>::deleteTrieNode(TrieNode* node) {
    if (node==NULL) return;
    
    for (int i = 0; i < 128; i++) {
        if (node->children[i]!=NULL) {
            deleteTrieNode(node->children[i]);
        }
    }
    
    delete node->data;
    delete node;
    
}
