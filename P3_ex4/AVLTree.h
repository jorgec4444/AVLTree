/* 
 * File:   AVLTree.h
 * Author: JORGEC
 *
 * Created on 24 de mayo de 2020, 12:38
 */

#ifndef AVLTREE_H
#define AVLTREE_H

#include <vector>
#include "Position.h"
#include <stdexcept>

using namespace std;

template <class K, class V>
class AVLTree {
    
public:
    /* Constructors i Destructors */
    // AVLTree constructor
    AVLTree() {
        root = nullptr; // Set root a nullptr
        cout << "AVLTree buit creat" << endl;
    }
    
    // AVLTree constructor còpia
    AVLTree(const AVLTree& orig) {
        root = new Position<K,V>(*orig.root); // Set root al node copiat
        cout << "AVLTree copiat!" << endl;
    }
    
    // AVLTree destructor
    virtual ~AVLTree() {
        delete root; // Trucada al destructor de root
        cout << "AVLTree eliminat!" << endl;
    }
    
    /* Consultors */

    bool isEmpty() const {
        return root == nullptr; // Comprova si el node root és nullptr
    }

    Position<K,V>* getRoot() const {
        return root;
    }
    
    // Mètode per calcular el size del AVLTree
    int size() const {
        if (root != nullptr)
            return 1 + sizeRec(root->left()) + sizeRec(root->right());
        else
            return 0;
    }
    
    // Mètode per calcular la height del AVLTree
    int height() {
        if (root == nullptr) return 0;
        
        int leftheight = height(root->left());
        int rightheight = height(root->right());
        
        return 1 + max(leftheight, rightheight);
    }
    
    // Insertar un element al AVLTree
    virtual Position<K, V>* insert(const K& key, const V& value) {
        Position<K,V>* nt = new Position<K,V>(key,value);    
        
        if (isEmpty())
            root = nt;
        else if (contains(key)) {
            nt = _search(key);
            nt->addValue(value);
        }
        else {
            Position<K,V>* temp = root;
            
            while (temp->hasLeft() && temp->hasRight()
                    || (temp->hasLeft() && !temp->hasRight() && key < temp->getKey())
                    || (!temp->hasLeft() && temp->hasRight() && key > temp->getKey()))
            {
                if (key < temp->getKey())
                    temp = temp->left();
                else
                    temp = temp->right();
            } 

            if (key < temp->getKey())
                temp->setLeft(nt);
            else
                temp->setRight(nt);
            
            nt->setParent(temp);
            nt->addValue(value);
        }
        return nt;
    }
    
    // Comprovar si el AVLTree conté la key especificada
    bool contains(const K& key) const {
        Position<K,V>* temp = root;
        
        if (temp->getKey() == key) return true;

        while (temp->hasLeft() || temp->hasRight()) {
            if (temp->getKey() == key)
                return true;
            if (key < temp->getKey()) {
                if (!temp->hasLeft()) return false;
                else temp = temp->left();
            }
            else {
                if (!temp->hasRight()) return false;
                else temp = temp->right();
            }
            }
            if (temp->getKey() == key) return true;
            return false;
        }
    
    // Retorna un vector de values de la key especificada
    vector<V> getValues(const K& key) const {
        if (!contains(key)) 
            throw out_of_range("La key de la qual volem extreure el vector no existeix.");
        else {
            Position<K,V>* pos;
            pos = _search(key);
            return pos->getValues();
        }
    }
    
    // Printeja el AVLTree en preordre
    void printPreOrder(const Position<K, V> *node = nullptr) const {
        cout << "Preordre = {" << root->getKey() << ",";
                
        if (root->hasLeft())
            showPreorder(root->left());

        if (root->hasRight())
            showPreorder(root->right());
            
            cout << "}" << endl;
        }
    
    // Printeja el AVLTree en postordre
    void printPostOrder(const Position<K, V> *node = nullptr) const {
        cout << "Postordre = {";
        if (root != nullptr) {
            showPostorder(root->left());
            showPostorder(root->right());
            cout << root->getKey() << "}" << endl;
        }
    }
    
    // Printeja el BSTree en postordre
    void printInorder() {
        int cnt = 0;
        if (root != nullptr) {
            cout << "Inordre = { ";
            showInorder(root->left(),cnt);
            cout << root->getKey() << "," << endl;
            showInorder(root->right(),cnt);
            cout << " }" << endl;
        }
    }
    
