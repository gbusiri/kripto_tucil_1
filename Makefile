all:
	mkdir -p bin/
	g++ vigenere.cpp -o bin/vigenere
	g++ vigenere_extended.cpp util.cpp -o bin/extended
	g++ vigenere_modified.cpp util.cpp -o bin/modified
	g++ playfair.cpp -o bin/playfair

clean:
	rm -rf bin/*