COMPILER=g++
LIBS=-lglut -lGL -lGLU

all: driver.cpp 
	$(COMPILER) driver.cpp -o run $(LIBS)

run: all 
	./run

clean:
	rm run
