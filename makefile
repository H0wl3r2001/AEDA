all:
	echo "setup, compile"
setup:
	g++ bakery.cpp shop.cpp person.cpp auxiliary.cpp initial_setup.cpp -o initial_setup
	./initial_setup
compile:
	g++ bakery.cpp shop.cpp person.cpp menu.cpp auxiliary.cpp main.cpp -o run
	./run