compile: skibidi.cpp
	g++ skibidi.cpp
run: skibidi.cpp
	./a.out
test: main.cpp, User.cpp, UserList.cpp
	g++ main.cpp User.cpp UserList.cpp

in:
	sudo apt install libncurses-dev