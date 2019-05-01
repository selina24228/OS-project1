all:
	gcc -std=c99 main.c myHeader.c -o main
	gcc -std=c99 fifo.c myHeader.c -o fifo	
	gcc -std=c99 child.c myHeader.c -o child 
