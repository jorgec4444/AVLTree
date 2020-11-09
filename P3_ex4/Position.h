/* 
 * File:   Position.h
 * Author: JORGEC
 *
 * Created on 24 de mayo de 2020, 12:39
 */

#ifndef POSITION_H
#define POSITION_H
#include <vector>
#include <iostream>

using namespace std;

template <class K, class V>
class Position {
    public:
        Position(const K key, const V tuple) {
            pKey = key;
            pParent = nullptr;
            pLeft = nullptr;
            pRight = nullptr;
            values.push_back(tuple);
        }
        
        Position(const Position<K, V>& orig) {
            pKey = orig.pKey;
            values = orig.getValues();
            
            if (orig.hasLeft()) {
                pLeft = new Position<K,V>(*orig.left());
            } else pLeft = nullptr;
        
            if (orig.hasRight()) {
                pRight = new Position<K,V>(*orig.right());
            } else pRight = nullptr;
        
            cout << "Node copiat!" << endl;
        }
        
        virtual ~Position() {
            if (hasLeft() && hasRight()) {
                delete pLeft;
                delete pRight;
            }else if (hasLeft() && !hasRight())
                delete pLeft;
            else if (!hasLeft() && hasRight())
                delete pRight;
            //cout << "Node " << pKey << " eliminat." << endl;
        }
        
        // Returns depth (num ancestres)
        int depth() const {
            int depth ;
            if (isRoot())
                return 0;
            else {
                depth = pParent->depth() + 1;
            }
            return depth;
        }
        
        // Retorna l'alçada del node
        int height() const {
            if (isLeaf()) return 1;
            else {
                Position<K,V>* left = pLeft;
                Position<K,V>* right = pRight;
                int leftheight = height(pLeft);
                int rightheight = height(pRight);
                
                return 1 + max(leftheight, rightheight);
            }
        }
        
        // Mètode auxiliar per retornar l'alçada del node
        int height(Position<K,V>* p) const {
            if (p == nullptr) return 0;
            else {
                int leftheight = height(p->left());
                int rightheight = height(p->right());

                return 1 + max(leftheight, rightheight);
            }
        }

        // Retorna la key del position
        const K& getKey() const {
            return pKey;
        }
        
        // Retorna el vector values del position actual
        vector<V> getValues() const {
            return values;
        }
        
        // Afegir un value al vector values del position actual
        void addValue(const V& value) {
            values.push_back(value);
        } 
        
        // Comprova si dos positions són iguals
        bool operator==(const Position<K, V>& other) const {
            if (other.getKey() == pKey) {
                if (values.size() == other.getValues().size()) {
                    if (values == other.getValues())
                        return true;
                }
                else return false;
            }
            else return false;
        }
        
        /*Setters*/
        
        // Set nou element
        void setElement(const K& data) {
            pKey = data;
        }
        
        // Set nou parent
        void setParent(Position<K, V>* parent) {
            pParent = parent;
        }
        
        // Set nou left
        void setLeft(Position<K, V>* left) {
            pLeft = left;
            pLeft->setParent(pParent);
        }
        
        // Set nou right
        void setRight(Position<K, V>* right) {
            pRight = right;
            pRight->setParent(pParent);
        }
        
        /*Consultors*/
        
        // Retorna el node pare
        Position<K, V>* parent() const {
            return pParent;
        }
        
       // Retorna el node left
        Position<K, V>* left() const {
            return pLeft;
        }
        
        // Retorna el node right
        Position<K, V>* right() const {
            return pRight;
        }
        
        // Retorna si el node té parent 
        bool isRoot() const {
            return (pParent == nullptr);
        }
        
        // Retorna si el node no té left o right
        bool isLeaf() const {
            return ((!hasRight()) && (!hasLeft()));
        }
        
        // Retorna si el node té pare
        bool hasParent() const {
            return (pParent != nullptr);
        }
        
        // Retorna si el node té right
        bool hasRight() const {
            return (pRight != nullptr);
        }
    
        // Retorna si el node té left
        bool hasLeft() const {
            return (pLeft != nullptr);
        }
        
        void clearLeft() {
            pLeft = nullptr;
        }

        void clearRight() {
            pRight = nullptr;
        }
        
        int getHight() {
            int hleft;
            int hright;
            int hl, hr;

            if (hasLeft() || hasRight()) {
                hleft = 2;
                hright = 2;
                getHight(pLeft, hleft, hright);
                hl = max(hleft, hright);
                hleft = 2;
                hright = 2;
                getHight(pRight, hleft, hright);
                hr = max(hleft, hright);
                return max(hl, hr);
            } else return 1;
        }
        
        int getBal() {
            if (hasRight() && hasLeft())
                return pRight->getHight() - pLeft->getHight();
            else if (hasRight() && !hasLeft())
                return pRight->getHight() - 0;
            else if (!hasRight() && hasLeft())
                return 0 - pLeft->getHight();
            else return 0;
        }
    
    private:
        K pKey;
        vector<V> values;
        Position<K,V>* pParent;
        Position<K,V>* pLeft;
        Position<K,V>* pRight;
        
        int getHight(Position<K,V>* p, int &hleft, int &hright) {
            if (p == nullptr) return 0;
            if (p->hasLeft() && p->hasRight())
            {
                hleft++;
                hright++;
                return max(getHight(p->left(), hleft, hright),getHight(p->right(), hleft, hright));
            }
            else if (p->hasLeft() && !p->hasRight())
            {
                hleft++;
                return getHight(p->left(), hleft, hright);
            }

            else if (!p->hasLeft() && p->hasRight())
            {
                hright++;
                return getHight(p->right(), hleft, hright);
            } else {
                if (p->parent()->left() == this) {
                    return hleft;
                } else return hright;
            }
        }
};

#endif /* POSITION_H */


