COMP = g++

build: prereq ./out/main.o ./out/Database.o out/helper_functions.o
	${COMP} out/main.o out/Database.o out/helper_functions.o


prereq:
	mkdir -p out

./out/main.o: main.cpp
	${COMP} -c main.cpp -o out/main.o

./out/Database.o: database_class/Database.cpp database_class/Database.h
	${COMP} -c database_class/Database.cpp -o out/Database.o

out/helper_functions.o: ./header_files/helper_functions.h ./source_files/helper_functions.cpp
	${COMP} -c ./source_files/helper_functions.cpp -o out/helper_functions.o

clean:
	rm -rfv out
	rm a.out
