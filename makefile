ifeq ($(OS),Windows_NT)
	PROG = prog.exe
	RM = del *.exe 2>nul
	RMDIR = if exist "temp" rmdir /s /q temp
	ARGS = -I "$(CURDIR)/SDL2/include" -L "$(CURDIR)/SDL2/lib" -lmingw32 -lSDL2main -lSDL2 -lSDL2_image
	NOCONSOLE = -w -mwindows
	FOLDER = folder
else
	PROG = prog.out
	RM = rm *.out > /dev/null 2>&1
	RMDIR = rm -rf temp
	ARGS = `sdl2-config --cflags --libs` -lSDL2_image
	NOCONSOLE =
	FOLDER = folder_lin
endif


objects := $(patsubst src/%.cpp,temp/%.o,$(wildcard src/*.cpp))

all: $(FOLDER) $(objects)
	g++ -std=c++14 $(objects) $(ARGS) -o $(PROG)
release: $(FOLDER) $(objects)
	g++ -std=c++14 $(objects) $(NOCONSOLE) $(ARGS) -o $(PROG)
temp/%.o: src/%.cpp include/%.hpp
	g++ -std=c++14 -c $< -o $@
folder:
	if not exist "temp" md temp
folder_lin:
	mkdir -p temp

include/main.hpp:
	type nul > include/main.hpp

.PHONY: clean
clean:
	$(RMDIR)
	$(RM)

