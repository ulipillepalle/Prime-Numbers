
primz:  main.o 
	g++ -o primz main.o

main.o:  main.cpp
	g++ -c main.cpp -o main.o

clean:
	rm primz main.o

run:
	time nice -n-20 ./primz 55000000000 &
