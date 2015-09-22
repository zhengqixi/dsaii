spell.exe: spellCheck.o hashTable.o check.cpp
	g++ -O3 -std=c++11 -o spell.exe check.cpp spellCheck.o hashTable.o 

spellCheck.o: spellCheck.cpp spellCheck.h hashTable.h
	g++ -O3 -std=c++11 -c spellcheck.cpp

hashTable.o: hashTable.cpp hashTable.h
	g++ -O3 -std=c++11 -c hashTable.cpp

debug:
	g++ -std=c++11 -g -o spellDebug.exe check.cpp spellCheck.cpp hashTable.cpp

clean:
	rm -f *.exe *.o *.stackdump *~

backup:
	test -d backups || mkdir backups
	cp *.cpp backups
	cp *.h backups
