game:
	g++ -c main.cpp 
	g++ main.o -o game -lsfml-graphics -lsfml-window -lsfml-system

clean:
	rm game
	rm main.o