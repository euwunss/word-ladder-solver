build_test:
	rm -f test.exe
	gcc test.c -o test.exe

run_test:
	./test.exe

valgrind:
	rm -f test.exe
	gcc -g test.c -o test.exe
	valgrind -s --tool=memcheck --leak-check=yes --track-origins=yes ./test.exe -f