LUI $5, 999
LUI $22, -15
#LUI $12, test       # Erreur : Caractère non respecté

# EXPECTED_ASSEMBLY
# 3c0503e7
# 3c16fff1

# EXPECTED_FINAL_STATE
# $05:65470464
# $22:-983040