    // Comprova si dos AVLTree són iguals
    bool identicalTree(const AVLTree<K, V>& other) const {
        if (size() != other.size())
            return false;
        else {
            return aux_identicalTree(getRoot(), other.getRoot());
        }
    }
    
    // Mètode auxiliar per comprovar si dos AVLTree són iguals
    bool aux_identicalTree(Position<K,V>* a, Position<K,V>* b) const {
        if (a == nullptr && b == nullptr) return true;
        else if (a == nullptr && b != nullptr) return false;
        else if (a != nullptr && b == nullptr) return false;
        else {
            if (a->operator ==(*b) && aux_identicalTree(a->left(),b->left()) 
                && aux_identicalTree(a->right(), b->right()))
                return true;
            else
                return false;
        }
    }
    
    // Mètode per trobar una key que pot estar al AVLtree
    Position<K, V>* _search(const K& key) const {
        Position<K,V>* temp = root;
            
        if (temp->getKey() == key){
            return temp;
        } 
        else {
            while (temp->hasLeft() || temp->hasRight()) {
                if (temp->getKey() == key){
                    return temp;
                }
                else if (key < temp->getKey()){
                    if (!temp->hasLeft()){
                        cout << "Node not found" << endl;
                        return nullptr;
                    }
                    else {
                        temp = temp->left();
                        return aux_search(temp,key);
                    }
                }
                else {
                    if (!temp->hasRight()){
                        cout << "Node not found" << endl;
                        return nullptr;
                    }
                    else {
                        temp = temp->right();
                        return aux_search(temp,key);
                    }
                }
            }
        }
        if (temp->getKey() == key){
            return temp;
        }
        return nullptr;
    }
    
    // Mètode auxiliar per trobar la key al AVLTree
    Position<K, V>* aux_search(Position<K,V>* pos, const K& key) const {
        if (pos->getKey() == key){
            return pos;
        }
        else {
            while (pos->hasLeft() || pos->hasRight()) {
                if (pos->getKey() == key){
                    return pos;
                }
                else if (key < pos->getKey()){
                    if (!pos->hasLeft()){
                        cout << "Node not found" << endl;
                        return nullptr;
                    }
                    else {
                        pos = pos->left();
                        return aux_search(pos,key);
                    }
                }
                else {
                    if (!pos->hasRight()){
                        cout << "Node not found" << endl;
                        return nullptr;
                    }
                    else {
                        pos = pos->right();
                        return aux_search(pos,key);
                    }
                }
            }
        }
        if (pos->getKey() == key){
           return pos;
        }
        return nullptr;
    }


    /* Modificadors */
    
    // Mètode per balancejar el AVLTree amb rotacions(L,R,LR...)
    void balance() {
        if (root->hasLeft() && root->hasRight()) {
            aux_balance(root->left());
            aux_balance(root->right());
        } else if (root->hasLeft() && !root->hasRight()) {
            aux_balance(root->left());
        } else if (!root->hasLeft() && root->hasRight()) {
            aux_balance(root->right());
        }
        
        int bal = root->getBal();
        
        if (bal < -1 && root->left()->getBal() < 0) {
            Position<K,V>* helper = nullptr;
            if (root->left()->hasRight()) {
                helper = root->left()->right();
            }
            root->left()->setRight(root);
            root->setParent(root->left());
            root->left()->setLeft(root->left()->left());
            root->left()->left()->setParent(root->left());
            root = root->left();
            root->right()->clearLeft();
            if (helper != nullptr) root->right()->setLeft(helper);
            cout << "Balancejat a la dreta" << endl;
        } else if (bal > 1 && root->right()->getBal() > 0) {
            Position<K,V>* helper = nullptr;
            if (root->right()->hasLeft()) {
                helper = root->right()->left();
            }
            
            root->right()->setLeft(root);
            root = root->right();
            root->left()->clearRight();
            if (helper != nullptr) root->left()->setRight(helper);
            cout << "Balancejat a l'esquerra" << endl;
        } else if (bal < -1 && root->left()->getBal() > 0) {
            root->left()->right()->setLeft(root->left());
            root->setLeft(root->left()->right());
            root->left()->left()->clearRight();
            cout << "Fill balancejat a l'esquerra" << endl;
            root->left()->setRight(root);
            root->setParent(root->left());
            root->left()->setLeft(root->left()->left());
            root->left()->left()->setParent(root->left());
            root = root->left();
            root->right()->clearLeft();
            root->right()->clearRight();
            cout << "Pare balancejat a la dreta" << endl;
        } else if (bal > 1 && root->right()->getBal() < 0) {
            root->right()->left()->setRight(root->right());
            root->setRight(root->right()->left());
            root->right()->right()->clearLeft();
            cout << "Fill balancejat a la dreta" << endl;
            root->right()->setLeft(root);
            root->setParent(root->right());
            root->right()->setRight(root->right()->right());
            root->right()->right()->setParent(root->right());
            root = root->right();
            root->left()->clearRight();
            root->left()->clearLeft();
            cout << "Pare balancejat a l'esquerra" << endl;
        }
    }
    
protected:
    Position<K,V>* root;
    
private:
    
