SRC = main.cpp Mines.h Mines.cpp tile.h tile.cpp color.cpp cursor.h cursor.cpp Menu.h Menu.cpp numberOfDigits.h numberOfDigits.cpp Enter.h Enter.cpp mygetch.h mygetch.cpp error.h error.cpp
OBJ = main.o Mines.o tile.o error.o mygetch.o cursor.o Menu.o numberOfDigits.o Enter.o
TARGET = MINES
CC = g++
FLAGS = -Wall

DEFAULT_SIZE = 3

#Packaging
TAR = tar -cvvf
GZIP = gzip -v


all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) -o $(TARGET) $(OBJ) $(FLAGS)

.cpp.o: $(SRC)
	$(CC) -c $< $(FLAGS)

.PHONY : run
run: ./$(TARGET)
	./$(TARGET)

.PHONY : test
test: ./$(TARGET)
	./$(TARGET) $(DEFAULT_SIZE)

arch: ./$(TARGET)
	$(TAR) $(TARGET)_BIN.tar $(TARGET)
	$(GZIP) $(TARGET)_BIN.tar

src_arch:
	$(TAR) $(TARGET)_SRC.tar $(SRC) makefile TODOlist
	$(GZIP) $(TARGET)_SRC.tar

debug:
	echo "#define DEBUG" > DEBUGDEF

no_debug:
	echo "#define NODEBUG" > DEBUGDEF

.PHONY : clean
clean:
	rm -f ./$(TARGET)
	rm -f *.o
