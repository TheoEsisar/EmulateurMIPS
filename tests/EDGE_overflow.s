# $2 = 2
ADDI $2, $0, 2
# $3 = 2³¹-1 (maximum signed integer)
SLL $3, $2, 29
ADDI $3, $3, -1
ADD $3, $3, $3
ADDI $3, $3, 1
# $4 = -2³¹ (minimum signed integer)
SUB $4, $0, $3
ADDI $4, $4, -1
# $5 = -2
SUB $5, $0, $2

# Overflows on ADD: positive, negative
ADD $6, $3, $2
ADD $7, $4, $5

# Overflow on ADDI
ADDI $8, $3, 1
ADDI $9, $4, -1

# Overflow on SUB
SUB $10, $3, $5
SUB $11, $4, $2

# Overflow on MULT
ADDI $12, $0, -1
MULT $4, $12

# EXPECTED_ASSEMBLY
# 20020002
# 00021f40
# 2063ffff
# 00631820
# 20630001
# 00032022
# 2084ffff
# 00022822
# 00623020
# 00853820
# 20680001
# 2089ffff
# 00655022
# 00825822
# 200cffff
# 008c0018

# EXPECTED_FINAL_STATE
# $02:2
# $03:2147483647
# $04:-2147483648
# $05:-2
# $12:-1
# HI:0
# LO:-2147483648
