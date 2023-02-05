# Rappel sur les delay slots:
# - Pour des raisons d'optimisation, durant un saut l'instruction après le saut
#   (le "delay slot") est exécutée à la volée.
# - L'exécution doit se faire dans cet ordre:
#   1. En arrivant sur l'instruction de saut, calcul de la destination du saut
#      et de la condition si le saut est conditionnel.
#   2a. Si le saut se fait:
#       3a. Exécution du delay slot
#       4a. Poursuite de l'exécution à la cible du saut
#   2b. Si le saut ne se fait pas:
#       3b. Exécution du delay slot
#       4b. Poursuite de l'exécution à l'instruction qui suit le delay slot

# D'abord on fait un test où le saut ne se fait pas.
ADDI $1, $0, 12
BEQ $1, $0, 2
ADDI $2, $0, 16
ADDI $1, $1, 4

# Ensuite un test où le saut se fait.
BEQ $1, $2, 3
ADDI $3, $0, 6
ADDI $1, $1, 1000
ADDI $2, $2, 1000

# Ici la branche n'est pas prise parce que $1 et $3 sont différents. Mais pour
# le voir il faut calculer la condition avant d'exécuter le delay slot.
BEQ $1, $3, 2
ADDI $3, $3, 10
ADDI $3, $3, 2

# De même, cette branche est prise si vous calculez correctement la condition
# (ie. avant le delay slot).
SUB $4, $1, $3
BLEZ $4, 2
ADDI $1, $1, 4
ADDI $4, $4, 1000

# Cas intéressant pour finir : si on prend un saut de longueur 0, on exécute le
# delay slot deux fois (mais si on ne le prend pas on ne l'exécute qu'une fois)
BEQ $0, $0, 0
ADDI $5, $5, 1

BNE $0, $0, 0
ADDI $6, $6, 1

ADDI $2, $2, 8

# EXPECTED_ASSEMBLY
# 2001000c
# 10200002
# 20020010
# 20210004
# 10220003
# 20030006
# 202103e8
# 204203e8
# 10230002
# 2063000a
# 20630002
# 00232022
# 18800002
# 20210004
# 208403e8
# 10000000
# 20a50001
# 14000000
# 20c60001
# 20420008

# EXPECTED_FINAL_STATE
# $01:20
# $02:24
# $03:18
# $04:-2
# $05:2
# $06:1