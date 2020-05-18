
# Install...
# sudo apt install libglu1-mesa-dev freeglut3-dev mesa-common-dev
# sudo apt install freeglut3-dev libpng-dev zlib1g-dev libsndfile1-dev
# sudo apt-get install libasound-dev portaudio19-dev libportaudio2 libportaudiocpp0

# Configure the lib paths if it isnt running on debian linux 64
libs = -lGL -lglut -lGLU -lpng -lz -lrt -lm -L/usr/lib/x86_64-linux-gnu -lportaudio -lsndfile

output:
	gcc main.c -o test $(libs)
	./test
