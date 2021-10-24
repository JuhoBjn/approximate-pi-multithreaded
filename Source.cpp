#include <iostream>
#include <vector>
#include <pthread.h>
#include <cmath>
#include <errno.h>
#include <stdlib.h>
#include "create_points.h"
using namespace std;

#define NUMBER_OF_THREADS 8

void spread_load(const int &points, vector<int> &points_per_thread);

int main(int argc, char *argv[]) {
	long amount_of_points = strtol(argv[1], NULL, 10);
	cout << "Generating " << amount_of_points << " points to approximate pi.\n";
	
	pthread_t threads[NUMBER_OF_THREADS];
	Points thread_points[NUMBER_OF_THREADS];
	vector<int> points_per_thread(NUMBER_OF_THREADS);
	spread_load(amount_of_points, points_per_thread);

	// Create threads to create points.
	for(int i = 0; i < NUMBER_OF_THREADS; ++i) {
		cout << "Creating thread " << i + 1 << endl;
		thread_points[i].amount_to_generate = points_per_thread[i];
		thread_points[i].tid = i;
		errno = pthread_create(&threads[i], NULL, create_points, (void *)&thread_points[i]);
		
		if(errno != 0) {
			perror("There appears to be an oopsie");
			cerr << "Thread " << i + 1 << " was not created.\n";
		}
	}

	// Wait for all threads to finish.
	for(pthread_t t: threads) {
		void **retval = NULL;
		pthread_join(t, retval);
	}

	// Total points inside circle and total from all threads.
	long total_inside_circle = 0;
	long total_points = 0;
	for(int i = 0; i < NUMBER_OF_THREADS; ++i){
		total_inside_circle += thread_points[i].points_inside_circle;
		total_points += thread_points[i].total_created;
	}

	// Approximate pi using generated points.
	double pi = 4.0 * (double)total_inside_circle / (double)total_points;
	cout << "Approximation of pi: " << pi << endl;

	return 0;
}

// Calculate amount of points to be generated by each thread.
void spread_load(const int &points, vector<int> &points_per_thread) {
	double num = (double)points / (double)NUMBER_OF_THREADS;
	if(num == static_cast<int>(num)) {
		for(int i = 0; i < points_per_thread.size(); ++i)
			points_per_thread[i] = static_cast<int>(num);
	}
	else {
		// Multiply decimal part of num by thread count and add to thread one. Rest of threads round num down.
		int intpart = floor(num);
		double decpart = num - (double)intpart;
		decpart *= NUMBER_OF_THREADS;
		int add_to_thread_one = floor(decpart);
		for(int i = 0; i < points_per_thread.size(); ++i) {
			points_per_thread[i] = intpart;
		}
		points_per_thread[0] += add_to_thread_one;
	}
}