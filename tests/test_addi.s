ADDI $9, $13, 32598
ADDI $31, $15, -1
ADDI $22, $22, 0
# ADDI $10, $9, 40000  # Erreur : Valeur hors limite

# EXPECTED_ASSEMBLY
# 21a97f56
# 21ffffff
# 22d60000

# EXPECTED_FINAL_STATE
# $09:32598
# $31:-1
