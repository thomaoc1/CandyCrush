FILES=main.cpp classes/*/*.cpp 
FLAGS=-Wall -Wextra -pedantic -std=c++2a

main: $(FILES)
	g++ $(FLAGS) $(FILES) -o main 

clean:
	rm -f main