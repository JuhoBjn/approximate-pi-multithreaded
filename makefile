CC = g++
FLAGS = -Wall -g -pthread

approximate_pi: Source.o create_points.o
	$(CC) $(FLAGS) -o approximate_pi Source.o create_points.o

Source.o: Source.cpp
	$(CC) $(FLAGS) -c Source.cpp

create_points: create_points.cpp create_points.h
	$(CC) $(FLAGS) -c create_points.cpp 

clean:
	@echo "Cleaning up..."
	$(RM) *.o
