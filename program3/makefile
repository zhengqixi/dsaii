useGraph.exe: useGraph.cpp heap.o hashTable.o graph.o
	g++ -std=c++11 -o useGraph.exe useGraph.cpp graph.o heap.o hashTable.o

graph.o: graph.cpp graph.h
	g++ -std=c++11 -c graph.cpp

heap.o: heap.cpp heap.h
	g++ -std=c++11 -c heap.cpp

hashTable.o: hashTable.cpp hashTable.h
	g++ -std=c++11 -c hashTable.cpp

debug:
	g++ -std=c++11 -g -o useGraphDebug.exe useGraph.cpp heap.cpp hashTable.cpp graph.cpp

clean:
	rm -f *.exe *.o *.stackdump *~
