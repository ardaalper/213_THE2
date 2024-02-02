#include <string>
#include <vector>
#include <iostream>
#include <utility>
#include <algorithm>
using namespace std;

// do not add any other library.
// modify parts as directed by assignment text and comments here.

template <class T>
class BST {
private:
    // Define TreeNode for the second phase (Binary Search Tree)
    /* DO NOT CHANGE */
    struct TreeNode {
        std::string key;
        T data;
        TreeNode* left;
        TreeNode* right;
        TreeNode(const std::string &k, const T& value) : key(k), data(value), left(NULL), right(NULL) {}
        
    };

    TreeNode* root;


public: // Do not change.

    BST();
    ~BST();
    TreeNode* getRoot() { return root; }
    bool isEmpty() { return root == NULL; }

    BST& insert(const std::string key, const T& value);
    bool search(std::string value) const;
    void remove(std::string value);
    BST<T>* merge(BST<T>* bst);
    BST<T>* intersection(BST<T>* bst);
    std::vector<TreeNode> tree2vector(TreeNode* root);
    void print();
    
private:// you may add your own utility member functions here.

    void print(TreeNode* node, std::string indent, bool last, bool isLeftChild); // Do not change.
    void destroyer(TreeNode* node);
    void inserter(TreeNode*& root,TreeNode* node);
    bool searcher(TreeNode* node, std::string key) const;
    void removehelper(TreeNode*& root,string key);
    typename  BST<T>::TreeNode* findmin(TreeNode* node);
    void tree2vectorhelper(TreeNode* root, vector<typename BST<T>::TreeNode>& res);
};

    // Constructor
    template <class T>
    BST<T>::BST() : root(NULL) {}

    // Destructor
    template <class T>
    BST<T>::~BST() {
    /* IMPLEMENT THIS */
        destroyer(root);
    }

    template <class T>
    BST<T>& BST<T>::insert(const string key, const T& value) {
             /* IMPLEMENT THIS */
        TreeNode* newnode=new TreeNode(key,value);
        inserter(root,newnode);
        return *this;
    }
    
    // Search function for BST.
    template <class T>
    bool BST<T>::search(std::string value) const {
     /* IMPLEMENT THIS */
        return searcher(root, value);

    }
    
    // Remove a node from BST for given key. If key not found, do not change anything.
    template <class T>
    void BST<T>::remove(std::string key) {
        /* IMPLEMENT THIS */
        removehelper(root,key);
    }
    
    // A helper function for converting a BST into vector.
    template <class T>
    vector<typename BST<T>::TreeNode> BST<T>::tree2vector(TreeNode* root) {
        vector<TreeNode> result;
        tree2vectorhelper(root,result);
        return result;
    }
    
    template <class T>
    void BST<T>::tree2vectorhelper(TreeNode* root, vector<typename BST<T>::TreeNode>& res) {
        if(root==NULL){
            return;
        }
        else{
            tree2vectorhelper(root->left,res);
            
            TreeNode alpha(root->key,root->data);
            res.push_back(alpha);
            
            tree2vectorhelper(root->right,res);
        }
    }
    
    template <class T>
        BST<T>* BST<T>::merge(BST<T>* bst) {

        vector<TreeNode> result1;
        vector<TreeNode> result2;
        tree2vectorhelper(root, result1);
        bst->tree2vectorhelper(bst->getRoot(), result2);
        BST<T>* answer = new BST<T>();
    
        vector<TreeNode> sortedresult;

        int r1index = 0;
        int r2index = 0;
        int r1size = (int)result1.size();
        int r2size = (int)result2.size();
        
        while (1) {
            if (r1index == r1size && r2index == r2size) {
                // ikisi de bitik
                break;
            } else if (r1index != r1size && r2index == r2size) {
                // r1 dolu,r2 bitik
                while (r1index != r1size) {
                    sortedresult.push_back(result1[r1index]);
                    r1index++;
                }
                break;
            } else if (r1index == r1size && r2index != r2size) {
                // r2 dolu,r1 bitik
                while (r2index != r2size) {
                    sortedresult.push_back(result2[r2index]);
                    r2index++;
                }
                break;
            } 
            else {
                // ikisi de dlou
                if (result1[r1index].key < result2[r2index].key) {
                    sortedresult.push_back(result1[r1index]);
                    r1index++;
                } 
                else if (result1[r1index].key > result2[r2index].key) {
                    sortedresult.push_back(result2[r2index]);
                    r2index++;
                } 
                else {
                    sortedresult.push_back(result1[r1index]);
                    r1index++;
                    r2index++;
                }
            }
        }

        int rssize = (int)sortedresult.size();
        for (int m=0;m<rssize;m++) {
            answer->insert(sortedresult[m].key, sortedresult[m].data);
        }
                


        result1.clear();
        result2.clear();
        sortedresult.clear();
        return answer;
    }
    
    
    template <class T>
    BST<T>* BST<T>::intersection(BST<T>* bst) {
    /* IMPLEMENT THIS */
        vector<TreeNode> result1;
        vector<TreeNode> result2;
        tree2vectorhelper(root, result1);
        bst->tree2vectorhelper(bst->getRoot(), result2);
        BST<T>* answer = new BST<T>();
    
        vector<TreeNode> sortedresult;

        int r1index = 0;
        int r2index = 0;
        int r1size = (int)result1.size();
        int r2size = (int)result2.size();
        
        while (1) {
            if (r1index == r1size && r2index == r2size) {
                // ikisi de bitik
                break;
            } else if (r1index != r1size && r2index == r2size) {
                // r1 dolu,r2 bitik
                while (r1index != r1size) {
                    //sortedresult.push_back(result1[r1index]);
                    r1index++;
                }
                break;
            } else if (r1index == r1size && r2index != r2size) {
                // r2 dolu,r1 bitik
                while (r2index != r2size) {
                    //sortedresult.push_back(result2[r2index]);
                    r2index++;
                }
                break;
            } 
            else {
                // ikisi de dlou
                if (result1[r1index].key < result2[r2index].key) {
                    //sortedresult.push_back(result1[r1index]);
                    r1index++;
                } 
                else if (result1[r1index].key > result2[r2index].key) {
                    //sortedresult.push_back(result2[r2index]);
                    r2index++;
                } 
                else {
                    sortedresult.push_back(result1[r1index]);
                    r1index++;
                    r2index++;
                }
            }
        }

        int rssize = (int)sortedresult.size();
        for (int m=0;m<rssize;m++) {
            answer->insert(sortedresult[m].key, sortedresult[m].data);
        }
                


        result1.clear();
        result2.clear();
        sortedresult.clear();
        return answer;
    }
    
    /* DO NOT CHANGE */
    template <class T>
    void BST<T>::print() {
        print(root, "", true, false);
    
    }
    
    /* DO NOT CHANGE */
    template <class T>
    void BST<T>::print(TreeNode* node, string indent, bool last, bool isLeftChild) {
        if (node != NULL) {
            cout << node->key << endl;
            print(node->left, indent, false, true);
            print(node->right, indent, true, false);
        }
    
    }

