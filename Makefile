build-debug: ping-pong.cpp
	g++ -std=c++14 ping-pong.cpp -o output -DDEBUG
build-release: ping-pong.cpp
	g++ -std=c++14 ping-pong.cpp -o output 
run:
	./output
