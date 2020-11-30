all: 	thdcircuit

thdcircuit:		thdcircuit.c
	gcc -pthread -Wall $< -o $@

clean:
	rm -f thdcircuit *.o core *~
