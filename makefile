snaze:  main.o snaze.o
	g++ -I include/ -std=c++11 -Wall -o snaze main.o snaze.o

main.o:  main/main.cpp
	g++ -I include/ -std=c++11 -Wall -c main/main.cpp

snaze.o: source/snaze.cpp
	g++ -I include/ -std=c++11 -Wall -c source/snaze.cpp