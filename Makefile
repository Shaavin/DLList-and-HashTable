a.out:
	g++ -std=c++11 myDlList_i127p615.hpp
	g++ -std=c++11 myHashTable_i127p615.hpp
	g++ -std=c++11 main.cpp
	./a.out inputs/instance1.txt output.txt

clean:
	rm *.gch output.txt a.out
