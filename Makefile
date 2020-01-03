all: control.o options.o utils.o write.o
	gcc -o control control.o options.o utils.o && gcc -o write write.o utils.o

control.o: control.c options.h
	gcc -o control.o -c control.c

options.o: options.c options.h
	gcc -c options.c 

utils.o: utils.c utils.h
	gcc -c utils.c

write.o: write.c 
	gcc -c write.c