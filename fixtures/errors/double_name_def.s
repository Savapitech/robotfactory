.name "Double name def"
.name "Double name def"
.comment "double name def"

	sti r1, %:hi, %1

hi:	live %234
	ld %0, r3
	zjmp %:hi
