snaze:  main.o
	g++ -I include/ -std=c++11 -Wall -o snaze main.o

main.o:  main/main.cpp
	g++ -I include/ -std=c++11 -Wall -c main/main.cpp