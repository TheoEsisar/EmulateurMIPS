SW $12, 32767($31)
SW $20, -1($1)
#SW $10, 90($32)         # Erreur : Registre trop grand

# EXPECTED_ASSEMBLY
# afec7fff
# ac34ffff

# EXPECTED_FINAL_STATE
