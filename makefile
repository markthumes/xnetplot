INC=-I. -Ix11wrapper
LIBS=-lX11 -lXext
CFLAGS=-Wall -Wextra -ggdb
default:
	g++ -c x11wrapper/x11wrapper.cpp -o x11wrapper.o $(INC) $(CFLAGS)
	g++ -c main.cpp -o main.o $(INC) $(CFLAGS)
	g++ -c graph.cpp -o graph.o $(INC) $(CFLAGS)
	g++ x11wrapper.o graph.o main.o $(LIBS) -o a.out

