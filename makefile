compile:
	c++ -o gatorTaxi ./main.cpp

run: compile
	./gatorTaxi $(input)
	