#pragma once
using namespace std;

// Create specified amount of points and return points.
void *create_points(void *thread_points);

struct Points {
    int tid = 0;
    long amount_to_generate = 0;
    long points_inside_circle = 0;
    long total_created = 0;    
};