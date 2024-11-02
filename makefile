build:
	rm -f main.exe
	gcc main.c -o main.exe

run:
	./main.exe

valgrind:
	rm -f main.exe
	gcc -g main.c -o main.exe
	valgrind -s --tool=memcheck --leak-check=yes --track-origins=yes ./main.exe -f

build_test:
	gcc test.c -o test.exe

run_test:
	./test.exe