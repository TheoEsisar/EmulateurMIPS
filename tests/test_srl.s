ADDI $1, $0, 1
SLL $7, $1, 10
SLL $20, $1, 30

SRL $8, $7, 10
SRL $0, $20, 30
# SRL $-0, $4, 9         # Erreur : Caractère non respecté

# EXPECTED_ASSEMBLY
# 20010001
# 00013a80
# 0001a780
# 00074282
# 00140782

# EXPECTED_FINAL_STATE
# $00:1
# $01:1
# $07:1024
# $08:1
# $20:1073741824
