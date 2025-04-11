compile: main.cpp
	g++ main.cpp -lncurses
mouseTEST: mouseTEST.cpp
	g++ mouseTEST.cpp -lncurses
run: main.cpp
	./a.out
test: UItest.cpp
	g++ UItest.cpp -lncurses