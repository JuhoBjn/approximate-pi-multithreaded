#include <iostream>
#include <pthread.h>
#include <stdlib.h>
#include "create_points.h"
using namespace std;

#define NUMBER_OF_THREADS 8

int main(int argc, char *argv[]) {
	int amount_of_points = atoi(argv[1]);
	cout << "Generating " << amount_of_points << " points per thread.\n";
	
	pthread_t threads[NUMBER_OF_THREADS];
	Points *thread_points[NUMBER_OF_THREADS];
	short status = 0;

	for(int i = 0; i < NUMBER_OF_THREADS; ++i) {
		cout << "Creating thread " << i << endl;
		thread_points[i]->amount_to_generate = amount_of_points;
		thread_points[i]->tid = i;
		status = pthread_create(&threads[i], NULL, create_points, (void *)thread_points[i]);
	}

	// Total points inside circle and total from all threads.
	long total_inside_circle = 0;
	long total_points = 0;
	for(int i = 0; i < NUMBER_OF_THREADS; ++i){
		total_inside_circle += thread_points[i]->points_inside_circle;
		total_points += thread_points[i]->total_created;
	}

	// Approximate pi using generated points.
	double pi = 4 * (double)total_inside_circle / (double)total_points;
	cout << "Approximation of pi: " << pi << endl;

	return 0;
}
