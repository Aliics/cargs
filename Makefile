.PHONY: all
all: clean build test

.PHONY: clean
clean:
	rm -rf out/

.PHONY: build
build:
	mkdir -p out/lib/include/
	mkdir -p out/test/

# Create binaries for all source files and then bundle them into an archive.
# Include the header files as well.
	cc -Wall -Wextra -o out/lib/cargs.o -c src/cargs.c -I src/
	cc -Wall -Wextra -o out/lib/parse.o -c src/parse.c -I src/
	ar -r out/lib/cargs.a out/lib/*.o
	cp src/*.h out/lib/include/
	rm -rf out/raw/

	cc -Wall -Wextra -o out/test/cargs_test.o test/*.c src/*.c -I src/ -I test/

.PHONY: test
test:
	./out/test/cargs_test.o
