#ifndef controle_H_
#define controle_H_
#include <cassert>
#include <cstdlib>

class controle {
public:
	controle(double lp = .10 ,double tp = .8);
	bool query() const;
private:
	double landing_probability;
	double takeoff_probability;
};

class averager {
public:
	averager();
	void add_number(double value);
	int how_many_numbers() const { return count; }
	double average() const;
private:
	int count;
	double sum;
};

class takeoff {
public:
	takeoff(unsigned int t = 60);
	void one_second();
	void start_takeoff();
	bool is_busy() const { return (washTimeLeft > 0); }
private:
	unsigned int secondsForWash;
	unsigned int washTimeLeft;
};


controle::controle(double lp, double tp) {
	assert(lp <= 1 && tp <= 1);
	assert(lp >= 0 && tp >= 0);
	landing_probability = lp;
	takeoff_probability = tp;
}

bool controle::query() const {
	return (rand() < landing_probability * RAND_MAX);
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

void takeoff::one_second() {
	if (is_busy()) {
		washTimeLeft--;
	}
}

void takeoff::start_takeoff() {
	assert(is_busy());
	washTimeLeft = secondsForWash;
}

#endif // !controle_H_