    // Mètode auxiliar per balancejar el AVLTree
    void aux_balance(Position<K,V>* p) {
        if (p->hasLeft() && p->hasRight()) {
            aux_balance(p->left());
            aux_balance(p->right());
        } 
        else if (p->hasLeft() && !p->hasRight()) aux_balance(p->left());
        else if (!p->hasLeft() && p->hasRight()) aux_balance(p->right());
        
        else {
            int bal = p->getBal();

            if (bal < -1 && p->left()->getBal() < 0) {//
                Position<K,V>* helper = nullptr;
                if (p->left()->hasRight()) {
                    helper = p->left()->right();
                }
                p->parent()->setLeft(p->left());
                p->left()->setRight(p);
                p->clearLeft();
                if (helper != nullptr) p->right()->setLeft(helper);
                cout << "Balancejat a la dreta" << endl;
            } else if (bal > 1 && p->right()->getBal() > 0) {
                Position<K,V>* helper = nullptr;
                if (p->right()->hasLeft()) {
                    helper = p->right()->left();
                }
                p->parent()->setRight(p->right());
                p->right()->setLeft(p);
                p->clearRight();
                if (helper != nullptr) p->left()->setRight(helper);
                cout << "Balancejat a l'esquerra" << endl;
            } else if (bal < -1 && p->left()->getBal() > 0) {
                p->left()->right()->setLeft(p->left());
                p->setLeft(p->left()->right());
                p->left()->left()->clearRight();
                cout << "Fill balancejat a l'esquerra" << endl;
                p->parent()->setLeft(p->left());
                p->left()->setRight(p);
                p->clearLeft();
                p->clearRight();
                cout << "Pare balancejat a la dreta" << endl;
            } else if (bal > 1 && p->right()->getBal() < 0) {
                p->right()->left()->setRight(p->right());
                p->setRight(p->right()->left());
                p->right()->right()->clearLeft();
                cout << "Fill balancejat a la dreta" << endl;
                p->parent()->setRight(p->right());
                p->right()->setLeft(p);
                p->clearLeft();
                p->clearRight();
                cout << "Pare balancejat a l'esquerra" << endl;
            }
        }
    }
    
    // Mètode auxiliar per retornar el size
    int sizeRec(Position<K,V>* p) const {
        if (p != nullptr)
            return 1 + sizeRec(p->left()) + sizeRec(p->right());
    }
    
    // Mètode auxiliar per printejar el AVLTree en preordre
    void showPreorder(Position<K,V>* p) const {
        cout << p->getKey() << ",";
                
        if (p->hasLeft())
            showPreorder(p->left());
        
        if (p->hasRight())
            showPreorder(p->right());
    }
    
    // Mètode auxiliar per printejar el AVLTree en postordre
    void showPostorder(Position<K,V>* p) const {
        if (p != nullptr) {
            showPostorder(p->left());
            showPostorder(p->right());
            cout << p->getKey() << ",";
        }
    }
    
    // Mètode auxiliar per printejar el BSTree en inordre
    void showInorder(Position<K,V>* p, int &cnt) const {
        if (cnt < 40) {
            if (p != nullptr) {
                showInorder(p->left(),cnt);
                cout << p->getKey() << ",";
                cnt++;
                showInorder(p->right(),cnt);
            }
        }
        else {
            char opt;
            cout << "\nVols contiunuar mostrant l'arbre?(S/N)" << endl;
            cin >> opt;
            if (opt == 's' || opt == 'S') {
                cnt = 0;
                showInorder(p,cnt);
            }
            else if (opt == 'n' || opt == 'N') {
                cout << "Sortint del Inorder..." << endl;
                exit(0);
            }
        }
    }
    
    // Mètode auxiliar per retornar l'alçada del AVLTree
    int height(Position<K,V>* p) const {
        if (p == nullptr) return 0;
        else {
            int leftheight = height(p->left());
            int rightheight = height(p->right());

            return 1 + max(leftheight, rightheight);
        }
    }
};
#endif /* AVLTREE_H */

