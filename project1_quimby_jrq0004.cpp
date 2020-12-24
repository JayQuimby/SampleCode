//
//  project1_quimby_jrq0004.cpp
//  I didnt use any outside sources beyond the note slides.
//
//  Created by Jack Quimby on 8/17/20.
//  Copyright © 2020 Jack Quimby. All rights reserved.
//
#include <iostream>
#include <string>
using std::cout; using std::endl; using std::string; using std::cin;

// declaration of variables to be used throughout the program

double loanAmount;
double interestRate;
double monthlyPayment;
double balance;

int main() {

  // recieve user input to make the table
    cout << "this program finds the number of months and interest paid on a loan"<< endl;
    cout << "Loan amount: "<< endl;
    cin >> loanAmount;

    // make sure the balance is positive
    while(loanAmount <= 0)
    {
      cout << "enter a value greater than 0." << endl;
      cin >> loanAmount;
    }

    cout << "Interest rate (% per year): "<< endl;
    cin >> interestRate;
    interestRate /= 12;
    cout << "Monthly payment: "<< endl;
    cin >> monthlyPayment;

// local variables for calculation and manipulation
    balance = loanAmount;
    double interest;
    double principal;
    double payment;
    int months = 0;
    double totalInterest = 0;
    bool increasing = false;
    int overflowCount = 0;

// calculate first payment
    interest = balance*interestRate/100;
    payment = (balance > monthlyPayment)? monthlyPayment: balance + interest;

    // check to make sure that the balance is decreasing
    if(payment < interest)
        increasing = true;

// create table header
    cout<<"*****************************************************************\n";
    cout<<"*                        Amortization Table                     *\n";
    cout<<"*****************************************************************\n";
    cout<<"Months  Balance         Payment    Rate    Interest     Principal" <<endl;
    cout.setf(std::ios::fixed);
    cout.precision(2);
    cout<<"0\t$" << balance << " \tN/A \t   N/A \t   N/A \t        N/A"<< endl;


    // loop finds the balance for the next month, prints the values and repeat.
    while(balance > 0 && overflowCount < 20)
    {
      //calculation to get the next months balance based on the interest paid
        interest = balance*interestRate/100;
        payment = (balance > monthlyPayment)? monthlyPayment: balance + interest; // conditional for last month case
        totalInterest += interest;
        principal = payment-interest;
        balance -= principal;
        months++;

        if(increasing) overflowCount++;

        // output results of calculation
        if(months < 10){
          cout << months << " \t";
        }
        else{
          cout << months << "\t";
        }
        cout.setf(std::ios::fixed);
        cout.precision(2);
        cout << "$" << balance;


        // this block is because the balance messes up formating and needs exception handling
        if(balance >= 1000){
          cout << "\t$";
        }
        else if(balance < 100 && balance >= 10){
          cout<<"  \t$";
        }
        else if(balance < 10 && balance > 0){
          cout<<"   \t$";
        }
        else if(balance == 0){
          cout <<"\t\t$";
        }
        else{
          cout << " \t$";
        }


        cout << payment << "\t   " << interestRate << "\t   $" << interest << "\t$" << principal << endl;

    }
    cout<<"*****************************************************************\n";

// output the total time and money spent
    if(!increasing){
        cout << "It takes " << months << " months to pay off the loan."<< endl;
        cout << "Total interest paid is: ";
        cout << "$" << totalInterest << endl;
    }
    // tell the user their numbers are not capable of being a loan that you can pay off
    else{
        cout << "you must increase your monthly payments in order to pay off the loan." << endl;
    }
    cout << endl;
}
