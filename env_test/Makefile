VPATH=src
VPATH=lib

#build: libmylr.so
	#build the lib of log reminder  
	#ar crv $@ libmylr.a logreminder.o
#libmylr.so: logreminder.o
#	gcc -o $@ -shared $<

#logreminder.o: logreminder.c logreminder.h
#	gcc -c -fPIC src/logreminder.c src/logreminder.h

test: src/main.c lib/libmylr.so lib/libmycl.so
	gcc src/main.c -L ./lib -lmylr -lmycl -lpthread -o test.o
	LD_LIBRARY_PATH=./lib 
	./test.o

clean:
	#rm *.so
	rm test.o
	find LogFile '*.txt' -type f -print -exec rm {} \; 

