VPATH=src

build: libmylr.so
	#build the lib of log reminder  
	#ar crv $@ libmylr.a logreminder.o
libmylr.so: logreminder.o
	gcc -o $@ -shared $<

logreminder.o: logreminder.c logreminder.h
	gcc -c -fPIC src/logreminder.c src/logreminder.h

test: main.c libmylr.so
	gcc src/main.c -L. -lmylr -o test.o
	LD_LIBRARY_PATH=. ./test.o

clean:
	rm *.so
	rm test.o
	find LogFile '*.txt' -type f -print -exec rm {} \; 

