#include <iostream>
#include "case.h"

using namespace std ;

Case::Case():valeur(0),etat('h') {}
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
ostream &operator<<(ostream &out, const Case C){
    if(C.etat=='h') out<< 'X' ;
    if(C.etat=='s') { if (C.valeur==-1) out << 'M' ;
    else out<< C.valeur ;}
    if(C.etat=='f') out<< 'F' ;

    return out ;
}
