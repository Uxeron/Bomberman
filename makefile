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

all: main.o
	g++ main.o $(NOCONSOLE) $(WINARGS) -lSDL2 -lSDL2_image -o $(PROG)
debug: main.o
	g++ main.o $(WINARGS) -lSDL2 -o $(PROG)
main.o: main.cpp
	g++ -c main.cpp -o main.o
clean:
	$(RM) *.o *.out *.exe