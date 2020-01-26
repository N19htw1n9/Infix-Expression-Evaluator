build: main.o intStack.o charStack.o
	g++ -o proj5 main.o intStack.o charStack.o

main.o: main.cpp Header.h
	g++ -c main.cpp

intStack.o: intStack.cpp Header.h
	g++ -c intStack.cpp

charStack.o: charStack.cpp Header.h
	g++ -c charStack.cpp

clean:
	rm main.o intStack.o charStack.o  comp
