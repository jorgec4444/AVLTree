/* 
 * File:   WordIndexer.h
 * Author: JORGEC
 *
 * Created on 24 de mayo de 2020, 12:40
 */

#ifndef WORDINDEXER_H
#define WORDINDEXER_H
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>

#include "AVLTree.h"
#include "Tuple.h"

using namespace std;

template <class K,class V>
class WordIndexer {
    public:
        WordIndexer() {
            arbre = new AVLTree<K,V>(); // Constructor inicial (AVLTree buit)
        }
        
        WordIndexer(string _filename) { // Constructor amb fitxer llegit
            arbre = new AVLTree<K,V>();
            filename = _filename;
            addText(filename);
        }
        
        WordIndexer(const AVLTree<K, V>& orig) { // Constructor còpia
            arbre = AVLTree<K, V>(*orig);
        }
        
        string getFilename() { // Retorna el filename
            return filename;
        }
        
        AVLTree<K,V>* getTree() const { // Retorna el AVLTree actual
            return arbre;
        } 
        
        virtual ~WordIndexer() { // Truca al destructor de AVLTree
            arbre->~AVLTree();
        }
        
        bool contains(string word) { // Comprova si l'arbre conté la paraula
            return arbre->contains(word);
        }
        
        // Retorna un vector de tuples de la paraula especificada
        const vector<Tuple<int,int>> printOccurrences(string word) const {
            Position<K,V>* nt = arbre->_search(word);
            return nt->getValues();
        }
        
        // Printeja la paraula y la seva posició utilitzant el printOccurrences()
        // (basat en inorder)
        void printDictionary() {
            cout << "Mostrant índex de paraules" << endl;
            if (arbre->getRoot() != nullptr) {
                cout << "{ ";
                showPrintDict(arbre->getRoot()->left());
                cout << arbre->getRoot()->getKey() << " [";
                for (int i = 0; i < printOccurrences(arbre->getRoot()->getKey()).size(); i++) {
                    cout << "(";
                    cout << printOccurrences(arbre->getRoot()->getKey())[i].getLinia();
                    cout << ",";
                    cout << printOccurrences(arbre->getRoot()->getKey())[i].getPos();
                    cout << ")";
                } 
                cout << "]" << endl;
                showPrintDict(arbre->getRoot()->right());
                cout << " ]}" << endl;
            }
        }
        
        // Mètode que llegeix un fitxer i introdueix les seves paraules sense 
        // majúscules ni signes de puntuació i la seva pos al AVLTree de la classe
        void addText(string filename) {
            ifstream f_data;
            string linia;
            string word;
            
            int l_cnt = 0;
            f_data.open(filename,ios::in);
            
            if (!f_data.fail()) {
                while (!f_data.eof()) {
                    getline(f_data,linia); //Llegeixo el fitxer linia per linia.
                    l_cnt += 1;
                    istringstream iss(linia); //Tracto la linia per poder iterar
                    
                    int w_cnt = 0;
                    while (iss >> word) {
                        //For per eliminar tots els signes de puntuació i
                        //canviar les majúscules per minúscules de les paraules
                        for (int i = 0; i < word.size(); i++) {
                            char lletra = word[i];
                            int n = (int)lletra;
                            if ((n >= 33 && n <= 47) || (n >= 58 && n <= 64) || 
                                (n >= 91 && n <= 96) || (n >= 123 && n <= 126))
                                word.erase(i,1);
                            else if ((n >= 65 && n <= 90)) { //també amb tolower
                                n += 32;
                                lletra = (char)n;
                                word[i] = lletra;
                            }
                        }
                        w_cnt += 1;
                        insertWord(word,l_cnt,w_cnt);
                    }
                }
            }else
                cout << "error" << endl;
            f_data.close();
        }
        
        // Mètode per inserir paraules i posició al AVLTree
        void insertWord(string word, int line, int posWord) {
            Tuple<int,int> tupla = Tuple<int,int>(line,posWord);
            arbre->insert(word, tupla);
        }
        
    private:
        AVLTree<K, V>* arbre;
        string filename;
        
        // Mètode auxiliar per printDictionary (basat en inorder)
        void showPrintDict(Position<K,V>* p) const {
            if (p != nullptr) {
                showPrintDict(p->left());
                cout << p->getKey() << " [";
                for (int i = 1; i < printOccurrences(p->getKey()).size(); i++) {
                    cout << "(";
                    cout << printOccurrences(p->getKey())[i].getLinia();
                    cout << ",";
                    cout << printOccurrences(p->getKey())[i].getPos();
                    cout << ")";
                }
                cout << "]" << endl;
                showPrintDict(p->right());
            }
        }
};

#endif /* WORDINDEXER_H */

