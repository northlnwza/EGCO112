compile: skibidi.cpp
	g++ skibidi.cpp  User.cpp UserList.cpp Student.cpp Staff.cpp Shop.cpp -o a.out

run: skibidi.cpp
	./a.out