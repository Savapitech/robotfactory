.name "All types" 
.comment "check argument length"

live %42
ld %42, r1
ld 69, r1
st r1, r2
st r1, 42
add r1, r2, r3
sub r1, r2, r3
and %42, %42, r1
and 69, %42, r1
and %42, 69, r1
and r1, r2, r3
and r1, %42, r3
and r1, 69, r3
zjmp %42
ldi r1, r2, r3
ldi %42, r2, r3
ldi 69, r2, r3
ldi r1, %42, r3
ldi %42, %42, r3
ldi 69, %42, r3
fork %42
lld %42, r1
lld 69, r1
lfork %42
aff r1
