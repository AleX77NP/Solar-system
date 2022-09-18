all: main

main: Source.cpp visuals.cpp
	g++ -ggdb -framework GLUT -framework OpenGL Source.cpp visuals.cpp