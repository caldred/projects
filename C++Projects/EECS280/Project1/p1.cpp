#include "io.h"
#include <cstdlib>

using namespace std;

int main()
{
    //declare variables
    double payment, rate, balance, oldBalance, years;
    int years_check;

    //take input for parameters
    payment = GetParam("Please enter the monthly payment: ", 1, 100000);
    rate  = GetParam("Please enter the interest rate: ", 0, 1);
    years = GetParam("Please enter the duration of the loan, in years: ",
                     1, 100);

    //check that years is an integer, and if not, then repeat prompt
    years_check = years;
    while (years_check != years)
    {
        years = GetParam("Please enter the duration of the loan, in years: ",
                         1, 100);
        years_check = years;
    }

    //print out the monthly payment data for the car loan with a nice header
    balance = 0;
    PrintHeader();
    for(int i = years * 12; i > 0; i--)
    {
        oldBalance = balance;
        balance = (payment + oldBalance)/(1 + rate / 12);
        PrintMonthlyData(i, balance - oldBalance,
                         payment - (balance - oldBalance), balance);
    }
}
