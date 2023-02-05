// Module permettant de faire les opérations de chaque instruction

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include "execution.h"

int pc;
int pas_a_pas;
int nb_instruction;

int create_mask(int start, int end){
  int result=0;
  if(start > end){
    printf("Erreur masque impossible\n");
  }else{
    for(int i=start;i<=end;i++) result += 1<<i;
  }
  return result;
}

int execution(FILE* fichier_assemble, FILE* fichier_final, int pas_a_pas_tmp){
    init_registre();
    init_memoire();
    pas_a_pas = pas_a_pas_tmp;

    /*Partie récupérant les instructions héxa puis les transforme en décimal et les stocke dans un tableau*/
    fseek(fichier_assemble, 0, SEEK_SET);
    //int *instructions = NULL;
    nb_instruction = 0;
    int instruction;

    char* ligne = NULL;
    size_t taille_ligne = 0;
 
    while (getline(&ligne, &taille_ligne, fichier_assemble) != -1) {

        instruction = (int)(strtol(ligne, NULL, 16));   //Convertit l'hexa en entier
        ecrire_memoire(nb_instruction, instruction);
        ecrire_memoire(nb_instruction+1, -1);

        nb_instruction++;

        ligne = NULL;
        taille_ligne = 0;


    }
    free(ligne);
    /*Fin du remplissage du tableau d'instruction*/
    
    nb_instruction--;       //Utile pour compter le nombre d'instructions et empêcher les sauts invalides

    pc = lecture_registre(34);
    int temp_instruction = lecture_memoire(pc/4);


    while (temp_instruction != -1) //Voir quelle condition il faut mettre pour stopper l'éxécution
    {
        execution_instruction(temp_instruction, 0);
        temp_instruction = lecture_memoire(pc/4);
    }

    if(pas_a_pas == 0){
        for (int i = 0; i < 32; i++)
        {
            if (lecture_registre(i) != 0)
            {
                if (i<10)
                {
                    fprintf(fichier_final, "$0%d:%d\n", i, lecture_registre(i));
                }
                else
                {
                    fprintf(fichier_final, "$%d:%d\n", i, lecture_registre(i));
                }
            }
            
            
            
        }
        if (lecture_registre(32) != 0 || lecture_registre(33) != 0)
        {
            fprintf(fichier_final, "HI:%d\n", lecture_registre(32));
            fprintf(fichier_final, "LO:%d\n", lecture_registre(33));
        }
        
        // fprintf(fichier_final, "PC : %d\n", lecture_registre(34)); Pas d'affichage du PC final en mode automatique
        
    }
    return 1;
}

