// error5.cpp -- unwinding the stack
#include <iostream>
#include <cmath>        // or math.h, UNIX users may need -lm flag
#include <cstring>
#include "exc_mean.h"

class demo
{
private:
    char word[40];
public:
    demo(const char * str)
    {
        std::strcpy(word, str);
        std::cout << "demo " << word << " created\n";
    }
    ~demo()
    {
        std::cout << "demo " << word << " destoryed\n";
    }
    void show() const 
    {
        std::cout << "demo " << word << " lives!\n";
    }
};

// functoin prototypes
double hmean(double a, double b) throw(bad_hmean);
double gmean(double a, double b) throw(bad_gmean);
double means(double a, double b) throw(bad_hmean, bad_gmean);

int main()
{
    using std::cout;
    using std::cin;
    using std::endl;

    double x, y, z;
    demo d1("found in main");
    cout << "Enter two numbers: ";
    while(cin >> x >> y){   // start of try block
        try {
            z = means(x, y);
            cout << "The mean mean of " << x << " and " << y
                << " is " << z << endl;
            cout << "Entry next pair: ";
        } // end of block
        catch (bad_hmean & bg)  // start of catch block
        {
            bg.mesg();
            cout << "Try again.\n";
            continue;
        }
        catch (bad_gmean hg)
        {
            cout << hg.mesg();
            cout << "Values used: " << hg.v1 << ", "
                << hg.v2 << endl;
            cout << "Sorry, you don't get to play any more.\n";
            break;
        }   // end of catch block
    }
    d1.show();
    cout << "Bye!\n";
    return 0;
}

double hmean(double a, double b) throw(bad_hmean)
{
    if (a == -b) {
        throw bad_hmean(a, b);
    }
    return 2.0 * a * b / (a + b);
}

double gmean(double a, double b) throw(bad_gmean)
{
    if (a < 0 || b < 0 ) {
        throw bad_gmean(a, b);
    }
    return std::sqrt(a * b);
}

double means(double a, double b) throw(bad_hmean, bad_gmean)
{
    double am, hm, gm;
    demo d2("found in means()");
    am = (a + b) / 2.0;     // arithmetic mean
    try
    {
        hm = hmean(a, b);
        gm = gmean(a , b);
    }
    catch(bad_hmean & bg)   // start of catch block
    {
        bg.mesg();
        std::cout << "Caught in mean()\n";
        throw;      // rethrows the exception
    }
    d2.show();
    return (am + hm + gm) / 3.0;
}

