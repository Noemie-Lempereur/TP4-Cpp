//
// Created by Noémie on 16/11/2020.
//

#include "PGM.h"
#include <cstdlib>
#include "time.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

int PGM::nbImages=0;

void PGM::setValeurMax(int max) {
    valeur_max=max;
}

void PGM::setValeurMin(int min) {
    valeur_min=min;
}

void PGM::setHauteur(int haut) {
    hauteur=haut;
}

void PGM::setLargeur(int larg) {
    largeur=larg;
}

void PGM::setData(int **tab) {
    data=tab;
}

int PGM::getLargeur() {
    return largeur;
}

int PGM::getHauteur() {
    return hauteur;
}

int PGM::getValeurMax() {
    return valeur_max;
}

int PGM::getValeurMin() {
    return valeur_min;
}

int** PGM::getData() {
    return data;
}

void PGM::initImage(int haut, int larg) {
    data=new int*[haut];
    for(int i=0;i<haut;i++) {
        data[i]=new int[larg];
    }
    setHauteur(haut);
    setLargeur(larg);
    setValeurMax(255);
    setValeurMin(0);
}

void PGM::supprImage() {
    for(int i=0;i<hauteur;i++) {
        delete[](data[i]);
    }
    delete[](data);
    setHauteur(0);
    setLargeur(0);
}

void PGM::creeImage(int minpix, int maxpix) {
    srand (time(NULL));
    int ran;
    for(int i=0;i<hauteur;i++){
        for(int j=0;j<largeur;j++) {
            ran = rand() % 256;
            data[i][j]=ran;
        }
    }
}

PGM::PGM() {
    initImage(0,0);
    nbImages++;
}

PGM::PGM(int haut, int larg, int max, int min) {
    initImage(haut,larg);
    nbImages++;
}

PGM::~PGM() {
    supprImage();
    nbImages--;
}

PGM::PGM(const PGM &copie) : hauteur(copie.hauteur),largeur(copie.largeur),valeur_min(copie.valeur_min),valeur_max(copie.valeur_max){
    initImage(hauteur,largeur);
    for(int i=0;i<hauteur;i++){
        for(int j=0;j<largeur;j++){
            data[i][j]=copie.data[i][j];
        }
    }
    nbImages++;
}

void PGM::afficherImage() {
    for(int i=0;i<hauteur;i++){
        for(int j=0;j<largeur;j++) {
            if (data[i][j]>99) {
                cout << data[i][j] << " ";
            }
            else{
                if(data[i][j]>9){
                    cout << data[i][j] << "  ";
                }
                else{
                    cout << data[i][j] << "   ";
                }
            }
        }
        cout<<endl;
    }
}

void PGM::ecrireFichier(char* nom_fichier) {
    ofstream myfile;
    myfile.open(nom_fichier);
    myfile<<"P2\n";
    myfile<<largeur<<' '<<hauteur<<'\n';
    myfile<<valeur_max<<'\n';
    for(int i=0;i<hauteur;i++){
        for(int j=0;j<largeur;j++) {
            if (data[i][j]>99) {
                myfile<< data[i][j] << " ";
            }
            else{
                if(data[i][j]>9){
                    myfile<< data[i][j] << "  ";
                }
                else{
                    myfile<< data[i][j] << "   ";
                }
            }
        }
        myfile<<'\n';
    }
}

void PGM::dessinRect(int x1, int y1, int x2, int y2, int val){
    for(int i=y1;i<=y2;i++){
        for(int j=x1;j<=x2;j++){
            data[i][j]=val;
        }
    }
}

void PGM::dessinLigne(int x1, int x2, int line, int val){
    for(int i=x1;i<= x2;i++){
        data[line][i]=val;
    }
}

void PGM::dessinCroix(int x, int y, int val){
    data[y][x]=val;
    data[y-1][x-1]=val;
    data[y+1][x+1]=val;
    data[y-1][x+1]=val;
    data[y+1][x-1]=val;
}

void PGM::lectureFichier(char* nom_fichier){
    ifstream monfichier;
    string ligne;
    stringstream s;
    monfichier.open(nom_fichier);
    if (monfichier.is_open()){
        getline(monfichier,ligne);
        s << monfichier.rdbuf();
        s >> largeur >> hauteur;
        s >> valeur_max;
        initImage(hauteur,largeur);
        for(int i=0;i<hauteur;i++){
            for(int j=0;j<largeur;j++){
                s>>data[i][j];
            }
        }
    }
    monfichier.close();
}

int PGM::getNbImages() {
    return nbImages;
}

void PGM::finProgramme() {
    nbImages=0;
}

void PGM::seuil(int seuil,char* nom_fichier) {
    for(int i=0;i<hauteur;i++){
        for(int j=0;j<largeur;j++){
            if(data[i][j]>seuil){
                data[i][j]=255;
            }
            else{
                data[i][j]=0;
            }
        }
    }
    ecrireFichier(nom_fichier);
}

void PGM::flou(int larg) {
    for(int i=0;i<hauteur;i++){
        for(int j=0;j<largeur;j++){
            int sum=0;
            int num=0;
            for(int k=i-larg;k<i+larg;k++){
                if(k>=0&&k<hauteur){
                    for (int p =j-larg; p<j + larg; p++) {
                        if(p>=0&&p<largeur){
                            sum=sum+data[k][p];
                            num=num+1;
                        }
                    }
                }
            }
            int val_moy=sum/num;
            data[i][j]=val_moy;
        }
    }
}

void Tri_Selection(int table[10000], int taille){
    int c;
    for(int i=0;i<taille-1;i++){
        for(int j=i+1;j<taille;j++){
            if(table[i]>table[j]){
                c=table[i];
                table[i]=table[j];
                table[j]=c;
            }
        }
    }
}

void PGM::filtrerImage(int l=0) {
    for(int i=0;i<hauteur;i++){
        for(int j=0;j<largeur;j++){
            int sum[10000]={0};
            int num=0;
            for(int k=(i-l);k<=(i+l);k++){
                if(k>=0&&k<hauteur){
                    for (int p =(j-l); p<=(j + l); p++) {
                        if(p>=0&&p<largeur){
                            sum[num]=data[k][p];
                            num=num+1;
                        }
                    }
                }
            }
            if(num!=0) {
                Tri_Selection(sum, num);
                int val_med = sum[num / 2];
                data[i][j] = val_med;
            }
        }
    }
}