int execution_instruction(int temp_instruction, int delay_slot){
    int opcode = 0;
    int rs, rt, rd, sa, base, target;
    signed short immediate, offset;
    char buffer;


    pc +=4;
    
    if (delay_slot == 1 && pas_a_pas == 1)
    {
        printf("\nExécution de l'instruction dans le delay slot ...\n");
    }
    
    if (temp_instruction == -1)
    {
        return 0;
    }
    

    opcode = (create_mask(26,31) & temp_instruction)>>26;
        if (opcode == 0)        //TYPE R
        {
            opcode = (create_mask(0,5) & temp_instruction);
            rs = (create_mask(21,25) & temp_instruction)>>21;
            rt = (create_mask(16,20) & temp_instruction)>>16;
            rd = (create_mask(11,15) & temp_instruction)>>11;
            sa = (create_mask(6,10) & temp_instruction)>>6;  
            if (opcode == 32)   //ADD
            {
                if(pas_a_pas == 1){
                    printf("ADD $%d, $%d, $%d\n", rd, rs, rt);
                }
                exec_add(rs, rt, rd);
            }
            else if (opcode == 36)   //AND
            {   
                if(pas_a_pas == 1){
                    printf("AND $%d, $%d, $%d\n", rd, rs, rt);
                }
                exec_and(rs, rt, rd);
            }
            else if (opcode == 26)   //DIV
            {   
                if(pas_a_pas == 1){
                    printf("DIV $%d, $%d\n", rs, rt);
                }
                exec_div(rs, rt);
            }
            else if (opcode == 8)   //JR
            {
                if(pas_a_pas == 1){
                    printf("JR $%d\n", rs);
                }
                exec_jr(rs);
            }            
            else if (opcode == 16)   //MFHI
            {   
                if(pas_a_pas == 1){
                    printf("MHFI $%d\n", rd);
                }
                exec_mfhi(rd);
            }
            else if (opcode == 18)   //MFLO
            {   
                if(pas_a_pas == 1){
                    printf("MFLO $%d\n", rd);
                }
                exec_mflo(rd);
            }
            else if (opcode == 24)   //MULT
            {   
                if(pas_a_pas == 1){
                    printf("MULT $%d, $%d\n", rs, rt);
                }
                exec_mult(rs, rt);
            }
            /*else if (opcode == 0)   //NOP
            {   
                exec_nop();             PAS NECESSAIRE CAR NOP EFFECTUE SLL de R0, R0, R0
            }*/ 
            else if (opcode == 37)   //OR
            {   
                if(pas_a_pas == 1){
                    printf("OR $%d, $%d, $%d\n", rd, rs, rt);
                }
                exec_or(rs, rt, rd);
            }
            else if (opcode == 2 && rs == 1)   //ROTR
            {   
                if(pas_a_pas == 1){
                    printf("ROTR $%d, $%d, $%d\n", rd, rt, sa);
                }
                exec_rotr(rd, rt, sa);
            }
            else if (opcode == 0)   //SLL
            {   
                if(pas_a_pas == 1){
                    printf("SLL $%d, $%d, %d\n", rd, rt, sa);
                }
                exec_sll(rd, rt, sa);
            }
            else if (opcode == 42)   //SLT
            {   
                if(pas_a_pas == 1){
                    printf("SLT $%d, $%d, $%d\n", rd, rs, rt);
                }
                exec_slt(rd, rs, rt);
            }
            else if (opcode == 2 && rs == 0)   //SRL
            {   
                if(pas_a_pas == 1){
                    printf("SRL $%d, $%d, $%d\n", rd, rt, sa);
                }
                exec_srl(rd, rt, sa);
            }
            else if (opcode == 34)   //SUB
            {   
                if(pas_a_pas == 1){
                    printf("SUB $%d, $%d, $%d\n", rd, rs, rt);
                }
                exec_sub(rd, rs, rt);
            }
            else if (opcode == 12)   //SYSCALL
            {   if(pas_a_pas == 1){
                    printf("SYSCALL\n");
                }
                exec_syscall();
            }
            else if (opcode == 38)   //XOR
            {   
                if(pas_a_pas == 1){
                    printf("XOR $%d, $%d, $%d\n", rd, rs, rt);
                }
                exec_xor(rd, rs, rt);
            }
               
        }
        else if (opcode == 8)   //ADDI
        {   
            rs = (create_mask(21,25) & temp_instruction)>>21;
            rt = (create_mask(16,20) & temp_instruction)>>16;
            immediate = (create_mask(0,15) & temp_instruction);
            if(pas_a_pas == 1){
                printf("ADDI $%d, $%d, %d\n", rt, rs, immediate);
            }
            exec_addi(rt, rs, immediate);
        }
        else if (opcode == 4)   //BEQ
        {

            rs = (create_mask(21,25) & temp_instruction)>>21;
            rt = (create_mask(16,20) & temp_instruction)>>16;
            offset = (create_mask(0,15) & temp_instruction);
            if(pas_a_pas == 1){
                printf("BEQ $%d, $%d, %d\n", rs, rt, offset);
            }
            exec_beq(rt, rs, offset);
        }
        else if (opcode == 7)   //BGTZ
        {
            rs = (create_mask(21,25) & temp_instruction)>>21;
            offset = (create_mask(0,15) & temp_instruction);
            if(pas_a_pas == 1){
                printf("BGTZ $%d, %d\n", rs, offset);
            }
            exec_bgtz(rs, offset);
        }
        else if (opcode == 6)   //BLEZ
        {
            rs = (create_mask(21,25) & temp_instruction)>>21;
            offset = (create_mask(0,15) & temp_instruction);
            if(pas_a_pas == 1){
                printf("BLEZ $%d, %d\n", rs, offset);
            }
            exec_blez(rs, offset);
        }
        else if (opcode == 5)   //BNE
        {

            rs = (create_mask(21,25) & temp_instruction)>>21;
            rt = (create_mask(16,20) & temp_instruction)>>16;
            offset = (create_mask(0,15) & temp_instruction);
            if(pas_a_pas == 1){
                    printf("BNE $%d, $%d, %i\n", rs, rt, offset);
                }
            exec_bne(rt, rs, offset);
        }        
        else if (opcode == 15)      //LUI
        {
            rt = (create_mask(16,20) & temp_instruction)>>16;
            immediate = (create_mask(0,15) & temp_instruction);
            if(pas_a_pas == 1){
                    printf("LUI $%d, %d\n", rt, immediate);
                }
            exec_lui(rt, immediate);
        }
        else if (opcode == 35)      //LW
        {
            base = (create_mask(21,25) & temp_instruction)>>21;
            rt = (create_mask(16,20) & temp_instruction)>>16;
            offset = (create_mask(0,15) & temp_instruction);
            if(pas_a_pas == 1){
                    printf("LW $%d, %d($%d)\n", rt, offset, base);
                }
            exec_lw(rt, offset, base);
        }
        else if (opcode == 43)      //SW
        {
            base = (create_mask(21,25) & temp_instruction)>>21;
            rt = (create_mask(16,20) & temp_instruction)>>16;
            offset = (create_mask(0,15) & temp_instruction);
            if(pas_a_pas == 1){
                    printf("SW $%d, %d($%d)\n", rt, offset, base);
                }
            exec_sw(rt, offset, base);
        }
        else if (opcode == 2)       //J
        {
            target = (create_mask(0,25) & temp_instruction);
            if(pas_a_pas == 1){
                    printf("J %d\n", target);
                }
            exec_j(target);
        }
        else if (opcode == 3)       //JAL
        {
            target = (create_mask(0,25) & temp_instruction);
            if(pas_a_pas == 1){
                    printf("JAL %d\n", target);
                }
            exec_jal(target);
        }

        ecrire_registre(34, pc);                        //Actualisation du PC
        
        if (pas_a_pas == 1 && delay_slot == 0)
        {
            printf("%8.8x\n", temp_instruction);
            //affiche_memoire();
            affiche_registre();
            scanf("%c", &buffer); 
        }

        return 0;
}





