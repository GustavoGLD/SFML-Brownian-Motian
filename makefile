all:
	g++ SRC/main.cpp -ltgui -lsfml-graphics -lsfml-window -lsfml-system -o program -g
	./program
