#ifndef __MOYENNE_H__
#define __MOYENNE_H__

#include <Arduino.h>

template <typename T>
class Moyenne {

    private :
        T *valeurs;
        int taille;
        int index;
    
    public : 
        Moyenne(int taille) : taille(taille), index(0) {
            valeurs = new T[taille];
            for (int i = 0; i < taille; i++) {
                valeurs[i] = 0;
            }
        }

        ~Moyenne() {
            delete[] valeurs;
        }

        Moyenne& operator+(T valeur) {
            valeurs[index] = valeur;
            index = (index + 1) % taille;
            return *this;
        }

        T getMoyenne() {
            T somme = 0;
            for (int i = 0; i < taille; i++) {
                somme += valeurs[i];
            }
            return somme / (T)taille;
        }

        T getBetterMoyenne() {
            T somme = 0;
            T coeff = 0;
            for (int i = 0; i < taille; i++) {
                int adjustedIndex = (index + i - 1 + taille) % taille;
                // Calculate the weight for the current value based on its position
                int weight = (i + 1);
                coeff += weight;
                somme += valeurs[adjustedIndex] * weight;
            }
            return coeff != 0 ? somme / coeff : 0;
        }
};

#endif // __MOYENNE_H__