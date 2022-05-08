FLAGS=-Wall -g

newcow: main.o newcow.o outils.o tamacowshi.o
	gcc -o $@ $^ $(FLAGS)

clean:
	rm *.o newcow