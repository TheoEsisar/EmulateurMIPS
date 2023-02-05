#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Ce module permet récuperer une ligne d'instruction et récupérer les opérandes

//Fonction qui supprime les espaces inutiles à la fin de la ligne
void supr_espace_ligne(char* ligne){
    int i = 1;
    while(ligne[i] != '\0'){
        if(ligne[i-1] == ' ' && (ligne[i] == ' ' || ligne[i] == '#' || ligne[i] == '\0' || ligne[i] == '\n')){
            ligne[i-1] = '\0';
        }
        i++;
    }
}

// Fonction qui récupère la ligne du fichier
int recup_ligne(char* ligne, FILE * fichier_assembleur){
    char c = fgetc(fichier_assembleur);
    int i=0;
    int result = 0;
    if (c == 13)            //Evite le Carriage Return
    {
        c=fgetc(fichier_assembleur);
    }
    
    while(c != '\n' && c != '\0' && c != EOF && c != '#' && i < 28 && c != 13){
        ligne[i] = c;
        i++;
        c = fgetc(fichier_assembleur);
    }
    ligne[i] = '\0';
    supr_espace_ligne(ligne);
    if (c!='\n' && c!= EOF)
    {
        while (c!='\n' && c!= EOF)
        {
            c = fgetc(fichier_assembleur);
        }  
    }
    if (c == EOF)
    {
        result = 1;
    }
    
    return result;
}


//Fonction renvoyant la position de l'instruction dans le tableau ci-dessous en fonction de la ligne reçu en entrée
int detection_instruction(char* ligne){
      char d[] = " ";
      char * compare= strtok(ligne, d);
      int int_str_compare = 1;
      char instruction[26][9] = {"ADD","ADDI","AND","BEQ","BGTZ","BLEZ","BNE","DIV","J","JAL","JR","LUI","LW","MFHI","MFLO","MULT","NOP","OR","ROTR","SLL","SLT","SRL","SUB","SW","SYSCALL","XOR"};
      for(int j=0; j<26; j++){
         int_str_compare = strcmp(compare, instruction[j]);
         if (int_str_compare == 0){
            return j;
         }
      }
      return -1;
}


// On peut avoir de 1 à 3 adresses à récupérer donc la taille de adresses est de 3 (adresse[2])
// Adresses doivent être initialisé à 0
void recup_adresses_typeR(char* ligne, int* adresses){      // Permet de récupérer les adresses des instructions et y "retournent" dans adresses
    int i = 0, j = 0;
    while(ligne[i] != '\0'){                                //On va jusqu'à la fin de la ligne
        if(ligne[i] == '$'){
            i++;
            while(ligne[i] != ',' && ligne[i] != '\0' && ligne[i] != ' '){     //Tant qu'on a pas finit le lire le nombre
                if(ligne[i] < 48 || ligne[i] > 57){                     //Vérifie que ce soit un chiffre
                    printf("\nErreur : Caractère non respecté\n\n");
                    exit( EXIT_FAILURE );
                }
                adresses[j] = adresses[j]*10 + (ligne[i]-48);
                i++;
            }
            if(adresses[j] >= 32){                          //Registre trop grand
                printf("\nErreur : Registre trop grand\n\n");
                exit( EXIT_FAILURE );
            }
            j++;                                            //Passe à l'adresse suivante
        }
        else{
            i++;
        }
    }
}


// On peut avoir 1 à 2 adresses et un entier de taille suffisant pour renter dans la taille de donnees est de 3 (donnees[2])
// Attention l'entier peut être négatif
// Adresses doivent être initialisé à 0
void recup_donnee_typeI(char* ligne, int* donnees){      // Permet de récupérer les données pour le type I et retourne le tableau de données
    int i = 0, j = 0;
    int signe = 1;
    while(ligne[i] != '\0'){                               //On va jusqu'à la fin de la ligne
        if(ligne[i] == '$'){                                //Cas de registre
            i++;
            while(ligne[i] != ','){                         //Tant qu'on a pas finit le lire le nombre
                if(ligne[i] < 48 || ligne[i] > 57){                     //Vérifie que ce soit un chiffre
                    printf("\nErreur : Caractère non respecté\n\n");
                    exit( EXIT_FAILURE );
                }
                donnees[j] = donnees[j]*10 + (ligne[i]-48);
                i++;
            }
            if(donnees[j] >= 32){                          //Registre trop grand
                printf("\nErreur : Registre trop grand\n\n");
                exit( EXIT_FAILURE );
            }
            j++;                                            //Passe à la donnée suivante
        }
        else if((ligne[i-1] == ' ' && ligne[i] != '$') || (ligne[i-1] == ',' && (ligne[i] != '$' && ligne[i] != ' '))){      //Cas d'entier
            if(ligne[i] == '-'){                            //Entier négatif
                signe = -1;
                i++;
            }
            while(ligne[i] != '\0' && ligne[i] != '(' && ligne[i] != ' '){     //Tant qu'on n'arrive pas au bout de la ligne ou à une parenthèse
                if(ligne[i] < 48 || ligne[i] > 57){                     //Vérifie que ce soit un chiffre
                    printf("\nErreur : Caractère non respecté\n\n");
                    printf("%d\n", ligne[i]);
                    exit( EXIT_FAILURE );
                }
                donnees[j] = donnees[j]*10 + signe*(ligne[i]-48);
                i++;
            }
            if(donnees[j] < -32768 || donnees[j] > 32767){
                printf("\nErreur : Valeur hors limite\n\n");
                exit( EXIT_FAILURE );
            }
            if(ligne[i] == '('){                            //Cas de SW et LW       //offset(base)
                j++;
                i = i+2;
                while(ligne[i] != ')'){                    //Tant qu'on n'arrive pas à la fin de la parenthèse
                    if(ligne[i] < 48 || ligne[i] > 57){                     //Vérifie que ce soit un chiffre
                    printf("\nErreur : Caractère non respecté\n\n");
                    exit( EXIT_FAILURE );
                }
                    donnees[j] = donnees[j]*10 + (ligne[i]-48);
                    i++;
                }
                if(donnees[j] >= 32){                          //Registre trop grand
                    printf("\nErreur : Registre trop grand\n\n");
                    exit( EXIT_FAILURE );
                }
                i++;
            }
        }
        else{
            i++;
        }
    }
}


// On utilise un double en index car celui-ci est codé sur 26 bits
// Index doit être iniatialisé à 0
double recup_index_typeJ(char* ligne){
    int i = 1;
    double index = 0;
    while(ligne[i-1] != ' '){                   //On va jusqu'au nombre
        i++;
    }
    while(ligne[i] != '\0'){                    //Tant qu'on a pas finit de lire le nombre
        if(ligne[i] < 48 || ligne[i] > 57){                     //Vérifie que ce soit un chiffre
            printf("\nErreur : Caractère non respecté\n\n");
            exit( EXIT_FAILURE );
        }
        index = index*10 + (ligne[i]-48);
        i++;
    }
    if(index >= 32768){                          //Index trop grand
        printf("\nErreur : Index trop grand\n\n");
        exit( EXIT_FAILURE );
    }
    return index;
}