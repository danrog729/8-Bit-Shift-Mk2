const val1 126
const val2 112

# jump addresses
const compare 24
const aLessThanB 52
const aGreaterThanB 72
const equal 92

# put a 1 into reg6
imm 1
sav reg6

# put the values into reg0 and reg1
imm val1
sav reg0
imm val2
sav reg1

# put reg0 * -1 into reg2
not reg0
add reg6
sav reg2

# put reg1 * -1 into reg3
not reg1
add reg6
sav reg3

# check if a == b, a < b or a > b
imm aLessThanB
sav reg7
mov reg3
add reg0 # val1-val2
jmp reg7 # a < b
imm aGreaterThanB
sav reg7
mov reg2
add reg1 # val2-val1
jmp reg7 # a > b
imm equal
sav reg7
not reg6 # -2
jmp reg7 # a == b

# subtract a from b, put into b
imm compare
sav reg7
mov reg1
add reg2
sav reg1
# put reg1 * -1 into reg3
not reg1
add reg6
sav reg3
not reg6 # -2
jmp reg7

# subtract b from a, put into a
imm compare
sav reg7
mov reg0
add reg3
sav reg0
# put reg0 * -1 into reg2
not reg0
add reg6
sav reg2
not reg6 # -2
jmp reg7

# return a or b, they are equal
imm 0
out reg0