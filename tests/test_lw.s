LW $2, 31($28)
LW $12, -32768($31)
# LW $10, 32768($1)           # Erreur : Valeur hors limite

# EXPECTED_ASSEMBLY
# 8f82001f
# 8fec8000

# EXPECTED_FINAL_STATE
