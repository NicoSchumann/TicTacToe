all:
	mkdir ./build && cd ./build && cmake .. && cp -r ../images . && make

.PHONY:
	clean

clean:
	rm -rf ./build
