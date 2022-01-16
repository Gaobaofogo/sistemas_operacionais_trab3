all:
	g++ -o prog prog.cpp

linter:
	cppcheck .
	python3 -m cpplint prog.cpp

clean:
	rm prog
