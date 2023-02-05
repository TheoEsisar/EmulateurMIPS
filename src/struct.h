#include <stdio.h>
#include <string.h>
#include "recup_instruction.h"

struct typeR
{
    char opcode[6];
    char rs[5];
    char rt[5];
    char rd[5];
    char sa[5];
    char function[6];
};

struct typeI
{
    char opcode[6];
    char rs[5];
    char rt[5];
    char immediate[16];
};

struct typeJ
{
    char opcode[6];
    char target[26] ;
};

struct typeS
{
    char special[6];
    char code[20];
    char syscall[6];
};

void typeR_to_Binary(struct typeR INST, int operande[3]);

// A retrailler ne peut pas fonctionner
// Enlever les partie sans valeur
// Objectif initialser pour chaque instrcution les valeurs par défauts

// Type R
struct typeR ADD = {.opcode = "000000", .sa = "00000", .function = "100000"};
struct typeR AND = {.opcode = "000000", .sa = "00000", .function = "100100"};
struct typeR DIV = {.opcode = "000000", .rd = "00000", .sa = "00000", .function = "011010"};
struct typeR JR = {.opcode = "000000", .rt = "00000", .rd = "00000", .sa = "00000", .function = "001000"};
struct typeR MFHI = {.opcode = "000000", .rs = "00000", .rt = "00000", .sa = "00000", .function = "010000"};
struct typeR MFLO = {.opcode = "000000", .rs = "00000", .rt = "00000", .sa = "00000", .function = "010010"};
struct typeR MULT = {.opcode = "000000", .rd = "00000", .sa = "00000", .function = "011000"};
struct typeR NOP = {.opcode = "000000", .rs = "00000", .rt = "00000", .rd = "00000", .sa = "00000", .function = "000000"};
struct typeR OR = {.opcode = "000000", .sa = "00000", .function = "100101"};
struct typeR ROTR = {.opcode = "000000", .rs = "00001", .function = "000010"}; 
struct typeR SLL = {.opcode = "000000", .rs = "00000", .function = "000000"};
struct typeR SLT = {.opcode = "000000", .sa = "00000", .function = "101010"};
struct typeR SRL = {.opcode = "000000", .rs = "00000", .function = "000010"};
struct typeR SUB = {.opcode = "000000", .sa = "00000", .function = "100010"};
struct typeR XOR = {.opcode = "000000", .sa = "00000", .function = "100110"};

// Type I
struct typeI ADDI = {.opcode = "001000"};
struct typeI BEQ = {.opcode = "000100"};
struct typeI BGTZ = {.opcode = "000111", .rt = "00000"};
struct typeI BLEZ = {.opcode = "000110", .rt = "00000"};
struct typeI BNE = {.opcode = "000101"};
struct typeI LUI = {.opcode = "001111", .rs = "00000"};
struct typeI LW = {.opcode = "100011", .rs = "00000"};
struct typeI SW = {.opcode = "101011", .rs = "00000"};

// Type J
struct typeJ J = {.opcode = "000010"};
struct typeJ JAL = {.opcode = "000011"};

// Type S
struct typeS SYSCALL = {.special = "000000", .code = "00000000000000000000", .syscall = "001100"};
