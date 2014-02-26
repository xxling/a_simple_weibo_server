protocol: main.o protocol.o
	gcc -o protocol main.o protocol.o -lpthread
main.o: main.c protocol.h
	gcc -c  main.c -lpthread
protocol.o: protocol.c protocol.h
	gcc -c protocol.c
clean:
	rm -f protocol protocol.o main.o

