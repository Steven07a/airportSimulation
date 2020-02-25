// airportSimulation.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "C:\Users\Steven_dev\Desktop\CS_Stuff\includes/queue.h"
#include "controler.h"

int main()
{
    Queue<int>* q = new Queue<int>;
    controle c;
    for (int i = 0; i < 100; i++) {
        std::cout << c.query() << std::endl;
    }
}

