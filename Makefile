all:
	g++ -Wall -pedantic -Wno-long-long -O0 -ggdb -o game ./src/main.cpp ./src/object.cpp ./src/hitbox.cpp ./src/files.cpp ./src/global.cpp -lglut -lGLU -lGL -lm

compile:
	g++ -Wall -pedantic -Wno-long-long -O0 -ggdb -o game ./src/main.cpp ./src/object.cpp ./src/hitbox.cpp ./src/files.cpp ./src/global.cpp -lglut -lGLU -lGL -lm

run:
	./game

clean:
	rm game

