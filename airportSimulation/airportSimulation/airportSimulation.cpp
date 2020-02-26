// airportSimulation.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <cstdlib>
#include <time.h>
#include "C:\Users\Steven_dev\Desktop\CS_Stuff\includes/queue.h"
#include "controler.h"

using namespace std;

void airport_simulation(unsigned int time_to_land, unsigned int time_to_takeoff,
    double landing_probability, double takeoff_probability, 
    unsigned int fuel_limit, unsigned int simulation_time);

int main()
{
    srand(time(0));
    unsigned int time_to_land = 5, time_to_takeoff = 15, fuel_limit = 20, simulation_time = 1440;
    double landing_probability = .1, takeoff_probability = .08;
    airport_simulation(time_to_land, time_to_takeoff, landing_probability,
        takeoff_probability, fuel_limit, simulation_time);

}

void airport_simulation(unsigned int time_to_land, unsigned int time_to_takeoff,
     double landing_probability, double takeoff_probability, unsigned int fuel_limit, unsigned int simulation_time) {

    Queue<int> arrival_queue, departure_queue;
    unsigned int next = 0, current_second = 0;
    control c;
    averager avg;
    takeoff takingOff;

    cout << "time to take off\t: " << time_to_takeoff << endl;
    cout << "time to land\t\t: " << time_to_land << endl;
    cout << "probability of landing\t: " << landing_probability << endl;
    cout << "probability of takeoff\t: " << takeoff_probability << endl;
    cout << "fuel: time to crash\t: " << fuel_limit << endl;
    cout << "total simulation time\t: " << simulation_time << endl;
    
    for (current_second = 1; current_second <= simulation_time; current_second++) {
        if (c.landingQuery()) {
            if (!takingOff.is_busy()) {
                takingOff.start_landing();
                arrival_queue.push(current_second);
            }
        }

        //arrival queue is planes waiting to leave
        if (!takingOff.is_busy() && (!arrival_queue.empty())) {
            if (c.takeoffQuery()) {
                next = arrival_queue.front();
                avg.add_number(current_second - next);
                takingOff.start_takeoff();
                arrival_queue.pop();
                departure_queue.push(next);
            }
        }
        takingOff.one_second();
    }

    cout << "Customers served: " << avg.how_many_numbers() << endl;
    if (avg.how_many_numbers() > 0) {
        cout << "Average wait: " << avg.average() << " sec" << endl;
    }


}