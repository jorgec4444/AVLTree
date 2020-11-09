/* 
 * File:   Tuple.h
 * Author: JORGEC
 *
 * Created on 24 de mayo de 2020, 12:40
 */

#ifndef TUPLE_H
#define TUPLE_H

using namespace std;

template <class L,class P>
class Tuple {
    public:
        // Constructor tuple
        Tuple(const L _linia, const P _pos){
            linia = _linia;
            pos = _pos;
        }

        // Getter linia
        const int& getLinia() const {
            return linia;
        }
        
        // Getter pos
        const int& getPos() const {
            return pos;
        }
        
        // Setter linia
        void setLinia (const int& _linia)  {
            linia = _linia;
        }
        
        // Setter pos
        void setPos (const int& _pos) {
            pos = _pos;
        }

        // Comprova si dos tuples tenen els mateixos valors
        bool operator==(const Tuple<L,P>& orig) const{
            if (getPos() == orig.getPos() && getLinia() == orig.getLinia())
                return true;
            else
                return false;
        }
        
        // Comprova si la tupla es més petita que una altra
        bool operator<(const Tuple<L,P>& orig) const{
            if (getLinia() < orig.getLinia())
                return true;
            else if(getLinia() == orig.getLinia()) {
                if (getPos() < orig.getPos())
                    return true;
                else return false;
            }else
                return false;
        }
        
        private:
            int linia;
            int pos;
};

#endif /* TUPLE_H */

