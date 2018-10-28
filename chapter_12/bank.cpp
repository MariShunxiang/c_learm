// back.cpp -- using the Queue interface 
// compile with queue.cpp
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "queue.h"
const int MIN_PER_HR = 60;

bool newcustomer(double x); // is there a new customer?

int main()
{
    using std::cin;
    using std::cout;
    using std::endl;
    using std::ios_base;
    // setting things up
    std::srand(std::time(0));   // random initializing

    cout << "Case Study: Bank of Heather Automatic Teller\n";
    cout << "Enter maximum size of queue: ";
    int qs;
    cin >> qs;
    Queue line(qs);     // line queue holds up to qs people

    cout << "Enter the number of simulation hours: ";
    int hours;          // hours of simulation
    cin >> hours;
    // simulation will run 1 cycle per minute
    long cyclelimit = MIN_PER_HR * hours;   // # of cycles

    cout << "Enter the average number of customers per hour: ";
    double perhour;     // average time between arrivals
    cin >> perhour;
    double min_per_cust;    // average time bewteen arrivals
    min_per_cust = MIN_PER_HR / perhour;
    
    Item temp;              // new customer date
    long turnaways = 0;     // turned away buy 
    long customers = 0;     // joined the queue
    long served = 0;        // served during line length
    long sum_line = 0;      // cumulative line length
    int wait_time = 0;      // time until autotiller is free
    long line_wait = 0;     // cumulative time in line
    
    // running the simulation
    for (int cycle = 0; cycle < cyclelimit; cycle++)
    {
        if (newcustomer (min_per_cust))     // heve newcomer
        {
            if (line.isfull())
                turnaways++;
            else
            {
                customers++;
                temp.set(cycle);    // cycle = time of arrival
                line.enqueue(temp); // add new customer to line
            }
        }

        if (wait_time <= 0 && !line.isempty())
        {
            line.dequque(temp);         // attend next customer
            wait_time = temp.ptime();   // for wait_time minutes
            line_wait += cycle - temp.when();
            served++;
        }

        if (wait_time > 0)
            wait_time--;

        sum_line += line.queuecount();
    }

    // reporting results
    if (customers > 0)
    {
        cout << "customers accepted: " << customers << endl;
        cout << " customers served: " << served << endl;
        cout << "       turnaways: " << turnaways << endl;
        cout << "average queue size: ";
        cout.precision(2);
        cout.setf(ios_base::fixed, ios_base::floatfield);
        cout.setf(ios_base::showpoint);
        cout << (double) sum_line / cyclelimit << endl;
        cout << " average wati time: "
            << (double) line_wait / served << " minutes\n";
    }
    else 
        cout << "No customers!\n";

    cout << "Done!\n";

    return 0;
}

bool newcustomer(double x)
{
    return (std::rand() * x / RAND_MAX < 1);
}

