/*
    AVLDict.hpp 
    Copyright (c) 2022 Max Goren
Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#ifndef AVLDICT_HPP
#define AVLDICT_HPP
#include <iostream>
using namespace std;

template <class T, class T2>
class AVLTree {
    private:
        struct node {
            T key;
            T2 value;
            int height;
            node* left;
            node* right;
            node* parent;
            node(T k, T2 v) {
                key = k; value = v; height = 0; left = right = parent = nullptr;
            }
        };
        node* root;
        int N;
        int height(node* h) {
            return (h == nullptr) ? -1:h->height;
        }
        int max(int a, int b) { return (a < b) ? b:a; }
        void left_rotate(node *x) {
            node *y = x->right;
            if (y) {
                x->right = y->left;
                if (y->left) y->left->parent = x;
                y->parent = x->parent;
            }
            if (!x->parent) root = y;
            else if (x == x->parent->left) x->parent->left = y;
            else x->parent->right = y;
            if (y) y->left = x;
            x->parent = y;
            x->height = 1 + max(height(x->left), height(x->right));
            y->height = 1 + max(height(y->left), height(y->right));
        }
  
        void right_rotate(node *x) {
            node *y = x->left;
            if (y) {
                x->left = y->right;
                if (y->right) y->right->parent = x;
                y->parent = x->parent;
            }
            if (!x->parent) root = y;
            else if (x == x->parent->left) x->parent->left = y;
            else x->parent->right = y;
            if (y) y->right = x;
            x->parent = y;
            x->height = 1 + max(height(x->left), height(x->right));
            y->height = 1 + max(height(y->left), height(y->right));
        } 
        int balanceFactor(node* h) {
            return height(h->left) - height(h->right);
        }
        void balance(node* x) {
            while (x && x->parent) {
                node *y = x->parent;
                y->height = 1 + max(height(y->left), height(y->right));
                if (balanceFactor(y) < -1) {
                    if (balanceFactor(y->right) > 0) {
                        right_rotate(y->right);
                    }
                    left_rotate(y);
                } else if (balanceFactor(y) > 1) {
                    if (balanceFactor(y->left) < 0) {
                        left_rotate(y->left);
                    }
                    right_rotate(y);
                }
                x = x->parent;
            }
        }
        void visit(node* h) {
            if (h != nullptr) {
                cout<<h->key<<" ";
                visit(h->left);
                visit(h->right);
            }
        } 
        void transplant(node *u, node* v) {
            if (u->parent == nullptr) {
                root = v;
            } else if (u == u->parent->left) {
                u->parent->left = v;
            } else {
                u->parent->right = v;
            }
            if (v != nullptr) {
                v->parent = u->parent;
            }
        }
        void eraseR(node* h) {
            node* t = h;
            if (h->left == nullptr)
                transplant(h, h->right);
            else if (h->right == nullptr) {
                transplant(h, h->left);
            } else {
                node* y = min(h->right);
                if (y->parent != h) {
                    transplant(y, y->right);
                    y->right = h->right;
                    y->right->parent = y;
                }
                transplant(h, y);
                y->left = h->left;
                y->left->parent = y;
            }
            delete t;
        }
        node* min(node* h) {
            node* x = h;
            while (x->left != nullptr) x = x->left;
            return x;
        }
    public:
        AVLTree() {
            root = nullptr;
            N = 0;
        }
        void insert(T key, T2 value) {
            node* x = root;
            node* p = x;
            while (x) {
                p = x;
                x = (key < x->key) ? x->left:x->right;
            }
            x = new node(key, value);
            if (!p) root = x;
            else if (key < p->key) p->left = x;
            else p->right = x;
            x->parent = p;
            balance(x);
            N++;
        }
        void erase(T key) {
            node *x = root;
            bool found = false;
            while (x != nullptr) {
                if (x->key == key) {
                    found = true;
                    break;
                }
                x = (key < x->key) ? x->left:x->right;
            }
            if (found) {
                eraseR(x);
                balance(x);
                N--;
            }
        }
        void show() {
            visit(root);
            cout<<endl;
        }
        bool contains(T key) {
            node* x = root;
            while (x != nullptr) {
                if (key == x->key)
                    return true;
                x = (key < x->key) ? x->left:x->right;
            }
            return false;
        }
        T2 get(T key) {
            node *x = root;
            while (x != nullptr) {
                if (key == x->key)
                    return x->value;
                x = (key < x->key) ? x->left:x->right;
            }
            return T2();
        }
};

#endif