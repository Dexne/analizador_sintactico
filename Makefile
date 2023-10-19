OUT=PilaLR.o

.PHONY: clean

all: main.cpp includes.h EP.cpp Pila.cpp Manejador.cpp
	g++ -o $(OUT) $<
	./$(OUT)

clean:
	rm -f *.o