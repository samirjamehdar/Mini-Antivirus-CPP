# Samir Jamehdar, samirjamehdar@hotmail.com
# Mathias Carlshjelm, mathias.c256400@gmail.com

main: main.o miniav.o
	g++ main.o miniav.o -o app

main.o: main.cpp
	g++ -c main.cpp

miniav.o: miniav.cpp
	g++ -c miniav.cpp

clean:
	-rm -f *.o app	