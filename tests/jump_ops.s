# Tests des sauts conditionnels. Il n'y a pas grand-chose de subtil ici car les
# delay slots sont tous NOP, donc vous obtiendrez le bon résultat même si vous
# ne gérez pas le delay slots correctement. Ici le but c'est juste de vérifier
# que vous sautez au bon endroit et quand il faut.

ADDI $1, $0, 32

# Saut à l'instruction #4 du programme (comptée à partir du début, en
# commençant à #0), c'est-à-dire le JAL
J 4
NOP                  # Delay slot
ADDI $10, $0, 1000   # Pas exécutée car on a sauté

# Saut à l'instruction #8 (le BEQ) ; de plus, $31 <- PC+8 = 16+8 = 24
JAL 8
NOP                  # Delay slot
ADDI $11, $0, 1000   # Pas exécutée car on a sauté
ADDI $12, $0, 1000   # Pas exécutée car on a sauté

# On saute par-dessus 2 instructions car $0 = $0
BEQ $0, $0, 2
NOP                  # Delay slot
ADDI $13, $0, 1000   # Pas exécutée car on a sauté

# On essaie de sauter 2 instructions, mais $1 = 32 != $0; donc on ne saute pas
BEQ $1, $0, 2
NOP                  # Delay slot
ADDI $1, $1, -16     # Exécutée car on n'a pas sauté

# On saute car $1 > 0
BGTZ $1, 2
NOP
ADDI $14, $0, 1000

# On ne saute pas car $1 n'est pas <= 0
BLEZ $1, 3
NOP
NOP
ADDI $2, $0, -4

# On ne saute pas car $0 n'est pas > 0
BGTZ $0, 2
NOP
ADDI $2, $2, -4

# On saute car $0 <= 0
BLEZ $0, 3
NOP
ADDI $15, $0, 1000
ADDI $16, $0, 1000

# On ne saute pas car $2 = -8 n'est pas > 0
BGTZ $2, 2
NOP
ADDI $2, $2, -4

# On saute car $2 = -12 est <= 0
BLEZ $2, 2
NOP
ADDI $17, $0, 1000

# On saute car $1 != $2
BNE $1, $2, 3
NOP
ADDI $18, $0, 1000
ADDI $19, $0, 1000

# On ne saute pas car $2 n'est pas != $2
BNE $2, $2, 2
NOP
ADD $3, $1, $2

# Saut de 0 instructions
BEQ $0, $0, 0
NOP

# EXPECTED_ASSEMBLY
# 20010020
# 08000004
# 00000000
# 200a03e8
# 0c000008
# 00000000
# 200b03e8
# 200c03e8
# 10000002
# 00000000
# 200d03e8
# 10200002
# 00000000
# 2021fff0
# 1c200002
# 00000000
# 200e03e8
# 18200003
# 00000000
# 00000000
# 2002fffc
# 1c000002
# 00000000
# 2042fffc
# 18000003
# 00000000
# 200f03e8
# 201003e8
# 1c400002
# 00000000
# 2042fffc
# 18400002
# 00000000
# 201103e8
# 14220003
# 00000000
# 201203e8
# 201303e8
# 14420002
# 00000000
# 00221820
# 10000000
# 00000000

# EXPECTED_FINAL_STATE
# $01:16
# $02:-12
# $03:4
# $31:24