/*Execution de chaque instruction*/




// TYPE R

void exec_add(int rs, int rt, int rd){
    // Protection overflow
    double d1 = lecture_registre(rs);
    double d2 = lecture_registre(rt);
    double test_overflow = d1 + d2;
    int temp;
    if (test_overflow > 2147483647 || test_overflow < - 2147483648){
        printf("\nInteger Overflow\n\n");
    }
    else{
        temp = lecture_registre(rs) + lecture_registre(rt);
        ecrire_registre(rd, temp);
    }
}

void exec_and(int rs, int rt, int rd){
    int temp = lecture_registre(rs) & lecture_registre(rt);
    ecrire_registre(rd, temp);
}

void exec_div(int rs, int rt){
    if(lecture_registre(rt) == 0){  // Division par zéro
        printf("Division par zéro\n");
        ecrire_registre(33, 0); //33 correspond à la case LO du tableau de registres.
        ecrire_registre(32, 0); //32 correspond à la case HI du tableau de registres.
    }
    else{
        int q = lecture_registre(rs)/lecture_registre(rt);
        ecrire_registre(33, q); //33 correspond à la case LO du tableau de registres.
        int r = lecture_registre(rs)%lecture_registre(rt);
        ecrire_registre(32, r); //32 correspond à la case HI du tableau de registres.
    }
}

