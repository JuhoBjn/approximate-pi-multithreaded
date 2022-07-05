# approximate-pi-threads
Approximate the value of pi using a random number generator. This time utilizing threads.

I first saw this problem in a YouTube video by Joma Tech. I found it quite interesting and coded along to his solution using C++.
Now, half a year later I decided to try and make a multi-threaded version of it. :D


## Compiling the program

To compile using make run `make`

To compile without make run `g++ -Wall -g -pthread -o approximate-pi *.cpp`


## Running the program

To run the program `./approximate-pi 100000`
The argument will be the amount of points to generate for the approximation.
