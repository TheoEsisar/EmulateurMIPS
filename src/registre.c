// Module permettant de lire et écrire le contenu des registres

#include <stdio.h>
#include <stdlib.h>

#define NB_REGISTRE 35

int registre[NB_REGISTRE]; //32 premiers registres puis HI, LO et pc

void init_registre(){
  int i = 0;
  for (i = 0;i<NB_REGISTRE;i++){
    registre[i] = 0;
  }
}

void ecrire_registre(int nb_registre, int valeur){
  registre[nb_registre] = valeur;
}

int lecture_registre(int nb_registre){
  return registre[nb_registre];
}

void affiche_registre(){
  for (int i = 0; i < 32; i++)
  {
    if (i<10)
    {
      printf("R0%d = %d  ", i, registre[i]);
    }
    else{
      printf("R%d = %d  ", i, registre[i]);
    }
    if((i+1)%8 == 0)
    printf("\n");
  }
  printf("HI = %d LO = %d PC = 0x%08x\n", registre[32], registre[33], registre[34]);
  
}