void exec_jr (int rs){  //JR
    if (lecture_registre(rs) > nb_instruction*4 || lecture_registre(rs) < 0)
    {
        printf("Saut à l'adresse %08x invalide !\n", lecture_registre(rs));
    }
    else{
        int delay_slot = lecture_memoire(pc/4);     //DELAY SLOT
        execution_instruction(delay_slot, 1);
        pc -= 4;
    
        pc = lecture_registre(rs);
    }
    
}

void exec_mfhi(int rd){ //MFHI
    ecrire_registre(rd, lecture_registre(32));
}

void exec_mflo(int rd){ //MLFO
    ecrire_registre(rd, lecture_registre(33));
}

void exec_mult(int rs, int rt){ //MULT
    int32_t a = lecture_registre(rs);
    int32_t b = lecture_registre(rt);
    int64_t prod = (int64_t) a*b;
    ecrire_registre(33, (int)(prod & 0xffffffff));
    ecrire_registre(32, (int)(prod>>32));    //A voir comment ça marche
}

/*void exec_nop(){    //NOP
    exec_sll(0, 0, 0);              PAS NECESSAIRE CAR NOP EFFECTUE SLL de R0, R0, R0
}*/

void exec_or(int rs, int rt, int rd){   //OR
    int temp = lecture_registre(rs) | lecture_registre(rt);
    ecrire_registre(rd, temp); 
}

void exec_rotr(int rd, int rt, int sa){ //ROTR
    int value = lecture_registre(rt);
    int temp = ((value >> sa) | (value << (32 - sa)));
    ecrire_registre(rd, temp);
}

void exec_sll(int rd, int rt, int sa){  //SLL
    int temp = (lecture_registre(rt) << sa);          // A corriger ?!
    ecrire_registre(rd, temp);
}

void exec_slt(int rd, int rs, int rt){  //SLT
    int temp = (lecture_registre(rs)<lecture_registre(rt));
    ecrire_registre(rd, temp);
}

void exec_srl(int rd, int rt, int sa){  //SRL
    int temp = (lecture_registre(rt) >> sa);
    ecrire_registre(rd, temp);
}

void exec_sub(int rd, int rs, int rt){  //SUB
    // Protection overflow
    double d1 = lecture_registre(rs); 
    double d2 = lecture_registre(rt);
    double test_overflow = d1 - d2;
    int temp;
    if (test_overflow > 2147483647 || test_overflow < - 2147483648){
        printf("\nInteger Overflow\n\n");
    }
    else{
        temp = lecture_registre(rs) - lecture_registre(rt);
        ecrire_registre(rd, temp);
    }
    
}

void exec_xor(int rd, int rs, int rt){  //XOR
    int temp = lecture_registre(rs) ^ lecture_registre(rt);
    ecrire_registre(rd, temp);
}



//TYPE I

void exec_addi(int rt, int rs, int immediate){  //ADDI
    // Protection overflow
    double d1 = lecture_registre(rs);
    double d2 = immediate;
    double test_overflow = d1 + d2;
    int temp;
    if (test_overflow > 2147483647 || test_overflow < - 2147483648){
        printf("\nInteger Overflow\n\n");
    }
    else{
        temp = lecture_registre(rs) + (signed short)immediate;
        ecrire_registre(rt, temp);
    }
}

void exec_beq(int rt, int rs, int offset){  //BEQ
    


    int delay_slot = lecture_memoire(pc/4);
    
    if (offset & create_mask(15,15))    //A vérifier
    {
        offset = offset | create_mask(16,31);
    }
    if (lecture_registre(rs) == lecture_registre(rt))
    {
        if ((pc + (offset<<2)) > nb_instruction*4 || (pc + (offset<<2)) < 0)
        {
            printf("Saut à l'adresse %08x invalide !\n", (pc + (offset<<2)));
        }
        else{
            execution_instruction(delay_slot, 1);
            pc -= 4;

            pc = pc + (offset<<2);
        }
    }
    else{
        execution_instruction(delay_slot, 1);
    }
  
}

