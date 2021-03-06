#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <cstdlib>
#include <map>
#include <vector>
#include <fstream>
#include "case.h"
#include "partie.h"
#include <ctime>
#include <sstream>
#include <string>
using namespace std;

map<string ,vector< string > > mp_p ;
map<string , int > mp_w ;
map<string ,int > mp_l ;
void menu() ;
void jouer() ;
void historique() ;
void meilleurscore();
void load(){
    ifstream fw("fw.txt",ios::in);// remplir le dictionnaire mp_w a partir du fichier fw
    if (fw){
        string ch1,ch2;
        int n ;

        while(fw.peek()!=EOF){
        fw >> ch1 >> ch2 >> n ;
        mp_w[ch1+" "+ch2]=n ;
        }
    }
    fw.close();
    ifstream fl("fl.txt",ios::in); // remplir le dictionnaire mp_l a partir du fichier fl
    if (fl){
        string ch1,ch2;
        int n ;
        while(fl.peek()!=EOF){
        fl >> ch1 >> ch2 >> n ;
        mp_l[ch1+" "+ch2]=n ;
        }
    }
    fl.close();
    ifstream fp("pw.txt",ios::in) ; // remplir le dictionnaire mp_p a partir du fichier pw et pnw
    ifstream fnp("pnw.txt",ios::in) ;
    if (fp && fnp) {
        string ch1,ch2,ch;
        int n ;
        while(fnp.peek()!=EOF){
            fnp >> ch1 >> ch2 >> n ;
            for (int i=0;i<n;i++){
                getline(fp,ch) ;
                mp_p[ch1+" "+ch2].push_back(ch) ;
            }
        }





    }
    fp.close() ;
    fnp.close() ;

}
int score(int n, double x ){ //Calcul du score
    int s;
    s=(10000000/x)* n;
    return s;
}
void save(){
    ofstream sfw("fw.txt",ios::out); // mise a jour du fichier fw a partir de mp_w
    if (sfw){
        map<string ,int>::iterator it ;
        for(it=mp_w.begin();it!=mp_w.end();it++){

            sfw << it->first <<" "<<it->second ;
            if (++it!=mp_w.end()) sfw << "\n" ;
            it-- ;
        }
    }
    sfw.close() ;
    ofstream sfl("fl.txt",ios::out); // mise a jour du fichier fl a partir de mp_l
    if(sfl){
        map<string ,int>::iterator it2 ;
        for(it2=mp_l.begin();it2!=mp_l.end();it2++){
            sfl << it2->first <<" "<<it2->second ;
            if (++it2!=mp_l.end()) sfl << "\n" ;
            it2-- ;
        }
    }
    sfl.close() ;
    ofstream sfp("pw.txt",ios::out) ; // mise a jour du fichier pw et pnw a partir de mp_p
    ofstream sfnp("pnw.txt",ios::out) ;
    if (sfp && sfnp){
    map<string ,vector< string > >::iterator it3 ;
        for(it3=mp_p.begin();it3!=mp_p.end();it3++){
            sfnp << it3->first << " "<< it3->second.size() ;
            if (++it3!=mp_p.end()) sfnp << "\n" ;
            it3-- ;
            while(!it3->second.empty()){
                sfp << it3->second.back()<<"\n" ;
                it3->second.pop_back() ;
            }
        }
    }
    sfp.close() ;
    sfnp.close() ;


}
int main()
{
    load() ;
    menu() ;
    save() ;
    return 0;
}
void menu(){ //Affichage du menu
    cout <<"1-jouer" << endl ;
    cout << "2-historique" << endl ;
    cout << "3-meilleurs scores" << endl ;
    cout << "4-quitter et enregistrer"<< endl;
    int n ;
    cin >> n ;
    switch (n){
    case 1:
        system("cls") ;
        jouer() ;
        break ;
    case 2:
        system("cls") ;
        historique() ;
        break ;
    case 4:
        system("cls");
        break;
    case 3:
       system("cls");
       meilleurscore();
        break ;
    }
}
void comparescore(int s, string n, string p)
{
    bool test=false;
    string tab[5];
    int t[5];
     ifstream fichier("ms.txt", ios::in);
     if (fichier)
     {
        for (int j=0; j<5; j++) //Mettre le contenu des lignes du fichier dans un tableau tab
        {
        string lg;
        getline(fichier, lg);
        tab[j]=lg;
        }
        fichier.close();
     }
        for (int i=0; i<5; i++) //Extraire les scores contenus dans les lignes dans un tableau d'entiers t

            {
                size_t pos = tab[i].find("//");
                string ch= tab[i].substr (pos+2);
                istringstream iss( ch );

                iss >> t[i];
            }

     for (int i=0; i<5; i++) //Comparer le score S avec les autres scores dans le tableau t
     {
         if (s>=t[i])
     {
         test=true;
         for (int j=4; j>i; j--) // D�calage des cases du tableau pour laisser un espace pour le score dans la case i
                {tab[j]=tab[j-1];
                }

     string ch= n + "-" + p;
     do
     {
         ch= ch+"-";
     }
     while (ch.length()!=20);
     string s1=to_string(s);
     ch= ch +"//"+s1; //Formatage de l'affichage de la case i
     tab[i]=ch;
     break;
     }}
     if (test) //Si l'utilisateur fait partie de la TOP5
     {
     cout<<"Felicitations tu es parmi la TOP 5"<< endl;
            for (int j=0; j<5; j++) //Affichage du tableau des scores et les noms
                {cout<< tab[j]<<endl;}
     ofstream fichierx("ms.txt", ios::out | ios::trunc);
        if(fichierx) //Stocker la nouvelle TOP5 dans le fichier
        {
                for (int j=0; j<5; j++)
                {
                fichierx << tab[j] << endl;}
                fichierx.close();
        }}
        else cout<<"Votre score est: "<<s<<endl;


}
void jouer(){
    cout << "donner votre nom et prenom :" ;
    string nom,prenom ;
    cin >> nom >> prenom ;
    time_t tp = time(0);

    tm * ts = localtime(&tp);
    stringstream ss ;

    ss  << ts->tm_mday<< "/"<< ts->tm_mon +1  << "/" << 1900 + ts->tm_year <<" "<<ts->tm_hour<<":"<< ts->tm_min ;


    system("cls") ;
    cout << "choisir la difficulte : "<< endl ;
    cout << "1-difficile" <<endl ;
    cout << "2-normal"<< endl ;
    cout << "3-facile" << endl ;
    int n ;
    cin >> n ;
    string ch ;
    int nb, nbli,nbcol;
    switch (n){
    case 1:
        ch="difficile" ;
        nb=99;
        nbcol=30;
        nbli=16;
        break ;
    case 2:
        ch="normal" ;
        nb=40;
        nbcol=16;
        nbli=16;
        break ;
    case 3:
        ch="facile" ;
        nb=10;
        nbcol=9;
        nbcol=9;
        break ;
    }
    Partie p(ch) ;


    int h ,q;
    system("cls") ;
    cout << p ;


    do
    {   cout << "donner les coordonnes de la case : ";
        cin >> h >> q ;}
    while (h<0 || h>=nbli || q<0 || q>=nbcol);
    p.placerMine(h,q) ;
    p.calculValeur() ;
    p.selectAction(0,h,q) ;
    clock_t start, t_end;
    start =clock(); //Declencher le chronom�tre


    do{
        system("cls") ;
        cout << p ;


         do
    {   cout << "donner les coordonnes de la case : ";
        cin >> h >> q ;}
    while (h<0 || h>=nbli || q<0 || q>=nbcol);
        cout << "choisir votre action :\n 1-liberer une case 2-marquer une mine 3-demarquer une mine 4-quitter partie" << endl ;
        cin >> n ;
        if(n==4) break ;

    }while(p.selectAction(n-1,h,q)) ;
    system("cls") ;
    cout << p ;
    t_end =clock(); //Arret du chronom�tre

    if (p.resultatPartie()){ //En cas de victoire
        int s;
        double seconds= t_end - start; //Calcul du temps �coul�

        s=score (nb , seconds); //Calcul du score
        cout << "\n \n Bien joue !!\n\n"<<endl;
        comparescore(s,nom,prenom); //Comparer son score aux scores de la TOP5
        if(mp_w[nom+" "+prenom]) mp_w[nom+" "+prenom]+=1 ;

        else  mp_w[nom+" "+prenom]=1 ;
        ss << " won score:"<<s ; //Stocker le score dans le fichier


    }
    else {
        cout <<"\n\nGame Over" ;
        if(mp_l[nom+" "+prenom]) mp_l[nom+" "+prenom]+=1 ;
        else mp_l[nom+" "+prenom]=1 ;
        ss << " loss" ; //Stocker le r�sultat dans le fichier
    }
    ch = ss.str() ;
    mp_p[nom+" "+prenom].push_back(ch) ;

    cout << "\n\n 1-rejouer 2-retourner vers menu\n" ;
    cin >> n ;
    switch (n){
    case 1:
        system("cls") ;
        jouer() ;
        break ;

    case 2:
        system("cls") ;
        menu();
    }




}
void meilleurscore()
{
   ifstream fichiers("ms.txt", ios::in);

        if(fichiers) //Affichage du contenu du fichier
        {       cout<<"TOP5"<<endl;
                for (int i=0; i<5;i++){
                string lg;
                getline(fichiers, lg);
                cout<<lg<<endl;}
                fichiers.close();
        }
        else
        cerr << "Aucun score a afficher" << endl;
        cout << "\n\n 1-retourner vers menu\n" ;
    int n ;
    cin >> n ;
    system("cls") ;
    menu() ;
}
void historique(){
    map<string ,vector< string > >::iterator it3 ;
    for(it3=mp_p.begin();it3!=mp_p.end();it3++){
        cout << it3->first <<" a joue "<<it3->second.size()<<" parties : " ;
        if (mp_w[it3->first]) cout << mp_w[it3->first] ;
        else cout << 0;
        cout <<" gagnes  " ;
        if (mp_l[it3->first]) cout << mp_l[it3->first] ;
        else cout << 0;
        cout << " perdues" << endl ;
        for(unsigned int j=0; j<it3->second.size();j++ ){
            cout << it3->second[j] << endl ;
        }

    }
    cout << "\n\n 1-retourner vers menu\n" ;
    int n ;
    cin >> n ;
    system("cls") ;
    menu() ;
}
