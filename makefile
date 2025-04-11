compile: UItest.cpp
	g++ UItest.cpp -lncurses
mouseTEST: mouseTEST.cpp
	g++ mouseTEST.cpp -lncurses
compilem: skibidi.cpp
	g++ skibidi.cpp
run: skibidi.cpp
	./a.out