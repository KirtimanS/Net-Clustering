all: 
	g++ -c -std=c++11 Graph\ Generator.cpp 
	g++ -c -std=c++11 Graph\ Explorer.cpp
	g++ -c -std=c++11 Eligible\ Lmrks.cpp
	g++ -c -std=c++11 Lmrk_2\ Processing.cpp
	g++ -c -std=c++11 Make\ Landmark.cpp
	g++ -c -std=c++11 Restrictions\ and\ Clean\ Up.cpp
	g++ -c -std=c++11 Display.cpp
	g++ -c -std=c++11 Spine\ v5-main.cpp
	
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

