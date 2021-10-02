
primz:  main.o
	g++ -o primz main.o

main.o:  main.cpp
	g++ -c main.cpp -o main.o

clean:
	rm primz main.o
