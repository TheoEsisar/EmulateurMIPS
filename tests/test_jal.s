JAL 1
NOP
# JAL 67108862          # Erreur : Index trop grand
# JAL -10000            # Erreur : Caractère non respecté

# EXPECTED_ASSEMBLY
# 0c000001
# 00000000

# EXPECTED_FINAL_STATE
# $31:8
