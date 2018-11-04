all: lab8

lab8: lab8.cpp
	g++ lab8a.cpp -Wall -olab8

clean:
	rm -f lab8
