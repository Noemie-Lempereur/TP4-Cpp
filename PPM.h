//
// Created by Noémie on 23/11/2020.
//

#ifndef TP4_PPM_H
#define TP4_PPM_H


class PPM {
private:
    int largeur;
    int hauteur;
    int valeur_max;
    int valeur_min;
    int ***data;
    static int nbImages;
public:
    PPM();
    PPM(int haut, int larg, int max,int min);
    ~PPM();
    PPM(PPM const& copie);
    void setLargeur(int larg);
    void setHauteur(int haut);
    void setValeurMax(int max);
    void setData(int **tab[3]);
    int getLargeur();
    int getHauteur();
    int getValeurMax();
    int*** getData();
    void initImage(int haut, int larg);
    void supprImage();
    void creeImage(int minpix=0, int maxpix=255);
    int getValeurMin();
    void setValeurMin(int min);
    void afficherImage();
    void ecrireFichier(char* nom_fichier);
    void dessinRect(int x1, int y1, int x2, int y2, int valR,int valV,int valB);
    void dessinLigne(int x1, int x2, int line, int valR,int valV,int valB);
    void dessinCroix(int x, int y, int valR,int valV,int valB);
    void lectureFichier(char *nom_fichier);
    static int getNbImages();
    void seuil(int seuil);
};


#endif //TP4_PPM_H
