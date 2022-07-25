
default: compile
	./a.out
	rm a.out

compile:
	g++ -I.. -std=c++11 main.cpp 

run:
	./a.out

py:
	./a.out > boxes.csv
	python3.8 plot_boxes.py
