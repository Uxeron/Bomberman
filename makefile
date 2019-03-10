ifeq ($(OS),Windows_NT)
	RM = del
	PROG = prog.exe
	WINARGS = -I "$(CURDIR)/SDL2/include" -L "$(CURDIR)/SDL2/lib" -lmingw32 -lSDL2main
	NOCONSOLE = -w -mwindows
else
	RM = rm
	PROG = prog.out
	WINARGS = 
	NOCONSOLE = 
endif

all: main.o window.o character.o interactiveObject.o
	g++ -std=c++11 main.o window.o character.o interactiveObject.o $(NOCONSOLE) $(WINARGS) -lSDL2 -lSDL2_image -o $(PROG)
debug: main.o window.o character.o interactiveObject.o
	g++ -std=c++11 main.o window.o character.o interactiveObject.o $(WINARGS) -lSDL2 -lSDL2_image -o $(PROG)
window.o: window.cpp
	g++ -std=c++11 -c window.cpp -o window.o
character.o: character.cpp
	g++ -std=c++11 -c character.cpp -o character.o
interactiveObject.o: interactiveObject.cpp
	g++ -std=c++11 -c interactiveObject.cpp -o interactiveObject.o
main.o: main.cpp
	g++ -std=c++11 -c main.cpp -o main.o
clean:
	$(RM) *.o *.out *.exe
