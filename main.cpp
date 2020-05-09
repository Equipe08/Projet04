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
    ifstream fw("fw.txt",ios::in);
    if (fw){
        string ch1,ch2;
        int n ;

        while(fw.peek()!=EOF){
        fw >> ch1 >> ch2 >> n ;
        mp_w[ch1+" "+ch2]=n ;
        }
    }
    fw.close();
    ifstream fl("fl.txt",ios::in);
    if (fl){
        string ch1,ch2;
        int n ;
        while(fl.peek()!=EOF){
        fl >> ch1 >> ch2 >> n ;
        mp_l[ch1+" "+ch2]=n ;
        }
    }
    fl.close();
    ifstream fp("pw.txt",ios::in) ;
    ifstream fnp("pnw.txt",ios::in) ;
    if (fp && fnp) {
        string ch1,ch2,ch;
        int n ;
        while(!fnp.eof()){
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
int score(int n, double x ){
    int s;
    s=(10000000/x)* n;
    return s;
}
void save(){
    ofstream sfw("fw.txt",ios::out);
    if (sfw){
        map<string ,int>::iterator it ;
        for(it=mp_w.begin();it!=mp_w.end();it++){

            sfw << it->first <<" "<<it->second ;
            if (++it!=mp_w.end()) sfw << "\n" ;
            it-- ;
        }
    }
    sfw.close() ;
    ofstream sfl("fl.txt",ios::out);
    if(sfl){
        map<string ,int>::iterator it2 ;
        for(it2=mp_l.begin();it2!=mp_l.end();it2++){
            sfl << it2->first <<" "<<it2->second ;
            if (++it2!=mp_l.end()) sfl << "\n" ;
            it2-- ;
        }
    }
    sfl.close() ;
    ofstream sfp("pw.txt",ios::out) ;
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
void menu(){
    cout <<"1-jouer" << endl ;
    cout << "2-historique" << endl ;
    cout << "3-meilleurs scores" << endl ;
    cout << "4-quitter"<< endl;
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
         for (int j=0; j<5; j++)
         {string lg;
        getline(fichier, lg);
        tab[j]=lg;
        }
        fichier.close();
     }
        for (int i=0; i<5; i++)

            {
                size_t pos = tab[i].find("//");
                string ch= tab[i].substr (pos+2);
                istringstream iss( ch );

                iss >> t[i];}

     for (int i=0; i<5; i++)
     {
         if (s>=t[i])
     {
         test=true;
         for (int j=4; j>i; j--)
                {tab[j]=tab[j-1];}

     string ch= n + "-" + p;
     do
     {
         ch= ch+"-";
     }
     while (ch.length()!=20);
     string s1=to_string(s);
     ch= ch +"//"+s1;
     tab[i]=ch;
     break;
     }}
     if (test)
     {
     cout<<"Felicitations tu es parmi la TOP 5"<< endl;
            for (int j=0; j<5; j++)
                {cout<< tab[j]<<endl;}
     ofstream fichierx("ms.txt", ios::out | ios::trunc);
        if(fichierx)
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
    int nb;
    switch (n){
    case 1:
        ch="difficile" ;
        nb=99;
        break ;
    case 2:
        ch="normal" ;
        nb=40;
        break ;
    case 3:
        ch="facile" ;
        nb=10;
        break ;
    }
    Partie p(ch) ;


    int h ,q;
    system("cls") ;
    cout << p ;

    cout << "donner les coordonnes de la case : ";
    cin >> h >> q ;
    p.placerMine(h,q) ;
    p.calculValeur() ;
    p.selectAction(0,h,q) ;
    clock_t start, t_end;
    start =clock();


    do{
        system("cls") ;
        cout << p ;

        cout << "donner les coordonnes de la case : ";
        cin >> h >> q ;
        cout << "choisir votre action :\n 1-liberer une case 2-marquer une mine 3-demarquer une mine 4-quitter partie" << endl ;
        cin >> n ;
        if(n==4) break ;

    }while(p.selectAction(n-1,h,q)) ;
    system("cls") ;
    cout << p ;

    t_end =clock();

    if (p.resultatPartie()){
        int s;
        double seconds= t_end - start;

        s=score (nb , seconds);
        cout << "\n \n Bien joue !!"<<endl;
        comparescore(s,nom,prenom);
        if(mp_w[nom+" "+prenom]) mp_w[nom+" "+prenom]+=1 ;

        else  mp_w[nom+" "+prenom]=1 ;
        ss << " won score:"<<s ;


    }
    else {
        cout <<"\n\nGame Over" ;
        if(mp_l[nom+" "+prenom]) mp_l[nom+" "+prenom]+=1 ;
        else mp_l[nom+" "+prenom]=1 ;
        ss << " loss" ;
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

        if(fichiers)
        {       cout<<"TOP5"<<endl;;
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
