COMPILER=g++
LIBS=-lglut -lGL -lGLU

all: driver.cpp 
	$(COMPILER) driver.cpp -o driver $(LIBS)

run: all 
	./driver

clean:
	rm driver
