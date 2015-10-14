test.exe: test.cpp hashTable.o
	g++ -O3 -std=c++11 -o spell.exe test.cpp hashTable.o 

hashTable.o: hashTable.cpp hashTable.h
	g++ -O3 -std=c++11 -c hashTable.cpp

debug:
	g++ -std=c++11 -g -o testDebug.exe test.cpp hashTable.cpp

clean:
	rm -f *.exe *.o *.stackdump *~

backup:
	test -d backups || mkdir backups
	cp *.cpp backups
	cp *.h backups
