
# sudo apt install libglu1-mesa-dev freeglut3-dev mesa-common-dev
# sudo apt install freeglut3-dev libpng-dev zlib1g-dev
libs = -lGL -lglut -lGLU -lpng -lz -lm

output:
	gcc main.c -o test $(libs)
	./test
