build:
	mkdir build
	g++ -o ./build/ShannonSwitching ./src/ShannonSwitching.cpp -g

clean:
	rm -rf ./build