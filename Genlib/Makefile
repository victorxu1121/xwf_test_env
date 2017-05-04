build:lib/libmax.so

libmax.so: lib/max.o
	gcc -o $@ -shared $<

max.o: src/max.c
	gcc -c -fPIC $<

test: a.out

a.out: src/main.c lib/libmax.so
	gcc main.c -L. -lmax
	LD_LIBRARY_PATH=. ./a.out

clean:
	rm -f lib/*.o src/*.so a.out





