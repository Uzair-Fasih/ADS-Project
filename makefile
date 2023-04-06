compile:
	c++ -o gatorTaxi ./main.cpp

run: compile
	./gatorTaxi $(input)

clean:
	rm -f output_file.txt
	rm -f gatorTaxi