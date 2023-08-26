#ifndef AVL_HPP
#define AVL_HPP
#include <iostream>
using std::cout;
using std::endl;

template <class T, class T2>
class AVL {
    private:
        struct node {
            T key;
            T2 value;
            int n;
            int height;
            node* left;
            node* right;
            node(T k, T2 val) {
                key = k;
                value = val;
                left = nullptr;
                right = nullptr;
                n = 0;
                height = 0;
            }
        };
        typedef node* link;
        link root;
        T nullKey;
        T2 nullItem;
        int count;
        int height(link);
        int size(link);
        int balanceFactor(link);
        int max(int, int);
        link min(link);
        link max(link);
        link deleteMin(link);
        link putR(link, T, T2);
        link eraseR(link, T);
        link rotL(link);
        link rotR(link);
        link balance(link);
        bool contains(link, T);
        T select(link, int);
        void preorder(link);
        void inorder(link);
        void cleanUp(link);
    public:
        AVL();
        AVL(const AVL& o);
        ~AVL() { 
            clear(); 
        }
        void put(T key, T2 value);
        void erase(T key);
        bool contains(T key);
        T2& get(T key);
        T2 min();
        T2 max();
        T select(int rank);
        void popMin();
        void show();
        void sort();
        bool empty();
        int size();
        void clear();
};

#endif