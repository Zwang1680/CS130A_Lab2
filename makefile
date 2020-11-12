all: project2_first.out project2_second.out

project2_first.out: project2_first.cpp hash24.cpp dictionary.cpp
	g++ -std=c++11 $^ -o $@

project2_second.out: project2_second.cpp hash24.cpp dictionary.cpp
	g++ -std=c++11 $^ -o $@

clean:
	rm -f *.out