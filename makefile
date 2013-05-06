COMPILER=g++
LIBS=-lglut -lGL -lGLU

all: driver.cpp ply_reader.cpp
	$(COMPILER) driver.cpp ply_reader.cpp -o run $(LIBS)

run: all 
	./run

clean:
	rm run *~
