#include "threadTexte.h"

int calculAlgo(int nombre)
{
     int compteur = 0;
     int temps=0;

     QTime time;

     time.start();

     QVector<bool> tableau(nombre+1, true);
     tableau[0] = false;
     tableau[1] = false;

     for(int i = 2;i <= nombre;i++)
     {
             //Algo
     }
     temps = time.elapsed();
     return temps;
}
