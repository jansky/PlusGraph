all: libplusgraph plusgraphcmd

libplusgraph: plusgraph.o
	ar rcs libplusgraph.a plusgraph.o

plusgraph.o: plusgraph.cpp
	g++ -g -c plusgraph.cpp

plusgraphcmd: libplusgraph plusgraphcmd.o
	g++ -g -o plusgraph plusgraphcmd.o libplusgraph.a -lpluscalc -lm

install:
	cp plusgraph /usr/bin
	cp libplusgraph.a /usr/lib
	cp plusgraph.h /usr/include

uninstall:
	rm /usr/bin/plusgraph
	rm /usr/lib/libplusgraph.a
	rm /usr/include/plusgraph.h

clean:
	rm *.o
	rm *.a
	rm plusgraph