
all:
	gcc -std=c99 src/main.c -o build/ligen -Iinclude -Wno-unused-value

clean:
	rm ./build/ligen

mov:
	sudo cp ./build/ligen sample

.PHONY: all