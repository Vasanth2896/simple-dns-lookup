CXX:= g++
CXXFLAGS:= -Wall -Wextra -O0
DEBUGFLAGS:= -Iinclude -g3



main: main.cpp
	${CXX} ${CXXFLAGS} main.cpp -o lookup

debug: main.cpp
	${CXX} ${CXXFLAGS} ${DEBUGFLAGS} main.cpp -o lookup

clean:
	rm -rf *.o lookup