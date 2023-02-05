// Projet MIPS 2022-2023
// Auteurs: Delgrange_Gay

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "recup_instruction.h"
#include "conversion.h"
#include "registre.h"
#include "memoire.h"
#include "execution.h"

int main(int argc, char **argv)
{
   FILE * fichier_assembleur = NULL;
   FILE * fichier_assemble = NULL;
   FILE * fichier_final = NULL;


    if(argc==1){  //Mode interactif

      printf("\nHello émulateur MIPS!\n\n");
      printf("Attention : certaines instructions ne fonctionnent pas en mode interactif (jump et branchement)\n\n");
   
      int instruction;
      char ligne[30];
      char fin[] = "EXIT";
      int i = 0;

      fgets(ligne, 29, stdin);   // Lecture de la ligne
      while(ligne[i] != 10){     //Enlève le saut de ligne
         i++;
      }
      ligne[i] = '\0';

      while(strcmp(fin, ligne) != 0){     // Tant qu'il dit pas EXIT, on continue
         
         instruction = BinaireToDecimal(instruction_to_binaire(ligne));
         printf("%8.8x\n", instruction);

         execution_instruction(instruction, 0);

         affiche_registre();
         printf("\n\n"); 

         fgets(ligne, 29, stdin);   // Lecture de la ligne
         i = 0;
         while(ligne[i] != 10){     //Enlève le saut de ligne
            i++;
         }
         ligne[i] = '\0';
         
      }

      printf("\n");

    }

    
    else if(argc==3){   //Mode pas à pas
      
      fichier_assembleur = fopen(argv[1], "r");
      fichier_assemble = fopen("tmp_assemble", "w+");   //Ouverture en mode écriture
      fichier_final = fopen("tmp_final", "w");          //Ouverture en mode écriture

      if(fichier_assembleur == NULL){                   //Vérification ouverture fichier
         printf("\nErreur : Fichier non trouvé\n\n");
         exit( EXIT_FAILURE );
      }

      printf("\nHello émulateur MIPS!\n\n");
      
      char ligne[30]; // valeur par défaut
      char instruct_binaire[33];
      int exit = 0;

      while (exit == 0)
      {
         exit = recup_ligne(ligne, fichier_assembleur);
         if (ligne[0] != '\0')
         {
            //printf("%s\n", ligne);
            strcpy(instruct_binaire, instruction_to_binaire(ligne));
            //printf("%8.8x\n", BinaireToDecimal(instruct_binaire));
            fprintf(fichier_assemble, "%8.8x\n", BinaireToDecimal(instruct_binaire));
         }
      }

      execution(fichier_assemble, fichier_final, 1);


      fclose(fichier_assembleur); //Fermeture du fichier
      fclose(fichier_assemble);
      fclose(fichier_final);
      remove("tmp_assemble");
      remove("tmp_final");
      
    }
    
    
      else if (argc==4){  //Mode automatique

      fichier_assembleur = fopen(argv[1], "r"); //Ouverture en mode lecture
      fichier_assemble = fopen(argv[2], "w+");   //Ouverture en mode écriture
      fichier_final = fopen(argv[3], "w");      //Ouverture en mode écriture
      
      if(fichier_assembleur == NULL){                       //Vérification ouverture fichier
         printf("\nErreur : Fichier non trouvé\n\n");
         exit( EXIT_FAILURE );
      }

      printf("\nHello émulateur MIPS!\n\n");

      char ligne[30]; // valeur par défaut
      char instruct_binaire[33];
      int exit = 0;

      while (exit == 0)
      {
         exit = recup_ligne(ligne, fichier_assembleur);
         if (ligne[0] != '\0')
         {
            //printf("%s\n", ligne);
            strcpy(instruct_binaire, instruction_to_binaire(ligne));
            //printf("%8.8x\n", BinaireToDecimal(instruct_binaire));
            fprintf(fichier_assemble, "%8.8x\n", BinaireToDecimal(instruct_binaire));
         }
      }

      execution(fichier_assemble, fichier_final, 0);

      //Fermeture des fichiers
      fclose(fichier_assembleur);   
      fclose(fichier_assemble);
      fclose(fichier_final);

    }
    else{
       printf("Erreur de syntaxe\n");
    }

    return 0;
}
