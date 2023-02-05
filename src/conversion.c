#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "struct.h"

// Ce module permet d'écrire l'instruction sous forme binaire et de convertir le binaire en décimal


char instruct_binaire[33];

void DecimalToBinaire(unsigned int decimal, int taille, char binaire[]){  // Transforme un nombre entier en binaire --- On utilise un unsigned int pour que les valeurs négatives que peuvent prendre es immediate soit mises en complément à 2
    for(int i=0;i < taille; i++){
        if ((decimal %2) == 0)
        {
            binaire[taille-i-1] = '0';
        }
        else {
            binaire[taille-i-1] = '1';   
        }
        
        //binaire[taille-i] = 48 + (decimal %2);
        decimal = decimal / 2;
    }
    //binaire[5] = '\0';
}

int BinaireToDecimal(char *binaire){        //Transforme un tableau d'éléments binaire en nombre entier
    int i, n, sum = 0;
    for (i = 0; i < 32; i++) {
        n = *(binaire + i) - '0';
        sum += (n * (1 << (32 - (i + 1))));
    }
    return sum;
}

void typeR_to_Binary(struct typeR INST, int operande[3]){
    // Initialisation
    char temp_5bits[5];
    int i, j = 0;

    //Assigne les opérandes binaire dans la structure
    DecimalToBinaire(operande[0], 5, temp_5bits);      
    strncpy(INST.rd, temp_5bits, 5);
    DecimalToBinaire(operande[1], 5, temp_5bits);  
    strncpy(INST.rs, temp_5bits, 5);
    DecimalToBinaire(operande[2], 5, temp_5bits);  
    strncpy(INST.rt, temp_5bits, 5);

    //Remplit l'instruction en binaire
    for (i = 0; i < 6; i++){
        instruct_binaire[i] = INST.opcode[j];
        j++;
    }
    j=0;
    for (i = 6; i < 11; i++){
        instruct_binaire[i] = INST.rs[j];
        j++;
    }
    j=0;
    for (i = 11; i < 16; i++){
        instruct_binaire[i] = INST.rt[j];
        j++;
    }
    j=0;
    for (i = 16; i < 21; i++){
        instruct_binaire[i] = INST.rd[j];
        j++;
    }
    j=0;
    for (i = 21; i < 26; i++){
        instruct_binaire[i] = INST.sa[j];
        j++;
    }
    j=0;
    for (i = 26; i < 32; i++){
        instruct_binaire[i] = INST.function[j];
        j++;
    }

    //printf("%8.8x\n", BinaireToDecimal(instruct_binaire));      //Affichage en hexa
}

void typeI_to_Binary(struct typeI INST, int operande[3]){
    // Initialisation
    char temp_5bits[5];
    char temp_16bits[16];
    int i, j = 0;    

    //Assigne les opérandes binaire dans la structure
    DecimalToBinaire(operande[0], 5, temp_5bits);      
    strncpy(INST.rt, temp_5bits, 5);
    DecimalToBinaire(operande[1], 5, temp_5bits);  
    strncpy(INST.rs, temp_5bits, 5);
    DecimalToBinaire(operande[2], 16, temp_16bits);  
    strncpy(INST.immediate, temp_16bits, 16);

    //Remplit l'instruction en binaire
    for (i = 0; i < 6; i++){
        instruct_binaire[i] = INST.opcode[j];
        j++;
    }
    j=0;
    for (i = 6; i < 11; i++){
        instruct_binaire[i] = INST.rs[j];
        j++;
    }
    j=0;
    for (i = 11; i < 16; i++){
        instruct_binaire[i] = INST.rt[j];
        j++;
    }
    j=0;
    for (i = 16; i < 32; i++){
        instruct_binaire[i] = INST.immediate[j];
        j++;
    }
   
    //printf("%8.8x\n", BinaireToDecimal(instruct_binaire));      //Affichage en hexa
}

void typeJ_to_Binary(struct typeJ INST, double index){
    // Initialisation
    char temp_26bits[26];
    int i, j = 0;    

    //Assigne les opérandes binaire dans la structure
    DecimalToBinaire(index, 26, temp_26bits);      
    strncpy(INST.target, temp_26bits, 26);

    //Remplit l'instruction en binaire
    for (i = 0; i < 6; i++){
        instruct_binaire[i] = INST.opcode[j];
        j++;
    }
    j=0;
    for (i = 6; i < 32; i++){
        instruct_binaire[i] = INST.target[j];
        j++;
    }

    //printf("%8.8x\n", BinaireToDecimal(instruct_binaire));      //Affichage en hexa
}

