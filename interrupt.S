#define FIRST_EXTERNAL_VECTOR 0x20
#define NR_VECTORS 256

#define ENTRY(name)	\
.global name;	\
name:
#define END(name)	\
.size name, . - name

.section .init.rodata,"a"
ENTRY(interrupt)
interrupt:
.text
	.p2align 5
	.p2align 6
ENTRY(irq_entries_start)
vector=FIRST_EXTERNAL_VECTOR
.rept (NR_VECTORS-FIRST_EXTERNAL_VECTOR+6)/7
	.balign 32
  .rept	7
    .if vector < NR_VECTORS
1:	pushl $(~vector+0x80)	/* Note: always in signed byte range */
      .if ((vector-FIRST_EXTERNAL_VECTOR)%7) <> 6
	jmp 2f
      .endif
      .previous
	.long 1b
      .text
vector=vector+1
    .endif
  .endr
2:	jmp common_interrupt
.endr
END(irq_entries_start)

.previous
END(interrupt)
.previous

common_interrupt:

