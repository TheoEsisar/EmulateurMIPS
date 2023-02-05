BEQ $10, $0, 1
BEQ $30, $28, -32768
# BEQ $15, $38, 5        # Erreur : Registre trop grand

# EXPECTED_ASSEMBLY
# 11400001
# 13dc8000

# EXPECTED_FINAL_STATE
