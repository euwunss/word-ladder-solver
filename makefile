# compiles main program
build:
	rm -f main.exe
	gcc main.c -o main.exe

# runs main program
run:
	./main.exe

# runs main program using redirection input from a file
run_from_file:
	./main.exe < tests/sampleInput.txt

# runs main program with Valgrind
valgrind:
	rm -f main.exe
	gcc -g main.c -o main.exe
	valgrind -s --tool=memcheck --leak-check=yes --track-origins=yes ./main.exe -f

# runs main program with Valgrind using redirection input from a file
valgrind_from_file:
	rm -f main.exe
	gcc -g main.c -o main.exe
	valgrind -s --tool=memcheck --leak-check=yes --track-origins=yes ./main.exe < tests/sampleInput.txt -f

# builds testing program
build_test:
	rm -f tests/test.exe
	gcc tests/test.c -o tests/test.exe

# runs testing program
run_test:
	./tests/test.exe

# runs testing program with Valgrind
valgrind_test:
	rm -f tests/test.exe
	gcc -g tests/test.c -o tests/test.exe
	valgrind -s --tool=memcheck --leak-check=yes --track-origins=yes ./tests/test.exe -f