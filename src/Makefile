#Test Makefile

XCC     = gcc
AS	= as
LD  = ld
CFLAGS  = -c -fPIC -Wall -I. -I../io/include -mcpu=arm920t -msoft-float

ASFLAGS	= -mcpu=arm920t -mapcs-32

LDFLAGS = -init main -Map iotest.map -N  -T orex.ld -L/u/wbcowan/gnuarm-4.0.2/lib/gcc/arm-elf/4.0.2 -L../lib
# -g: include hooks for gdb
# -c: only compile
# -mcpu=arm920t: generate code for the 920t architecture
# -fpic: emit position-independent code
# -Wall: report all warnings
# -msoft-float: use software for floating point

all: tst.s tst.elf

tst.s: tst.c tst.h
	$(XCC) -S $(CFLAGS) tst.c
	
tst.o: tst.s
	$(AS) $(ASFLAGS) -o tst.o tst.s
	
tst.elf: tst.o
	$(LD) $(LDFLAGS) -o $@ tst.o -lbwio -lgcc
	

clean:
	-rm -f iotest.elf *.s *.o iotest.map
