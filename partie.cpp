#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <algorithm>
#include <set>
#include "partie.h"

Partie::Partie(string s){ //Constructeur de la grille � partir du niveau de la difficult�
    if (s=="difficile"){
        nb_col=30 ;
        nb_li=16;
        nb_bomb=99 ;
    }
    if(s=="normal"){
        nb_col=16 ;
        nb_li=16 ;
        nb_bomb=40 ;
    }
    if(s=="facile"){
        nb_col=9 ;
        nb_li=9;
        nb_bomb= 10 ;
    }
}
Partie::~Partie() {} //Destructeur
ostream & operator<<(ostream &out , const Partie p){ //Surchage de l'op�rateur << pour un affichage direct de la grille
    out << "   " ;
    for(int i=0;i<p.nb_col;i++){
        out  << i <<" ";
        if (i<10) out << " " ;
    }
    out << "\n" ;
    for(int i=0;i<p.nb_li;i++){
        out <<i<< " " ;
        if (i<10) out << " " ;

        for(int j=0;j<p.nb_col;j++){
            out << p.grille[i][j]<<"  " ;
        }
        out << "\n" ;
    }
    return out ;
}
void Partie::calculValeur(){
     for(int i=0;i<nb_li;i++){
        for(int j=0;j<nb_col;j++){
            if (grille[i][j].getValue()==-1){ //Pour chaque case contenant une grille les valeurs des cases � proximit� seront incr�ment�es de 1
                for(int k=i-1;k<i+2;k++){
                    for(int h=j-1;h<j+2;h++){
                        if((k>=0) && (h>=0) && (k<nb_li) && (h<nb_col) && !((k==i) and (h== j))) { //Controle des bornes pour ne pas d�passer la grille
                            if (grille[k][h].getValue()!=-1) {
                                    grille[k][h].setValue(grille[k][h].getValue() +1 ) ;
                            }
                        }
                    }
                }
            }
        }
    }
}
void Partie::afficherBomb(){ //En cas d'�chec toutes les bombes de la grille seront affich�es
       for(int i=0;i<nb_li;i++){
        for(int j=0;j<nb_col;j++){
            if (grille[i][j].getValue()==-1) grille[i][j].setShown() ;
        }
   }
}
void Partie::placerMine(int x,int y){ //Placement des mines en fonction de la premi�re case choisie
    int a,b,Ent;
    bool test;
    srand(time(NULL)) ;
    Ent= 2 + rand() % 2; //Choisir un entourage bien d�termin� al�atoirement
    vector <int> vecX;
    vector <int> vecY;
    for (int i=0; i<Ent+1; i++) //Les coordonn�es des cases de l'entourage choisie seront ajout�s � 2 vecteur vecX et vecY
    {
        vecX.push_back(x+i);
        vecY.push_back(y+i);
        vecX.push_back(x-i);
        vecY.push_back(y-i);
    }
    /*for (int i=Ent+1; i<2*Ent+1;i++)
    {
        vecX.push_back(x-i);
        vecY.push_back(y-i);
    }*/
    for(int i=0;i<nb_bomb;i++){

        do {
        test = true ;
        a=rand()%nb_li ;
        b=rand()%nb_col ;
        if (find(vecX.begin(), vecX.end(), a) != vecX.end() && find(vecY.begin(), vecY.end(), b) != vecY.end())
            {
                test=false;}}
        while ((grille[a][b].getValue()==-1) || (test==false))   ; //R�peter le choix de a et b jusqu'� ce que case (a,b) n'est pas dans l'entourage de la case (x,y) et ne contient pas une mine
        grille[a][b].setValue(-1) ;
    }
}
void Partie::afficherZeros(int x, int y){ //Pour toute case de valeur z�ro lib�r�e toutes les case � proximit� seront lib�r�es
    if (grille[x][y].getValue()==0){
        grille[x][y].setShown();
        for (int i=x-1;i<x+2;i++){
            for (int j=y-1;j<y+2;j++){
            if((i>=0) &&(j>=0) &&(i<nb_li) &&(j<nb_col) &&!((i==x)&&(j==y)) && grille[i][j].getEtat()!='s') afficherZeros(i,j); //Si une case lib�r�e est de valeur 0, on fait appel par r�cursivit� � afficherZeros
            }
        }
    }
    else {
        grille[x][y].setShown() ; //Condition d'arret
    }
}
bool Partie::selectAction(int i ,int x,int y){
    if (i==0){ //Si l'action est lib�rer case
        if (grille[x][y].getValue()==-1 && grille[x][y].getEtat()!='f') {afficherBomb() ; return false ;} //Si la case choisie contient une bombe la fonction retourne false
        if (grille[x][y].getValue()==0) afficherZeros(x,y) ; //Si la case choisie est un z�ro , afficherZeros est appel�e
        if (grille[x][y].getEtat()!='f') grille[x][y].setShown() ; //Si un drapeau est plac�, un F est affich�
        for(int i=0;i<nb_li;i++){
            for(int j=0;j<nb_col;j++){
                if (grille[i][j].getValue()!=-1 && grille[i][j].getEtat()!='s') return true ; //Si toutes les cases ne contenant pas de bombes sont lib�r�es alors la fonction retourne true
            }
       }
        return false ;
    }
    if(i==1){ //Si l'action est marquer mine
        if (grille[x][y].getEtat()=='s') return true ; //Si la case choisie est lib�r�e la fonction retourne true
        grille[x][y].setFlag() ; //Sinon afficher F
        nb_bomb-=1 ; //Le nombre de bombes est d�cr�ment� de 1
        return true ;
    }
    if(i==2){ //Si l'action est d�marquer mine
        if (grille[x][y].getEtat()=='f') grille[x][y].setHidden() ;
        return true ;
    }
}
bool Partie::resultatPartie(){ //Fdsultat de la partie � partir des �tats des cases conteant une bombes
    for(int i=0;i<nb_li;i++){
        for(int j=0;j<nb_col;j++){
            if (grille[i][j].getValue()==-1 && grille[i][j].getEtat()=='s') return false  ;
            if (grille[i][j].getValue()!=-1 && grille[i][j].getEtat()=='h') return false ;
        }
   }
   return true ;
}

