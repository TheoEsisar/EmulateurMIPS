#include "memoire.h"
#include "registre.h"

// Module permettant de faire les opérations de chaque instruction
int create_mask(int start, int end);
int execution(FILE* fichier_assemble, FILE* fichier_final, int pas_a_pas_tmp);
int execution_instruction(int instruction, int delay_slot);


//TYPE R
void exec_add(int rs, int rt, int rd);
void exec_and(int rs, int rt, int rd);
void exec_div(int rs, int rt);
void exec_jr (int rs);
void exec_mfhi(int rd);
void exec_mflo(int rd);
void exec_mult(int rs, int rt);
void exec_nop(void);
void exec_or(int rs, int rt, int rd);
void exec_rotr(int rd, int rt, int sa);
void exec_sll(int rd, int rt, int sa);
void exec_slt(int rd, int rs, int rt);
void exec_srl(int rd, int rt, int sa);
void exec_sub(int rd, int rs, int rt);
void exec_syscall(void);
void exec_xor(int rd, int rs, int rt);


//TYPE I
void exec_addi(int rt, int rs, int immediate);
void exec_beq(int rt, int rs, int offset);
void exec_bgtz(int rs, int offset);
void exec_blez(int rs, int offset);
void exec_bne(int rt, int rs, int offset);
void exec_lui (int rt, int immediate);
void exec_lw(int rt, int offset, int base);
void exec_sw(int rt, int offset, int base);


//TYPE J
void exec_j(int target);
void exec_jal(int target);