FILES=main.cpp classes/*/*.cpp classes/*/*/*.cpp 
FLAGS=-Wall -Wextra -pedantic -std=c++2a
LINKERS=-lfltk

main: $(FILES)
	g++ $(FLAGS) $(FILES) -o main $(LINKERS)

clean:
	rm -f main