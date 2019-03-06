CXX = g++
CPPFLAGS = -g -Wall
BIN_DIR = bin

all: bin/Scrabble

bin/Scrabble: bin/Player.o bin/UserInterface.o bin/Bag.o \
	bin/Square.o bin/Dictionary.o bin/Board.o
	$(CXX) $(CPPFLAGS) -I lib bin/Player.o bin/UserInterface.o \
	bin/Bag.o bin/Square.o bin/Dictionary.o \
	bin/Board.o Scrabble.cpp -o bin/Scrabble

bin/Player.o: lib/Player.h src/Player.cpp bin/.dirstamp
	$(CXX) $(CPPFLAGS) -c -I lib src/Player.cpp -o bin/Player.o

bin/Board.o: lib/Board.h src/Board.cpp bin/.dirstamp
	$(CXX) $(CPPFLAGS) -c -I lib src/Board.cpp -o bin/Board.o

bin/UserInterface.o: lib/UserInterface.h src/UserInterface.cpp bin/.dirstamp
	$(CXX) $(CPPFLAGS) -c -I lib src/UserInterface.cpp -o bin/UserInterface.o

bin/Bag.o: lib/Tile.h lib/Bag.h src/Bag.cpp bin/.dirstamp
	$(CXX) $(CPPFLAGS) -c -I lib src/Bag.cpp -o bin/Bag.o

bin/Square.o: lib/Square.h src/Square.cpp bin/.dirstamp
	$(CXX) $(CPPFLAGS) -c -I lib src/Square.cpp -o bin/Square.o

bin/Dictionary.o: lib/Dictionary.h src/Dictionary.cpp bin/.dirstamp
	$(CXX) $(CPPFLAGS) -c -I lib src/Dictionary.cpp -o bin/Dictionary.o

.PHONY: clean
clean:
	rm -rf bin

bin/.dirstamp:
	mkdir -p bin
	touch bin/.dirstamp

