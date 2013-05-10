COMPILER=g++
LIBS=-lglut -lGL -lGLU
FLAGS=-std=c++0x

all: driver.cpp ply_reader.cpp pre_processor.cpp
	$(COMPILER) $(FLAGS) driver.cpp ply_reader.cpp pre_processor.cpp -o run $(LIBS)

run: all 
	./run

clean:
	rm run *~ .*.swp
