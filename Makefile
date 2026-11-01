#run with make
all:
	g++ -std=c++17 -pthread main.cpp dining.cpp peterson_lock.cpp tournament_tree_lock.cpp -o my-dining

clean:
	rm -f my-dining

#all and clean are commands
.PHONY: all clean