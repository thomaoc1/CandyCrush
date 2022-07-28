FILES=main.cpp classes/*/*.cpp classes/*/*/*.cpp 
FLAGS=-Wall -Wextra -pedantic -std=c++2a
LINKERS=-lfltk

CandyCrush: $(FILES)
	g++ $(FLAGS) $(FILES) -o CandyCrush $(LINKERS)
clean:
	rm -f CandyCrush