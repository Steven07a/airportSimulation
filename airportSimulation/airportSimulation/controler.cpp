#include <cassert>
#include <cstdlib>
#include <iostream>
#include"controler.h"
using namespace std;

control::control(double lp, double tp) {
	assert(lp <= 1 && tp <= 1);
	assert(lp >= 0 && tp >= 0);
	landing_probability = lp;
	takeoff_probability = tp;
}

bool control::landingQuery() const {
	return (rand() < landing_probability * RAND_MAX);
}

bool control::takeoffQuery() const {
	return (rand() < takeoff_probability * RAND_MAX);
}

averager::averager() {
	count = 0;
	sum = 0;
}

void averager::add_number(double value) {
	count++;
	sum += value;
}

double averager::average() const {
	assert(count > 0);
	return (sum / count);
}

takeoff::takeoff(unsigned int takeoff_time, unsigned int landing_time) {
	seconds_to_land = landing_time;
	seconds_to_takeoff = takeoff_time;
	time_to_land = 0;
	time_to_takeoff = 0;
}
void takeoff::one_second() {
	if (time_to_land > 0) {
		time_to_land--;
	}
	else if (time_to_takeoff > 0){
		time_to_takeoff--;
	}

}

void takeoff::start_takeoff() {
	assert(!is_busy());
	time_to_takeoff = seconds_to_takeoff;
}

void takeoff::start_landing() {
	assert(!is_busy());
	time_to_land = seconds_to_land;
}

bool takeoff::is_busy() const {
	if (time_to_land > 0) {
		return true;
	}
	else if (time_to_takeoff > 0) {
		return true;
	}
	else {
		return false;
	}
}