#include <iostream>
#include "case.h"

using namespace std ;

Case::Case():valeur(0),etat('h') {} //Constructeur par défaut
Case::Case(int v,char c):valeur(v),etat(c) {}
Case::~Case() {}
void Case::setShown(){
    etat='s' ;
}
void Case::setHidden(){
    etat='h' ;
}
void Case::setFlag(){
    etat='f' ;
}
int Case::getValue() const {
    return valeur ;
}
void Case::setValue(int v){
    valeur=v ;
}
char Case::getEtat() const {
    return etat ;
}
ostream &operator<<(ostream &out, const Case C){ //Affichage personnalisé de la case en fonction de son état
    if(C.etat=='h') out<< 'X' ; //Afficher "X" dans le cas où la case est hidden
    if(C.etat=='s')  {if (C.valeur==-1) out << 'M' ; //Afficher la valeur ou "M" (mine) dans le cas où la case est shown
    else out<< C.valeur ;}
    if(C.etat=='f') out<< 'F' ; //Afficher "F" dans le cas où la case est marqué par un flag par l'utilistauer

    return out ;
}