//////////////////////////////////////////////////
    template <class T>
        void BST<T>:: destroyer(TreeNode* node){
            if (node == NULL) {
                return;
            }
            else{
                destroyer(node->left);
                destroyer(node->right);
            }
            
            delete node;
        }
    template <class T>
        void BST<T>::inserter(TreeNode*& root, TreeNode* node) {
            if (root == NULL) {
                root = node;
            } else if ((root->key).compare(node->key) > 0) {
                inserter(root->left, node);
            } else if ((root->key).compare(node->key) < 0) {
                inserter(root->right, node);
            }
        }
    template <class T>
    bool BST<T>:: searcher(TreeNode* node, std::string key) const{
        if(node!=NULL && node->data.getMovieName()==key){
            return true;
        }
        else if(node->left!=NULL && node->right!=NULL){//soldan ve sağdan gidiyosa
            return searcher(node->left,key) || searcher(node->right,key) || false;
        }
        else if(node->left==NULL && node->right!=NULL){//sağdan gidiyosa
            return searcher(node->right,key) || false;
        }
        else if(node->left!=NULL && node->right==NULL){//soldan gidiyosa
            return searcher(node->left,key)  || false;
        }
        else{//gitmiyorsa :D
            return false;
        }
    }
    template <class T>
    typename  BST<T>::TreeNode* BST<T>::findmin(TreeNode* node){
       if(node->left==NULL){
           return node;
       }
       else{
           return findmin(node->left);
       }
    }
    
    template <class T>
    void BST<T>::removehelper(TreeNode*& root,string key){
        if(root==NULL) return;
        
        if(root->key==key){
            if(root->left !=NULL && root->right !=NULL){
                root->data=findmin(root->right)->data;
                root->key=findmin(root->right)->key;
                removehelper(root->right,root->key);
            }
            else{
                TreeNode* oldnode = root;
                root=(root->left != NULL)? root->left : root->right;
                delete oldnode;
            }
        }
        else{
            removehelper(root->left,key);
            removehelper(root->right,key);
        }
    }