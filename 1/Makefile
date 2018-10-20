a.exe: test.o Checkerboard.o
	g++ -o a.exe test.o Checkerboard.o

test.o: test.cpp Checkerboard.h
	g++ -c test.cpp

Checkerboard.o: Checkerboard.cpp Checkerboard.h
	g++ -c Checkerboard.cpp

debug:
	g++ -g -o spellDebug.exe test.cpp Checkerboard.cpp

clean:
	rm -f *.exe *.o *.stackdump *~

backup:
	test -d backups || mkdir backups
	cp *.cpp backups
	cp *.h backups
