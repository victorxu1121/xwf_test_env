VPATH=src

build: libmycl.so
	#build the lib of log reminder  
	#ar crv $@ libmylr.a logreminder.o
libmycl.so: cmdline.o
	gcc -o $@ -shared $<

cmdline.o: cmdline.c cmdline.h
	gcc -c -fPIC src/cmdline.c src/cmdline.h

test: main.c libmycl.so
	gcc src/main.c -L. -lmycl -o test.o
	LD_LIBRARY_PATH=. ./test.o

#abc: cmdline.c cmdline.h main.c
#	gcc src/cmdline.c src/cmdline.h src/main.c -o test.o

clean:
	rm *.so
	rm test.o 


