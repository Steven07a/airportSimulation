// airportSimulation.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <iomanip>
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
	time_t a = time(0);
	unsigned int time_to_land = 5, time_to_takeoff = 15, fuel_limit = 20, simulation_time = 1440;
	double landing_probability = .1, takeoff_probability = .08;
	airport_simulation(
		time_to_land,
		time_to_takeoff,
		landing_probability,
		takeoff_probability,
		fuel_limit,
		simulation_time
	);

	return 0;
}

void airport_simulation(unsigned int time_to_land, unsigned int time_to_takeoff,
	double landing_probability, double takeoff_probability, unsigned int fuel_limit, unsigned int simulation_time) {
	Queue<int> arrival_queue, departure_queue;
	unsigned int next = 0, current_second = 0, landingCount = 0, depatureCount = 0, crashed = 0;
	control c(landing_probability,takeoff_probability);
	averager landingAverage, departureAverage;
	takeoff runway(time_to_takeoff,time_to_land), runway1(time_to_takeoff,time_to_land);

	cout << fixed;
	cout << setprecision(2);
	cout << "time to take off\t: " << time_to_takeoff << endl;
	cout << "time to land\t\t: " << time_to_land << endl;
	cout << "probability of landing\t: " << landing_probability << endl;
	cout << "probability of takeoff\t: " << takeoff_probability << endl;
	cout << "fuel: time to crash\t: " << fuel_limit << endl;
	cout << "total simulation time\t: " << simulation_time << endl;

	for (current_second = 1; current_second <= simulation_time; current_second++) {
		
		if (c.landingQuery()) {
			arrival_queue.push(current_second);
			next = arrival_queue.front();
		}

		if (!runway.is_busy() && !arrival_queue.empty()) {
			if ((current_second - next) > fuel_limit) {
				crashed++;
				arrival_queue.pop();
			} else {
				landingAverage.add_number(current_second - next);
				runway.start_landing();
				arrival_queue.pop();
				departure_queue.push(current_second + time_to_land);
				landingCount++;
			}
		} else if (!runway1.is_busy() && !arrival_queue.empty()) {
			if ((current_second - next) > fuel_limit) {
				crashed++;
				arrival_queue.pop();
			} else {
				landingAverage.add_number(current_second - next);
				runway1.start_landing();
				arrival_queue.pop();
				departure_queue.push(current_second + time_to_land);
				landingCount++;
			}
		}

		//arrival queue is planes waiting to leave
		if (!runway.is_busy() && (!departure_queue.empty())) {
			if (departure_queue.front() < current_second) {
				if (c.takeoffQuery()) {
					next = departure_queue.front();
					depatureCount++;
					departureAverage.add_number(current_second - next);
					runway.start_takeoff();
					departure_queue.pop();
				}
			} else {
				cout << endl;
			}
		} else if (!runway1.is_busy() && (!departure_queue.empty())) {
			if (departure_queue.front() < current_second) {
				if (c.takeoffQuery()) {
					next = departure_queue.front();
					depatureCount++;
					departureAverage.add_number(current_second - next);
					runway1.start_takeoff();
					departure_queue.pop();
				}
			}
		}
		runway.one_second();
		runway1.one_second();
	}

	cout << "\n\n\n" << landingCount << " landed\n";
	cout << depatureCount << " took off" << endl;
	cout << crashed << " planes crashed." << endl;
	cout << "Average waiting time to land: " << landingAverage.average() << " sec" << endl;
	cout << "Average waiting time to take off: " << departureAverage.average() << " sec" << endl;
	cout << "planes in landing queue : " << arrival_queue.size() << endl;
	cout << "planes in take off queue : " << departure_queue.size() << endl;

}