CC = g++ -std=c++11
CFLAGS = -c
all: 
	$(CC) $(CFLAGS) Graph\ Generator.cpp 
	$(CC) $(CFLAGS) Graph\ Explorer.cpp
	$(CC) $(CFLAGS) Eligible\ Lmrks.cpp
	$(CC) $(CFLAGS) Lmrk_2\ Processing.cpp
	$(CC) $(CFLAGS) Make\ Landmark.cpp
	$(CC) $(CFLAGS) Restrictions\ and\ Clean\ Up.cpp
	$(CC) $(CFLAGS) Display.cpp
	$(CC) $(CFLAGS) Spine\ v5-main.cpp
	
	g++ Graph\ Generator.o Graph\ Explorer.o Eligible\ Lmrks.o Lmrk_2\ Processing.o Make\ Landmark.o Restrictions\ and\ Clean\ Up.o Display.o Spine\ v5-main.o -o net\ clustering

clean:
	rm -f Graph\ Generator.o 
	rm -f Graph\ Explorer.o 
	rm -f Eligible\ Lmrks.o 
	rm -f Lmrk_2\ Processing.o
	rm -f Make\ Landmark.o 
	rm -f Restrictions\ and\ Clean\ Up.o 
	rm -f Display.o 
	rm -f Spine\ v5-main.o 
	rm -f net\ clustering

