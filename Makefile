all:
	gcc -std=gnu99 main.c myHeader.c -o main
	gcc -std=gnu99 fifo.c myHeader.c -o fifo	
	gcc -std=gnu99 child.c myHeader.c -o child 
