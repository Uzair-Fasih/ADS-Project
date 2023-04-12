compile:
	c++ -o gatorTaxi ./main.cpp

run: compile
	./gatorTaxi $(input)

clean:
	rm -f output_file.txt
	rm -f gatorTaxi
	rm -f Fasih_Mohammad_Uzair.zip

package:clean
	zip -r Fasih_Mohammad_Uzair.zip main.cpp GatorTaxi.hpp MinHeap.hpp RedBlackTree.hpp Nodes.hpp Report.pdf makefile