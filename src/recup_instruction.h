#include <stdio.h>

// Ce module permet récuperer une ligne d'instruction et récupérer les opérandes

// Fichier recup_instruction.c
int recup_ligne(char* ligne, FILE * fichier_assembleur);
int detection_instruction(char* ligne);
void recup_adresses_typeR(char* ligne, int* adresses);
void recup_donnee_typeI(char* ligne, int* donnees);
double recup_index_typeJ(char* ligne);