char* instruction_to_binaire(char* ligne){

    // Initialisation
    int operande[] = {0, 0, 0};
    int operande_temp;
    double index;
    char temp_5bits[5];
    char ligne_temp[22];
    strcpy(ligne_temp, ligne);

    // Récupère l'instruction
    int nb_instruction = detection_instruction(ligne_temp);

    //TYPE R
    if(nb_instruction == 0){        //ADD
        recup_adresses_typeR(ligne, operande);
        typeR_to_Binary(ADD, operande);
    }
    else if(nb_instruction == 2){   //AND
        recup_adresses_typeR(ligne, operande);
        typeR_to_Binary(AND, operande);
    }
    else if(nb_instruction == 7){   //DIV
        recup_adresses_typeR(ligne, operande);
        operande[2] = operande[1];
        operande[1] = operande[0];
        operande[0] = 0;
        typeR_to_Binary(DIV, operande);
    }
    else if(nb_instruction == 10){   //JR
        recup_adresses_typeR(ligne, operande);
        operande[1] = operande[0];
        operande[0] = 0;
        operande[0] = 0;
        typeR_to_Binary(JR, operande);
    }
    else if(nb_instruction == 13){   //MFHI
        recup_adresses_typeR(ligne, operande);
        typeR_to_Binary(MFHI, operande);
    }
    else if(nb_instruction == 14){   //MFLO
        recup_adresses_typeR(ligne, operande);
        typeR_to_Binary(MFLO, operande);
    }
    else if(nb_instruction == 15){   //MULT
        recup_adresses_typeR(ligne, operande);
        operande[2] = operande[1];
        operande[1] = operande[0];
        operande[0] = 0;
        typeR_to_Binary(MULT, operande);
    }
    else if(nb_instruction == 16){   //NOP
        recup_adresses_typeR(ligne, operande);
        typeR_to_Binary(NOP, operande);
    }
    else if(nb_instruction == 17){   //OR
        recup_adresses_typeR(ligne, operande);
        typeR_to_Binary(OR, operande);
    }
    else if(nb_instruction == 18){   //ROTR
        recup_donnee_typeI(ligne, operande);
        DecimalToBinaire(operande[2], 5, temp_5bits);  
        strncpy(ROTR.sa, temp_5bits, 5);
        operande[2] = operande[1];
        operande[1] = 1;
        typeR_to_Binary(ROTR, operande);
    }
    else if(nb_instruction == 19){   //SLL
        recup_donnee_typeI(ligne, operande);
        DecimalToBinaire(operande[2], 5, temp_5bits);  
        strncpy(SLL.sa, temp_5bits, 5);
        operande[2] = operande[1];
        operande[1] = 0;
        typeR_to_Binary(SLL, operande);
    }
    else if(nb_instruction == 20){   //SLT
        recup_adresses_typeR(ligne, operande);
        typeR_to_Binary(SLT, operande);
    }
    else if(nb_instruction == 21){   //SRL
        recup_donnee_typeI(ligne, operande);
        DecimalToBinaire(operande[2], 5, temp_5bits);  
        strncpy(SRL.sa, temp_5bits, 5);
        operande[2] = operande[1];
        operande[1] = 0;
        typeR_to_Binary(SRL, operande);
    }
    else if(nb_instruction == 22){   //SUB
        recup_adresses_typeR(ligne, operande);
        typeR_to_Binary(SUB, operande);
    }
    else if(nb_instruction == 25){   //XOR
        recup_adresses_typeR(ligne, operande);
        typeR_to_Binary(XOR, operande);
    }

    //TYPE I
    else if(nb_instruction == 1){        //ADDI
        recup_donnee_typeI(ligne, operande);
        typeI_to_Binary(ADDI, operande);
    }
    else if(nb_instruction == 3){        //BEQ
        recup_donnee_typeI(ligne, operande);
        operande_temp = operande[0];
        operande[0] = operande[1];
        operande[1] = operande_temp;
        typeI_to_Binary(BEQ, operande);
    }
    else if(nb_instruction == 4){        //BGTZ
        recup_donnee_typeI(ligne, operande);
        operande[2] = operande[1];
        operande[1] = operande[0];
        operande[0] = 0;
        typeI_to_Binary(BGTZ, operande);
    }
    else if(nb_instruction == 5){        //BLEZ
        recup_donnee_typeI(ligne, operande);
        operande[2] = operande[1];
        operande[1] = operande[0];
        operande[0] = 0;
        typeI_to_Binary(BLEZ, operande);
    }
    else if(nb_instruction == 6){        //BNE
        recup_donnee_typeI(ligne, operande);
        operande_temp = operande[0];
        operande[0] = operande[1];
        operande[1] = operande_temp;
        typeI_to_Binary(BNE, operande);
    }
    else if(nb_instruction == 11){        //LUI
        recup_donnee_typeI(ligne, operande);
        operande[2] = operande[1];
        operande[1] = 0;
        typeI_to_Binary(LUI, operande);
    }
    else if(nb_instruction == 12){  //LW
        recup_donnee_typeI(ligne, operande);
        operande_temp = operande[2];
        operande[2] = operande[1];
        operande[1] = operande_temp;
        typeI_to_Binary(LW, operande);
    }
    else if(nb_instruction == 23){  //SW
        recup_donnee_typeI(ligne, operande);
        operande_temp = operande[2];
        operande[2] = operande[1];
        operande[1] = operande_temp;
        typeI_to_Binary(SW, operande);
    }

    //Type J
    else if(nb_instruction == 8){   //J
        index = recup_index_typeJ(ligne);
        typeJ_to_Binary(J, index);
    }
    else if(nb_instruction == 9){   //JAL
        index = recup_index_typeJ(ligne);
        typeJ_to_Binary(JAL, index);
    }

    //Type S
    else if(nb_instruction == 24){   //SYSCALL
        strcpy(instruct_binaire, "00000000000000000000000000001100");
        //printf("%8.8x\n", BinaireToDecimal(instruct_binaire));
    }
    
    else{       //Aucune instruction dectecté
        printf("\nErreur : L'instruction est inconnue\n\n");
        exit( EXIT_FAILURE );
    }

    return instruct_binaire;
}