void exec_bgtz(int rs, int offset){ //BGTZ

    int delay_slot = lecture_memoire(pc/4);

    if (offset & create_mask(15,15))
    {
        offset = offset | create_mask(16,31);
    }
    if (lecture_registre(rs) > 0)
    {
        if ((pc + (offset<<2)) > nb_instruction*4 || (pc + (offset<<2)) < 0)
        {
            printf("Saut à l'adresse %08x invalide !\n", (pc + (offset<<2)));
        }
        else{
            execution_instruction(delay_slot, 1);
            pc -= 4;

            pc = pc + (offset<<2);
        }
    }
    else{
        execution_instruction(delay_slot, 1);
    }  
}

void exec_blez(int rs, int offset){ //BLEZ

    int delay_slot = lecture_memoire(pc/4);

    if (offset & create_mask(15,15))
    {
        offset = offset | create_mask(16,31);
    }
    if (lecture_registre(rs) <= 0)
    {
        if ((pc + (offset<<2)) > nb_instruction*4 || (pc + (offset<<2)) < 0)
        {
            printf("Saut à l'adresse %08x invalide !\n", (pc + (offset<<2)));
        }
        else{
            execution_instruction(delay_slot, 1);
            pc -= 4;

            pc = pc + (offset<<2);
        }
    }
    else{
        execution_instruction(delay_slot, 1);
    }  
}

void exec_bne(int rt, int rs, int offset){  //BNE

    int delay_slot = lecture_memoire(pc/4);

    if (offset & create_mask(15,15))
    {
        offset = offset | create_mask(16,31);
    }
    if (lecture_registre(rs) != lecture_registre(rt))
    {
        if ((pc + (offset<<2)) > nb_instruction*4 || (pc + (offset<<2)) < 0)
        {
            printf("Saut à l'adresse %08x invalide !\n", (pc + (offset<<2)));
        }
        else{
            execution_instruction(delay_slot, 1);
            pc -= 4;

            pc = pc + (offset<<2);
        }
    }
    else{
        execution_instruction(delay_slot, 1);
    }
}

void exec_lui (int rt, int immediate){  //LUI
    int temp = immediate << 16;
    ecrire_registre(rt, temp);
}

void exec_lw(int rt, int offset, int base){ //LW
    int temp = lecture_memoire(lecture_registre(base) + offset);
    ecrire_registre(rt, temp);
}

void exec_sw(int rt, int offset, int base){ //SW
    int temp = lecture_registre(rt);
    ecrire_memoire(lecture_registre(base) + offset, temp);
}


//TYPE J

void exec_j(int target){    //J
    
    if (target > nb_instruction || target < 0)
    {
        printf("Saut à l'adresse %08x invalide !\n", (target<<2));
    }
    else
    {
        int delay_slot = lecture_memoire(pc/4);     //DELAY SLOT
        execution_instruction(delay_slot, 1);
        pc -= 4;

        pc = (pc & create_mask(28,31)) + (target<<2);
    } 
}

void exec_jal(int target){  //JAL

    if (target > nb_instruction || target < 0)
    {
        printf("Saut à l'adresse %08x invalide !\n", (target<<2));
    }
    else
    {
        int delay_slot = lecture_memoire(pc/4);     //DELAY SLOT
        execution_instruction(delay_slot, 1);
        pc -= 4;

        ecrire_registre(31, pc+4);      //PC déjà incrémenté de 4 lors de l'éxecution de l'instruction donc 4+4 = 8
        pc = (pc & create_mask(28,31)) | (target<<2);
    }
    
}


//SYSCALL
void exec_syscall(void){
    printf("\nSyscall Exit\n\n"); // Quitte le programme
    exit( EXIT_FAILURE );
}