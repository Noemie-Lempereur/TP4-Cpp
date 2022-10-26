#include <iostream>
#include "PGM.h"
#include "PPM.h"
int main() {/*
    PGM img1=PGM(5,10,255,0);
    img1.initImage(5,10);
    img1.dessinRect(1,2,5,4,20);
    img1.afficherImage();
    std::cout<<std::endl;
    img1.creeImage();
    img1.afficherImage();
    std::cout<<std::endl;
    img1.dessinCroix(3,2,0);
    img1.afficherImage();
    std::cout<<std::endl;
    img1.ecrireFichier("exercice.txt");
    img1.seuil(200,"exercice.txt");
    img1.afficherImage();*/
    PPM img2=PPM(20,20,255,0);
    img2.creeImage(0,255);
    img2.ecrireFichier("testppm.ppm");
    PPM img3=PPM(7,24,255,0);
    img3.lectureFichier("ISEN2.ppm");
    img2.seuil(120);
    img3.dessinRect(3,4,10,6,56,255,3);
    img2.ecrireFichier("ISENligne.ppm");
    //img2.afficherImage();
    //img2.lectureFichier("lena.pgm");
    //img2.afficherImage();
    //img2.dessinLigne(250,350,300,6);


   // img2.seuil(120,"len120seuil.pgm");
   // img2.ecrireFichier("lencroix.pgm");
/*
    PGM img3=PGM(5,10,255,0);
    img3.initImage(5,10);
    //img3.afficherImage();
    img3.lectureFichier("balloons_noisy.ascii.pgm");
    //img3.afficherImage();
    img2.flou(20);
    //img3.filtrerImage(10);
    //img2.ecrireFichier("flou100.pgm");
*/
    //img3.afficherImage();
    return 0;
}
