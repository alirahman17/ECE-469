networkTrain.exe: networkTrain.o neuralNet.o
	g++ -o networkTrain.exe networkTrain.o neuralNet.o

networkTest.exe: networkTest.o neuralNet.o
	g++ -o networkTest.exe networkTest.o neuralNet.o

neuralNet.o: neuralNet.cpp neuralNet.hpp
	g++ -c neuralNet.cpp

networkTrain.o: networkTrain.cpp neuralNet.hpp
	g++ -c networkTrain.cpp

networkTest.o: networkTest.cpp neuralNet.hpp
	g++ -c networkTest.cpp

debug:
	g++ -g -o trainDebug.exe networkTrain.cpp neuralNet.cpp

clean:
	rm -f *.exe *.o *.stackdump *~

backup:
	test -d backups || mkdir backups
	cp *.cpp backups
	cp *.h backups
