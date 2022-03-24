.PHONY: all
all: clean build-test test

.PHONY: clean
clean:
	rm -rf out/

.PHONY: build-test
build-test:
	mkdir out/
	cc -Wall -o out/cargs_test.o test/*.c src/* -I src/ -I test/

.PHONY: test
test:
	./out/cargs_test.o
