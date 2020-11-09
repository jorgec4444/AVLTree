/* 
 * File:   main.cpp
 * Author: JORGEC
 *
 * Created on 24 de mayo de 2020, 12:38
 */

#include <cstdlib>
#include "WordIndexer.h"
#include "Tuple.h"
#include <ctime>
#include "AVLTree.h"
#include <iostream>

using namespace std;

// EXERCICI 5
/**|---------------------------------------------------------------------------|
 * |            | Inserció      | Inserció      | Cerca        | Cerca         |
 * |            | Fixter SHORT  | Fitxer LONG   | Fitxer LONG  | Fitxer LONG   |
 * |------------|---------------|---------------|--------------|---------------|
 * |BSTree      | 0.2 ms        |    62 ms      |  608 ms      | 749 ms        |
 * |AVLTree     | 0.12 ms       |    46 ms      |  529 ms      | 546 ms        |
 **|---------------------------------------------------------------------------|
/* En aquesta taula podem observar que el cost
 * computacional de la inserció i cerca es més
 * elevat a un BST que a un AVLTree, degut
 * a que el AVLTree distribueix les dades
 * d'una manera més organitzada i reduïnt així
 * el temps de cerca de la posició (a la inserció)
 * i del valor (a la cerca).
 * 
 * En quant a cost computacional, tant la inserció com la cerca
 * tenen un cost de O(n) en un BST (en el pitjor cas tindrà que
 * recòrrer tot el BST, mentres que en el AVLTree
 * el seu cost computacional és de O(logn) (sempre redueix les
 * dades/possibilitats a la meitat).
 */

//Prints the menu.
void printMenu() {
    cout << "Què vols fer?" << endl
            << "1. Carregar un fitxer al wordIndexer" << endl
            << "2. Mostrar arbre per ID en ordre creixent" << endl
            << "3. Llegir dictionary.txt" << endl
            << "4. Visualitzar índex de paraules" << endl
            << "5. Mostrar profunditat de l'arbre de wordIndexer" << endl
            << "6. Sortir" << endl;
}

int main(int argc, char** argv) {
    int option = 0;
    string filename;

    WordIndexer<string, Tuple<int, int>>* word_i = nullptr;
    
    cout << "Selecciona primerament l'opció 1" << endl;
    while(option != 6) {
        printMenu();
        cin >> option;
        switch(option) {
            default:{
                cout << "Torna a introduir una opció vàlida" << endl;
                cin >> option;
                break;
            }
            case 1:{
                char opcio;
                bool ok = false;

                while (!ok) {
                    cout << "Quin fitxer vols (P/G)?" << endl;
                    cin >> opcio;

                    if ((opcio == 'P') || (opcio == 'p')) {
                        filename = "shortText.txt";
                        ok = true;
                    }
                    else if ((opcio == 'G') || (opcio == 'g')) {
                        filename = "longText.txt";
                        ok = true;
                    }
                    else
                        cout << "Torna a introduir una opcio vàlida" << endl;
                }
                cout << "Calculant temps de creació de l'objecte wordIndexer..." << endl;
                
                unsigned t0, t1;
                t0 = clock();
                word_i = new WordIndexer<string, Tuple<int,int>>(filename);
                word_i->getTree()->balance();
                t1 = clock();
                double temps = double(t1-t0);
                cout << "Temps d'execució: " << temps  << "ms" << endl;
                break;
            }
            case 2:{
                if (word_i == nullptr) {
                    cout << "Crea un arbre primer!" << endl;
                } else {
                    word_i->getTree()->printInorder();
                }
                break;
            }
            
            /*Basant-me en el m'etode addText llegeixo el fitxer 
              dictionary i comprovo si l'arbre conté les paraules del fitxer.*/
            case 3:{ 
                unsigned t0, t1;
                ifstream f_data;
                string linia;
                string word;

                f_data.open("dictionary.txt",ios::in);
                t0 = clock();
                if (!f_data.fail()) {
                    while (!f_data.eof()) {
                        getline(f_data,linia); //Llegeixo el fitxer linia per linia.
                        istringstream iss(linia); //Tracto la linia per poder iterar

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
                            word_i->contains(word);
                        }
                }
                t1 = clock();
                double temps = double(t1-t0);
                cout << "Temps d'execució de cerca de totes les paraules del fitxer: " << temps  << "ms" << endl;
                }else
                    cout << "error" << endl;
                f_data.close();
                break;
            }
            case 4:{
                word_i->printDictionary();
                break;
            }
            case 5:{
                cout << "Profunditat de l'arbre guardat al wordIndexer: ";
                cout << word_i->getTree()->height()-2 << endl;
                break;
            }
            case 6:{
                cout << "Sortint..." << endl;
                break;
            }
        }
    }
    return 0;
}

