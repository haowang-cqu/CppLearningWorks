DIR: main.o DocMan.o GetInput.o
	g++ main.o DocMan.o GetInput.o -o DIR
mian.o: main.cpp
	g++ -c main.cpp
DocMan.o: DocMan.cpp
	g++ -c DocMan.cpp
GetInput.o: GetInput.cpp
	g++ -c GetInput.cpp
clean:
	rm main.o 
	rm DocMan.o
	rm GetInput.o
