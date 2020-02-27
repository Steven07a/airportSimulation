#ifndef controle_H_
#define controle_H_
#include <cassert>
#include <cstdlib>

class control {
public:
	control(double lp = .20 ,double tp = .08);
	bool takeoffQuery() const;
	bool landingQuery() const;
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
	takeoff(unsigned int takeoff_time = 15, unsigned int landing_time = 5);
	void one_second();
	void start_takeoff();
	void start_landing();
	bool is_busy() const;
private:
	unsigned int time_to_land;
	unsigned int time_to_takeoff;
	unsigned int seconds_to_land;
	unsigned int seconds_to_takeoff;
};


#endif // !controle_H_