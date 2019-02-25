ifeq ($(OS),Windows_NT)
	RM = del
	PROG = prog.exe
	WINARGS = -lmingw32 -lSDLmain
else
	RM = rm
	PROG = prog.out
	WINARGS = 
endif

all: main.o
	g++ main.o -o $(PROG) $(WINARGS) -lSDL
main.o: lesson01.cpp
	g++ -c lesson01.cpp -o main.o
clean:
	$(RM) *.o *.out *.exe
