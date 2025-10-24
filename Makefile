comp:= g++
compFlags:= -Wall -Wextra -O0


main: main.cpp
	${comp} ${compFlags} main.cpp -o lookup

clean:
	rm -rf *.o lookup