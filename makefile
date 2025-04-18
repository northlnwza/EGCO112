compile: main.cpp
	g++ main.cpp -lncurses
mouseTEST: mouseTEST.cpp
	g++ mouseTEST.cpp -lncurses
run: main.cpp
	./a.out
test: UItest.cpp
	gcc Timetable.h -lncurses
prac: UIprac
	g++ UIprac/UIprac7.cpp -lncurses