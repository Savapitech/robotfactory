.name "Double label"
.comment "double label"

	sti r1, %:hi, %1

hi:	live %234
	ld %0, r3
	zjmp %:hi

hi: ld %0, r2
