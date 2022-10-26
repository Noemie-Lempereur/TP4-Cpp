//
// Created by Noémie on 16/11/2020.
//

#ifndef TP4_PGM_H
#define TP4_PGM_H



class PGM {
private:
    int largeur;
    int hauteur;
    int valeur_max;
    int valeur_min;
    int **data;
    static int nbImages;
public:
    PGM();
    PGM(int haut, int larg, int max,int min);
    ~PGM();
    PGM(PGM const& copie);
    void setLargeur(int larg);
    void setHauteur(int haut);
    void setValeurMax(int max);
    void setData(int **tab);
    int getLargeur();
    int getHauteur();
    int getValeurMax();
    int** getData();
    void initImage(int haut, int larg);
    void supprImage();
    void creeImage(int minpix=0, int maxpix=255);
    int getValeurMin();
    void setValeurMin(int min);
    void afficherImage();
    void ecrireFichier(char* nom_fichier);
    void dessinRect(int x1, int y1, int x2, int y2, int val);
    void dessinLigne(int x1, int x2, int line, int val);
    void dessinCroix(int x, int y, int val);
    void lectureFichier(char *nom_fichier);
    static int getNbImages();
    void finProgramme();
    void seuil(int seuil, char *nom_fichier);
    void flou(int larg);
    void filtrerImage(int l);
};


#endif //TP4_PGM_H
