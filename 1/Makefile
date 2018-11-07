Game.exe: Game.o Checkerboard.o Piece.o Move.o
	g++ -o a.exe Game.o Checkerboard.o Piece.o Move.o

Move.o: Move.cpp Move.hpp
	g++ -c Move.cpp

Piece.o: Piece.cpp piece.hpp
	g++ -c Piece.cpp

Checkerboard.o: Checkerboard.cpp Checkerboard.hpp piece.hpp Move.hpp
	g++ -c Checkerboard.cpp

Game.o: Game.cpp Checkerboard.hpp piece.hpp Move.hpp
	g++ -c Game.cpp

debug:
	g++ -g -o gameDebug.exe Game.cpp Checkerboard.cpp Piece.cpp Move.cpp

clean:
	rm -f *.exe *.o *.stackdump *~

backup:
	test -d backups || mkdir backups
	cp *.cpp backups
	cp *.h backups
