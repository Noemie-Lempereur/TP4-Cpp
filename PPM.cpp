//
// Created by Noémie on 23/11/2020.
//

#include "PPM.h"

#include <cstdlib>
#include "time.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

int PPM::nbImages=0;

void PPM::setValeurMax(int max) {
    valeur_max=max;
}

void PPM::setValeurMin(int min) {
    valeur_min=min;
}

void PPM::setHauteur(int haut) {
    hauteur=haut;
}

void PPM::setLargeur(int larg) {
    largeur=larg;
}

void PPM::setData(int ***tab) {
    data=tab;
}

int PPM::getLargeur() {
    return largeur;
}

int PPM::getHauteur() {
    return hauteur;
}

int PPM::getValeurMax() {
    return valeur_max;
}

int PPM::getValeurMin() {
    return valeur_min;
}

int*** PPM::getData() {
    return data;
}

void PPM::initImage(int haut, int larg) {
    data=new int**[haut];
    for(int i=0;i<haut;i++) {
        data[i]=new int*[larg];
        for(int j=0;j<larg;j++) {
            data[i][j]=new int[3];
        }
    }
    setHauteur(haut);
    setLargeur(larg);
    setValeurMax(255);
    setValeurMin(0);
}

void PPM::supprImage() {
    for(int i=0;i<hauteur;i++) {
        for(int j=0;j<3;j++) {
            delete[](data[i][j]);
        }
        delete[](data[i]);
    }
    delete[](data);
    setHauteur(0);
    setLargeur(0);
}

void PPM::creeImage(int minpix, int maxpix) {
    srand (time(NULL));
    int ran;
    for(int i=0;i<hauteur;i++){
        for(int j=0;j<largeur;j++) {
            ran = rand() % 256;
            data[i][j][0]=ran;
            ran = rand() % 256;
            data[i][j][1]=ran;
            ran = rand() % 256;
            data[i][j][2]=ran;
        }
    }
}

PPM::PPM() {
    initImage(300,300);
    nbImages++;
}

PPM::PPM(int haut, int larg, int max, int min) {
    initImage(haut,larg);
    nbImages++;
}

PPM::~PPM() {
    supprImage();
    nbImages--;
}

PPM::PPM(const PPM &copie) {
    initImage(hauteur,largeur);
    for(int i=0;i<hauteur;i++){
        for(int j=0;j<largeur;j++){
            for(int k=0;k<3;k++) {
                data[i][j][k] = copie.data[i][j][k];
            }
        }
    }
    nbImages++;
}

void PPM::afficherImage() {
    for(int i=0;i<hauteur;i++){
        for(int j=0;j<largeur;j++) {
            for(int k=0;k<3;k++) {
                if (data[i][j][k] > 99) {
                    cout << data[i][j][k] << " ";
                } else {
                    if (data[i][j][k] > 9) {
                        cout << data[i][j][k] << "  ";
                    } else {
                        cout << data[i][j][k] << "   ";
                    }
                }
            }
            cout <<"    ";
        }
        cout<<endl;
    }
}

void PPM::ecrireFichier(char* nom_fichier) {
    ofstream myfile;
    myfile.open(nom_fichier);
    myfile<<"P3\n";
    myfile<<largeur<<' '<<hauteur<<'\n';
    myfile<<valeur_max<<'\n';
    for(int i=0;i<hauteur;i++){
        for(int j=0;j<largeur;j++) {
            for(int k=0;k<3;k++) {
                if (data[i][j][k] > 99) {
                    myfile << data[i][j][k] << " ";
                } else {
                    if (data[i][j][k] > 9) {
                        myfile << data[i][j][k] << "  ";
                    } else {
                        myfile << data[i][j][k] << "   ";
                    }
                }
            }
        }
        myfile<<'\n';
    }
}

void PPM::dessinRect(int x1, int y1, int x2, int y2, int valR,int valV,int valB){
    for(int i=y1;i<=y2;i++){
        for(int j=x1;j<=x2;j++){
            data[i][j][0]=valR;
            data[i][j][1]=valV;
            data[i][j][2]=valB;
        }
    }
}

void PPM::dessinLigne(int x1, int x2, int line, int valR,int valV,int valB){
    for(int i=x1;i<= x2;i++){
        data[line][i][0]=valR;
        data[line][i][1]=valV;
        data[line][i][2]=valB;
    }
}

void PPM::dessinCroix(int x, int y, int valR,int valV,int valB){
    data[y][x][0]=valR;
    data[y][x][1]=valV;
    data[y][x][2]=valB;
    data[y-1][x-1][0]=valR;
    data[y-1][x-1][1]=valV;
    data[y-1][x-1][2]=valB;
    data[y+1][x+1][0]=valR;
    data[y+1][x+1][1]=valV;
    data[y+1][x+1][2]=valB;
    data[y-1][x+1][0]=valR;
    data[y-1][x+1][1]=valV;
    data[y-1][x+1][2]=valB;
    data[y+1][x-1][0]=valR;
    data[y+1][x-1][1]=valV;
    data[y+1][x-1][2]=valB;
}

void PPM::lectureFichier(char* nom_fichier){
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
        cout<<hauteur<<endl;
        cout<<largeur<<endl;
        for(int i=0;i<hauteur;i++){
            for(int j=0;j<largeur;j++){
                for(int k=0;k<3;k++) {
                    cout<<data[i][j][k]<<endl;
                    s >> data[i][j][k];
                }
            }
        }
    }
    monfichier.close();
}

int PPM::getNbImages() {
    return nbImages;
}

void PPM::seuil(int seuil) {
    for(int i=0;i<hauteur;i++){
        for(int j=0;j<largeur;j++){
            for(int k=0;k<3;k++) {
                if (data[i][j][k] > seuil) {
                    data[i][j][k] = 255;
                } else {
                    data[i][j][k] = 0;
                }
            }
        }
    }
}
