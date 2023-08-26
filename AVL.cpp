#include <iostream>
#include "AVL.hpp"

using std::cout;
using std::endl;

template <class T, class T2>
AVL<T,T2>::AVL()
{
    root = nullptr;
    count = 0;
}

template <class T, class T2>
AVL<T,T2>::AVL(const AVL& o)
{
    root = o.root;
    count = o.count;
}

template <class T, class T2>
int AVL<T, T2>::height(link h)
{
    return (h == nullptr) ? -1 : h->height;
}

template <class T, class T2>
int AVL<T, T2>::size(link h)
{
    if (h == nullptr)
        return 0;
    return h->n;
}

template <class T, class T2>
typename AVL<T,T2>::link AVL<T, T2>::rotL(link h)
{
    link x = h->right;
    h->right = x->left;
    x->left = h;
    h->height = 1 + max(height(h->left), height(h->right));
    x->height = 1 + max(height(x->left), height(x->right));
    h->n = 1 + size(h->left) + size(h->right);
    x->n = 1 + size(x->left) + size(x->right);
    return x;
}

template <class T, class T2>
typename AVL<T,T2>::link AVL<T, T2>::rotR(link h)
{
    link x = h->left;
    h->left = x->right;
    x->right = h;
    h->height = 1 + max(height(h->left), height(h->right));
    x->height = 1 + max(height(x->left), height(x->right));
    h->n = 1 + size(h->left) + size(h->right);
    x->n = 1 + size(x->left) + size(x->right);
    return x;
}

template <class T, class T2>
int AVL<T, T2>::balanceFactor(link h)
{
        return height(h->left) - height(h->right);
}

template <class T, class T2>
typename AVL<T,T2>::link AVL<T, T2>::balance(link h)
{
        if (balanceFactor(h) < -1)
        {
            if (balanceFactor(h->right) > 0)
            {
                h->right = rotR(h->right);
            }
            h = rotL(h);
        }
        else if (balanceFactor(h) > 1)
        {
            if (balanceFactor(h->left) < 0)
            {
                h->left = rotL(h->left);
            }
            h = rotR(h);
        }
        return h;
}

template <class T, class T2>
typename AVL<T,T2>::link AVL<T, T2>::putR(link h, T key, T2 value)
{
        if (h == nullptr) {
            count++;
            return new node(key, value);
        }
        if (key == h->key) {
            h->value = value;
            return h;
        } else if (key < h->key) {
            h->left = putR(h->left, key, value);
        } else {
            h->right = putR(h->right, key, value);
        }
        h->height = 1 + max(height(h->left), height(h->right));
        h->n = 1 + size(h->left) + size(h->right);
        return balance(h);
}

template <class T, class T2>
bool AVL<T, T2>::contains(link h, T key)
{
        if (h == nullptr)
        {
            return false;
        }
        if (key == h->key)
            return true;
        if (key < h->key)
            return contains(h->left, key);
        else
            return contains(h->right, key);
}

template <class T, class T2>
typename AVL<T,T2>::link AVL<T, T2>::min(link h)
{
        if (h->left == nullptr)
            return h;
        return min(h->left);
}

template <class T, class T2>
typename AVL<T,T2>::link AVL<T, T2>::max(link h)
{
        if (h->right == nullptr)
            return h;
        return max(h->right);
}

template <class T, class T2>
int AVL<T, T2>::max(int a, int b)
{
        return (a > b) ? a : b;
}

template <class T, class T2>
typename AVL<T,T2>::link AVL<T, T2>::deleteMin(link h)
{
        if (h->left == nullptr)
        {
            return h->right;
        }
        h->left = deleteMin(h->left);
        return h;
}

template <class T, class T2>
typename AVL<T,T2>::link AVL<T, T2>::eraseR(link h, T key)
{
        if (h == nullptr)
            return nullptr;
        if (key < h->key)
        {
            h->left = eraseR(h->left, key);
        }
        else if (key > h->key)
        {
            h->right = eraseR(h->right, key);
        }
        else
        {
            link t = h;
            count--;
            if (h->left == nullptr)
                return h->right;
            if (h->right == nullptr)
                return h->left;
            h = min(t->right);
            h->right = deleteMin(t->right);
            h->left = t->left;
            delete t;
        }
        return balance(h);
}

template <class T, class T2>
T AVL<T, T2>::select(link h, int rank)
{
        if (h == nullptr)
            return nullKey;
        int lsize = size(h->left);
        if (lsize > rank)
            return select(h->left, rank);
        else if (lsize < rank)
            return select(h->right, rank - lsize - 1);
        else
            return h->key;
}

template <class T, class T2>
void AVL<T, T2>::preorder(link h)
{
        if (h == nullptr)
            return;
        cout << h->key << " ";
        preorder(h->left);
        preorder(h->right);
}

template <class T, class T2>
void AVL<T, T2>::inorder(link h)
{
        if (h != nullptr)
        {
            inorder(h->left);
            cout << h->key << " ";
            inorder(h->right);
        }
}

template <class T, class T2>
void AVL<T, T2>::cleanUp(link h)
{
        if (h != nullptr)
        {
            cleanUp(h->left);
            cleanUp(h->right);
            delete h;
        }
}

template <class T, class T2>
void AVL<T, T2>::put(T key, T2 value)
{
        root = putR(root, key, value);
}

template <class T, class T2>
void AVL<T, T2>::erase(T key)
{
        root = eraseR(root, key);
}

template <class T, class T2>
bool AVL<T, T2>::contains(T key)
{
        return contains(root, key);
}

template <class T, class T2>
T2& AVL<T, T2>::get(T key)
{
        link x = root;
        while (x != nullptr)
        {
            if (key == x->key)
                return x->value;
            x = (key < x->key) ? x->left : x->right;
        }
        return nullItem;
}

template <class T, class T2>
T2 AVL<T, T2>::min()
{
     return min(root)->value;
}

template <class T, class T2>
T2 AVL<T, T2>::max()
{
        return max(root)->value;
}

template <class T, class T2>
T AVL<T, T2>::select(int rank)
{
        return select(root, rank);
}

template <class T, class T2>
void AVL<T, T2>::popMin()
{
        if (empty())
            return;
        root = deleteMin(root);
        count--;
}

template <class T, class T2>
void AVL<T, T2>::show()
{
        if (empty())
            return;
        preorder(root);
        cout << endl;
}


template <class T, class T2>
void AVL<T, T2>::sort()
{
        if (empty())
            return;
        inorder(root);
        cout << endl;
}

template <class T, class T2>
bool AVL<T, T2>::empty()
{
        return root == nullptr;
}


template <class T, class T2>
int AVL<T, T2>::size()
{
        return count;
}

template <class T, class T2>
void AVL<T, T2>::clear() 
{ 
    cleanUp(root); 
}