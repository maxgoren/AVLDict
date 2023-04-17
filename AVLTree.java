
public class AVLTree<K extends Comparable<K>, V> {
    private class Node {
        K key;
        V value;
        int height;
        Node left;
        Node right;
        Node par;
        Node(K key, V value) {
            this.key = key;
            this.value = value;
        }
    }
    private Node root;
    private int N;
    public AVLTree() {

    }

    public void add(K key, V value) {
        Node x = root;
        Node p = x;
        while (x != null) {
            p = x;
            x = (key.compareTo(x.key) < 0) ? x.left:x.right;
        }
        x = new Node(key, value);
        if (p == null) root = x;
        else if (key.compareTo(p.key) < 0) p.left = x;
        else p.right = x;
        x.par = p;
        balanceAVL(x);
        N++;
    }
    public V get(K key) {
        Node x = root;
        while (x != null) {
            if (key.equals(x.key)) {
                return x.value;
            }
            x = (key.compareTo(x.key) < 0) ? x.left:x.right;
        }
        return null;
    }
    public void erase(K key) {
        Node x = root;
        boolean found = false;
        while (x != null) {
            if (key.equals(x.key)) {
                found = true;
                break;
            }
            x = (key.compareTo(x.key) < 0) ? x.left:x.right;
        }
        if (found) {
            erase(x);
            balanceAVL(x);
            N--;
        }
    }

    public void show() {
        preorder(root);
        System.out.println();
    }

    public int size() {
        return N;
    }

    public boolean isEmpty() {
        return root == null;
    }

    private int height(Node h) { return h == null ? -1:h.height; }
    private int balanceFactor(Node h) {
        return height(h.left) - height(h.right);
    }
    private void leftRotate(Node x) {
        Node y = x.right;
        if (y != null) {
            x.right = y.left;
            if (y.left != null) y.left.par = x;
            y.par = x.par;
        }
        if (x.par == null) root = y;
        else if (x == x.par.left) x.par.left = y;
        else x.par.right = y;
        if (y != null) y.left = x;
        x.par = y;
        x.height = 1 + Math.max(height(x.left), height(x.right));
        y.height = 1 + Math.max(height(y.left), height(y.right));
    }
    private void rightRotate(Node x) {
        Node y = x.left;
        if (y != null) {
            x.left = y.right;
            if (y.right != null) y.right.par = x;
            y.par = x.par;
        }
        if (x.par == null) root = y;
        else if (x == x.par.left) x.par.left = y;
        else x.par.right = y;
        if (y != null) y.right = x;
        x.par = y;
        x.height = 1 + Math.max(height(x.left), height(x.right));
        y.height = 1 + Math.max(height(y.left), height(y.right));
    }
    private void balanceAVL(Node x) {
        while (x != null && x.par != null) {
            Node y = x.par;
            y.height = 1 + Math.max(height(y.left), height(y.right));
            if (balanceFactor(y) < -1) {
                if (balanceFactor(y.right) > 0) {
                    rightRotate(y.right);
                }
                leftRotate(y);
            } else if (balanceFactor(y) > 1) {
                if (balanceFactor(y.left) < 0) {
                    leftRotate(y.left);
                }
                rightRotate(y);
            }
            x = x.par;
        }
    }
    private void preorder(Node x) {
        if (x != null) {
            System.out.print(x.key + " ");
            preorder(x.left);
            preorder(x.right);
        }
    }
    private Node min(Node x) {
        Node y = x;
        while (y.left != null) y = y.left;
        return y;
    }
    private void transplant(Node u, Node v) {
        if (u.par == null) {
            root = v;
        } else if (u == u.par.left) {
            u.par.left = v;
        } else {
            u.par.right = v;
        }
        if (v != null) {
            v.par = u.par;
        }
    }
    private void erase(Node x) {
        if (x.left == null) {
            transplant(x, x.right);
        } else if (x.right == null) { 
            transplant(x, x.left);
        } else {
            Node y = min(x.right);
            if (y.par != x) {
                transplant(y, y.right);
                y.right = x.right;
                y.right.par = y;
            }
            transplant(x, y);
            y.left = x.left;
            y.left.par = y;
        }
    }
}