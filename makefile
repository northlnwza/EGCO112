compile: skibidi.cpp
	g++ skibidi.cpp  User.cpp UserList.cpp Student.cpp Staff.cpp Shop.cpp -o a.out -std=c++17

run: skibidi.cpp
	./a.out