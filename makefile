PROG = prog.exe
WINARGS = -I "$(CURDIR)/SDL2/include" -L "$(CURDIR)/SDL2/lib" -lmingw32 -lSDL2main
NOCONSOLE = -w -mwindows

objects := $(patsubst src/%.cpp,temp/%.o,$(wildcard src/*.cpp))

all: folder $(objects)
	g++ -std=c++11 $(objects) $(WINARGS) -lSDL2 -lSDL2_image -o $(PROG)
release: folder $(objects)
	g++ -std=c++11 $(objects) $(NOCONSOLE) $(WINARGS) -lSDL2 -lSDL2_image -o $(PROG)
temp/%.o: src/%.cpp include/%.hpp
	g++ -std=c++11 -c $< -o $@
folder:
	if not exist "temp" md temp
include/main.hpp:
	type nul > include/main.hpp

.PHONY: clean
clean:
	if exist "temp" rmdir /s /q temp
	del *.out *.exe 2>nul
