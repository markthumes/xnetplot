INC=-I. -Ix11wrapper
LIBS=-lX11 -lXext
default:
	g++ -c x11wrapper/x11wrapper.cpp -o x11wrapper.o $(INC)
	g++ -c main.cpp -o main.o $(INC)
	g++ -c graph.cpp -o graph.o $(INC)
	g++ x11wrapper.o graph.o main.o $(LIBS) -o a.out

