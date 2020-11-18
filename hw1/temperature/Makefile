all: temperature

temperature:	temperature.o
	gcc temperature.o -o temperature

temperature.o:	temperature.c
	gcc -c temperature.c -o temperature.o

clean:
	rm -f temperature temperature.o core *~
