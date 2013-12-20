CC = g++ 

mst: mst.o fibHeap.o simpleScheme.o 
	$(CC) -o mst mst.o fibHeap.o simpleScheme.o 
	
mst.o: mst.cpp
	$(CC) -g -c mst.cpp
	
fibHeap.o: fibHeap.cpp
	$(CC) -g -c fibHeap.cpp
	
simpleScheme.o: simpleScheme.cpp
	$(CC) -g -c simpleScheme.cpp
	
clean: 
	rm -f *.o