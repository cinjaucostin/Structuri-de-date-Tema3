build:
	gcc *.c -o bnet

test: build
	valgrind --leak-check=full ./bnet

clean:
	rm bnet
	rm *.out