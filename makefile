build: Main.o intStack.o charStack.o
	g++ -o proj5 Main.o intStack.o charStack.o

Main.o: Main.cpp Header.h
	g++ -c Main.cpp

intStack.o: intStack.cpp Header.h
	g++ -c intStack.cpp

charStack.o: charStack.cpp Header.h
	g++ -c charStack.cpp

clean:
	rm Main.o intStack.o charStack.o  comp
