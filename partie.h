#ifndef PARTIE_H_INCLUDED
#define PARTIE_H_INCLUDED
#include <iostream>
#include <set>
#include "case.h"
class Partie{
private:
    int nb_col ;
    int nb_li ;
    int nb_bomb ;
    Case grille[30][30] ;
public:
    Partie(string ) ;
    ~Partie() ;
    void placerMine(int , int) ;
    void calculValeur() ;
    void afficherBomb() ;
    void afficherZeros(int ,int ) ;
    bool selectAction(int,int,int) ;
    bool resultatPartie() ;
    friend ostream & operator<<(ostream & , const Partie ) ;

};


#endif // PARTIE_H_INCLUDED
