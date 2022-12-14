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
#include <memory>
using namespace std;

template <class K, class V>
class Dict {
    private:
        struct node;
        typedef shared_ptr<node> link;
        struct node {
            K key;
            V value;
            int height;
            link left;
            link right;
            node(K k, V v) {
                key = k; value = v;
                height = 0;
                left = right = nullptr;
            }
        };
        link head;
        int count;
        int height(link h) { return (h == nullptr) ? -1:h->height; }
        int bf(link h) { return height(h->left) - height(h->right); }
        int heightAdjust(link h) {
            return 1 + max(height(h->left), height(h->right));
        }
        link rotL(link h) {
            link x = h->right; h->right = x->left; x->left = h;
            h->height = heightAdjust(h);
            x->height = heightAdjust(x);
            return x;
        }
        link rotR(link h) {
            link x = h->left; h->left = x->right; x->right = h;
            h->height = heightAdjust(h);
            x->height = heightAdjust(x);
            return x;
        }
        link balance(link h) {
            if (bf(h) < -1) {
                if (bf(h->right) > 0) {
                    h->right = rotR(h->right);
                }
                h = rotL(h);
            } else if (bf(h) > 1) {
                if (bf(h->left) < 0) {
                    h->left = rotL(h->left);
                }
                h = rotR(h);
            }
            return h;
        }
        link put(link h, K key, V val) {
            if (h == nullptr) 
                return make_shared<node>(key, val);
            if (key < h->key) h->left = put(h->left, key, val);
            else h->right = put(h->right, key, val);
            h->height = heightAdjust(h);
            return balance(h);
        }
        link get(link h, K key) {
            if (h == nullptr || key == h->key)
                return h;
            if (key < h->key) return get(h->left, key);
            else return get(h->right, key);
        }
        link getMin(link h) {
            if (h == nullptr || h->left == nullptr)
                return h;
            return getMin(h->left);
        }
        link removeMin(link h) {
            if (h->left == nullptr)
                return h->right;
            h->left = removeMin(h->left);
            h->height = heightAdjust(h);
            return h;
        }
        link remove(link h, K key) {
            if (h == nullptr)
                return h;
            if (key < h->key) {
                h->left = remove(h->left, key);
            } else if (key > h->key) {
                h->right = remove(h->right, key);
            } else {
                if (h->left == nullptr) {
                    return h->right;
                } else if (h->right == nullptr) {
                    return h->left;
                } else {
                    link y = h;
                    h = getMin(y->right);
                    h->right = removeMin(y->right);
                    h->left = y->left;
                }
            }
            h->height = heightAdjust(h);
            return balance(h);
        }
        void preorder(link h) {
            if (h != nullptr) {
                cout<<h->key<<" ";
                preorder(h->left);
                preorder(h->right);
            }
        }
    public:
        Dict() {
            head = nullptr;
        }
        void put(K key, V value) {
            head = put(head, key, value);
            count++;
        }
        V get(K key) {
            link x = get(head, key);
            if (x != nullptr)
                return x->value;
            return -1;
        }
        void remove(K key) {
            head = remove(head, key);
            count--;
        }
        int size() const { return count; }
        bool empty() const { return head == nullptr; }
        void show() {
            preorder(head);
            cout<<endl;
        }
};

#endif
