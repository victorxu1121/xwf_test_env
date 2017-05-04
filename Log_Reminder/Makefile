
#build: libmylr.a
	#build the lib of log reminder  
#	ar crv $@ libmylr.a logreminder.o

#logreminder.o: src/header_logreminder.h src/logreminder.c
#	gcc -c src.header_logreminder.h src/logreminder.c
 
#test: test.o
   
#test.o: main.c
#	gcc -c src/main.c -L. -lmylr -o test.o

all:
	#gcc -c src/header_logreminder.h src/logreminder.c 
	#ar crv libmylr.a logreminder.o
	#gcc -g src/main.c -lmylr -o test
	gcc src/header_logreminder.h src/logreminder.c src/main.c -o test.o
	
run:
	./test
edit:
	vim src/test_log_reminder.c
clean:
	rm test.o 
	find LogFile '*.txt' -type f -print -exec rm {} \; 

