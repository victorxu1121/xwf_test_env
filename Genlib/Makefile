VPATH = src
build:libmax.so

libmax.so: max.o
	gcc -o $@ -shared $<

max.o: max.c
	gcc -c -fPIC $<

test: a.out

a.out: main.c libmax.so
	gcc src/main.c -L. -lmax
	LD_LIBRARY_PATH=. ./a.out

clean:
	rm -f *.o *.so a.out





