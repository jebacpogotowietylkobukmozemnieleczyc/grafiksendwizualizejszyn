LIBS=-lGL -lglut -lGLEW

main_file: main_file.cpp detailed_cube.cpp tga.cpp
	g++ -o main_file main_file.cpp detailed_cube.cpp tga.cpp $(LIBS)
