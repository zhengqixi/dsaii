useHeap.exe: useHeap.o heap.o hashTable.o
	g++ -std=c++11 -o useHeap.exe useHeap.o heap.o hashTable.o

useHeap.o: useHeap.cpp
	g++ -std=c++11 -c useHeap.cpp

heap.o: heap.cpp heap.h
	g++ -std=c++11 -c heap.cpp

hashTable.o: hashTable.cpp hashTable.h
	g++ -std=c++11 -c hashTable.cpp

debug:
	g++ -g -o useHeapDebug.exe useHeap.cpp heap.cpp hash.cpp

clean:
	rm -f *.exe *.o *.stackdump *~
