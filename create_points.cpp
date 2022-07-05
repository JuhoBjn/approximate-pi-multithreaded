#include "create_points.h"
#include <iostream>
#include <random>
#include <cmath>
#include <pthread.h>

// Create specified amount of points and check if they're inside a circle with a radius of 1.
void *create_points(void *thread_points) {
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<double> distribution(0,1);

    for(unsigned long i = 0; i < ((Points *)thread_points)->amount_to_generate; ++i) {
        double point_x = distribution(gen);
        double point_y = distribution(gen);
        
        if(pow(point_x, 2) + pow(point_y, 2) <= 1.0)
            ((Points *)thread_points)->points_inside_circle++;
        ((Points *)thread_points)->total_created++;
    }
    cout << "Exiting thread " << ((Points *)thread_points)->tid + 1 << endl;
    pthread_exit(NULL);
}