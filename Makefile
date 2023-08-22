all:
	mkdir ./build && cd ./build && cmake .. && cp -r ../images . && && cp -r ../fonts && make

.PHONY:
	clean

clean:
	rm -rf ./build
