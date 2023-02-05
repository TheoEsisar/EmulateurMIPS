// Module permettant de gérer la mémoire de notre émulateur MIPS

#include <stdio.h>
#include <stdlib.h>
#include "memoire.h"

#define TAILLE_MEMOIRE 1024   //Taille de la mémoire. A modifier ici si besoin
int memoire[TAILLE_MEMOIRE];

void init_memoire(){
  int i = 0;
  for (i = 0;i<TAILLE_MEMOIRE;i++){
    memoire[i] = 0;
  }
}

void ecrire_memoire(int nb_memoire, int valeur){
  if (nb_memoire >= TAILLE_MEMOIRE){  //Vérification dépassement
    printf("\nErreur : Dépassement mémoire\n\n");
    exit( EXIT_FAILURE );
  }
  memoire[nb_memoire] = valeur;
}

int lecture_memoire(int nb_memoire){
  return memoire[nb_memoire];
}

void affiche_memoire(){
  for (int i = 0; i < 20; i++)
  {
    printf("M[%d] = %d  ", i, memoire[i]);
    if((i+1)%8 == 0)
    printf("\n");
  }
  printf("\n");
}