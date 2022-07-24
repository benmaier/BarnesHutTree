
default: compile
	./a.out
	rm a.out

compile:
	g++ -I.. -std=c++11 main.cpp 

run:
	./a.out

py:
	./a.out > run.csv
	python3.8 plot_theta_scan.py
