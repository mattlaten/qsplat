COMPILER=g++
LIBS=-lglut -lGL -lGLU

all: driver.cpp ply_reader.cpp pre_processor.cpp
	$(COMPILER) driver.cpp ply_reader.cpp pre_processor.cpp -o run $(LIBS)

run: all 
	./run

clean:
	rm run *~ .*.swp
