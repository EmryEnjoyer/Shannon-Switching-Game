CC=g++
CFLAGS=-g

OBJECTS =

build: $(OBJECTS) ./build/ShannonSwitching.o
	g++ -o ./build/ShannonSwitching ./build/ShannonSwitching.o $(OBJECTS) -g

./build/ShannonSwitching.o: ./src/ShannonSwitching.cpp
	mkdir -p build
	g++ -o $@ -c $(CFLAGS) $<

./build/%.o: ./src/Graphs/%.cpp
	mkdir -p build
	${CC} -o $@ -c ${CFLAGS} $<

clean:
	rm -rf ./build