//
//  project2_quimby_jrq0004.cpp
//  I did not use any outside sources except the lecture slides
//  To run, simply compile and execute. All output should wait for aknowlegment
//  from the user to continue at each simulation stage.
//
//  Created by Jack Quimby on 9/9/20.
//  Copyright © 2020 Jack Quimby. All rights reserved.
//
#include <iostream>
#include <ctime>
#include <assert.h>
#include <stdlib.h>

using std::cout; using std::endl; using std::cin;

bool twoOrMore(bool aLiving, bool bLiving, bool cLiving); // two or more prototype

int aaronShoots1(bool& bLiving, bool& cLiving); // all the different shooting prototypes
int aaronShoots2(bool& bLiving, bool& cLiving);
int bobShoots(bool& aLiving, bool& cLiving);
int charlieShoots(bool& aLiving, bool& bLiving);

int duel(void); // the two kinds of duel
int duel2(void);

void runTest1(void); // looping fucntion for statistic analysis
void runTest2(void);
void buffer(void);

void testTwoOrMore(void);   // testing functions for all the functions used
void testAaronShoots1(void);
void testAaronShoots2(void);
void testBobShoots(void);
void testCharlieShoots(void);

double aPercent1 = 0.0; // variables to store aaron's win percentages for comparison
double aPercent2 = 0.0;

int main()
{
  srand(time(0)); // initilize randon number generator

  // the simulation starts and runs through the tests before simulating duels
  cout<< "\n**** welcome to Jack's Duel Simulator ****\n";
  testTwoOrMore();
  buffer();
  testAaronShoots1();
  buffer();
  testAaronShoots2();
  buffer();
  testBobShoots();
  buffer();
  testCharlieShoots();

  // after completing testing of the code we run  the simulations 10000 times each
  cout << "\nready to run duel simulation 1: (10000 trials)\n";
  buffer();
  runTest1();
  cout << "\nready to run duel simulation 2: (10000 trials)\n";
  buffer();
  runTest2();

// compare which strategy had better results for Aaron
  if(aPercent1 > aPercent2)
    cout << "\nstrategy 1 is better than strategy 2\n";
  else
    cout << "\nstrategy 2 is better than strategy 1\n";
  cout<<"\n***** simulation ended *****\n";
  return 0;
}

// waiting method in between tests
void buffer(void)
{
  cout << "press enter to continue...\n";
  cin.ignore().get();
}

// uses an array to store wins for each player
// the while loop runs a designated amount of times
// once all trials have been completed the statistics are calculated and printed
void runTest1(void)
{
  int trials = 10000;
  int count = 0;
  int wins [3] = {};

  while(count < trials)
  {
    int result = duel();
    wins[result]++;
    count++;
  }
  double winPercent = (double)wins[0]/(double)trials*100;
  aPercent1 = winPercent;
  cout.precision(4);
  cout << "Aaron won "<< wins[0]<<"/"<<trials << " duels or " << winPercent << "%\n";
  winPercent = (double)wins[1]/(double)trials*100;
  cout << "Bob won "<< wins[1]<<"/"<<trials << " duels or " << winPercent << "%\n";
  winPercent = (double)wins[2]/(double)trials*100;
  cout << "Charlie won "<< wins[2]<<"/"<<trials << " duels or " << winPercent << "%\n";
}

// literal copy of runTest1 but with aaron using strategy 2
void runTest2(void)
{
  int trials = 10000;
  int count = 0;
  int wins [3] = {};

  while(count < trials)
  {
    int result = duel2();
    wins[result]++;
    count++;
  }
  double winPercent = (double)wins[0]/(double)trials*100;
  aPercent2 = winPercent;
  cout.precision(4);
  cout << "Aaron won "<< wins[0]<<"/"<<trials << " duels or " << winPercent << "%\n";
  winPercent = (double)wins[1]/(double)trials*100;
  cout << "Bob won "<< wins[1]<<"/"<<trials << " duels or " << winPercent << "%\n";
  winPercent = (double)wins[2]/(double)trials*100;
  cout << "Charlie won "<< wins[2]<<"/"<<trials << " duels or " << winPercent << "%\n";
}

// counts the amount of turns to keep the order designated by the game
// starts with all players living and uses the booleans for reference in the shooting functions
//the conditions for a player to shoot are that they must be living and it must be their turns
// the function returns the index of the winner which is then used to incrament the array in runTest
int duel(void)
{
  int turn = 0;
  bool aAlive = true;
  bool bAlive = true;
  bool cAlive = true;

  while(twoOrMore(aAlive, bAlive, cAlive))
  {
    if(aAlive && turn%3 == 0){
      aaronShoots1(bAlive, cAlive);
    }
    else if(bAlive && turn%3==1){
      bobShoots(aAlive, cAlive);
    }
    else if(cAlive && turn%3==2){
      charlieShoots(aAlive, bAlive);
    }
    //cout <<"abc" << endl;
    //cout << aAlive << bAlive << cAlive << endl;
    turn++;
    //break;
  }
  if(aAlive)
    return 0;
  else if(bAlive)
    return 1;
  else
    return 2;
}

// copy of duel but for Aaron's second strategy

int duel2(void)
{
  int turn = 0;
  bool aAlive = true;
  bool bAlive = true;
  bool cAlive = true;

  while(twoOrMore(aAlive, bAlive, cAlive))
  {
    if(aAlive && turn%3 == 0){
      aaronShoots2(bAlive, cAlive);
    }
    else if(bAlive && turn%3==1){
      bobShoots(aAlive, cAlive);
    }
    else if(cAlive && turn%3==2){
      charlieShoots(aAlive, bAlive);
    }
    //cout <<"abc" << endl;
    //cout << aAlive << bAlive << cAlive << endl;
    turn++;
    //break;
  }
  if(aAlive)
    return 0;
  else if(bAlive)
    return 1;
  else
    return 2;
}

// tests if there are at least two people still left in the match
// this is used to keep the while loop going until the round has concluded with one winner
// I used boolean algebra to reduce the expression to simplest form
bool twoOrMore(bool aLiving, bool bLiving, bool cLiving)
{
  if((aLiving&&bLiving)||(aLiving&&cLiving)||(bLiving&&cLiving))
    return true;
  else
    return false;
}

// this strategy implements that aaron should shoot if one or both of his opponents is alive
// he shoots with an accuracy of 33% if he manages to hit them then their respective boolean is changed to false
int aaronShoots1(bool& bLiving, bool& cLiving)
{
  int shooting = 3;
  int aProbability = rand() % 100;
  if(bLiving + cLiving >= 1)
  {
    if(cLiving == 1)
    {
      if(aProbability <= 33)
        cLiving = 0;
      shooting = 2;
    }
    else if(bLiving == 1)
    {
      if(aProbability <= 33)
        bLiving = 0;
      shooting = 1;
    }
  }
  return shooting;
}

// this is the second implementation for aaron, where he does not shoot unless he is in a solo duel
// this lets the other more skilled shooters fight it out and keeps them from trying to kill him
// the only real diference is b+c == 1 instead of b+c >= 1
int aaronShoots2(bool& bLiving, bool& cLiving)
{
  int shooting = 3;
  int aProbability = rand() % 100;
  if(bLiving + cLiving == 1)
  {
    if(cLiving == 1)
    {
      if(aProbability <= 33)
        cLiving = 0;
      shooting = 2;
    }
    else if(bLiving == 1)
    {
      if(aProbability <= 33)
        bLiving = 0;
      shooting = 1;
    }
  }
  else
    shooting = 0;
  return shooting;
}

// analogous to Aaron's first strategy but he shoots at charlie before Aaron and has a 50% chance
// to hit his target as compared to 33% for Aaron
int bobShoots(bool& aLiving, bool& cLiving)
{
  int shooting = 3;
  int bProbability = rand() % 100;
  if(aLiving + cLiving >= 1)
  {
    if(cLiving == 1)
    {
      shooting = 2;
      if(bProbability <= 50)
        cLiving = 0;
    }

    else if(aLiving == 1)
    {
      shooting = 0;
      if(bProbability <= 50)
        aLiving = 0;
    }
  }
  return shooting;
}

// same as bob's strategy but charlie targets bob over Aaron and charlie never misses

int charlieShoots(bool& aLiving, bool& bLiving)
{
  int shooting = 3;
  if(aLiving + bLiving >= 1)
  {
    if(bLiving == 1)
    {
      bLiving = 0;
      shooting = 1;
    }
    else if(aLiving == 1)
    {
      aLiving = 0;
      shooting = 0;
    }
  }
  return shooting;
}

// brute force testing for the two or more functions I based it on a truth table
// basic format of testing driver: lable test -> assert that what you expect is happening -> print results
// this pattern is repeated for all of the following testing functions
void testTwoOrMore(void)
{
  cout << "Unit testing 1: Function - twoOrMore() \n";

  cout << "\tcase 1: Aaron alive, Bob alive, Charlie alive\n";
  assert(true == twoOrMore(true,true,true));
  cout << "\t\tcase passed...\n";

  cout << "\tcase 2: Aaron dead, Bob alive, Charlie alive\n";
  assert(true == twoOrMore(false,true,true));
  cout << "\t\tcase passed...\n";

  cout << "\tcase 3: Aaron alive, Bob dead, Charlie alive\n";
  assert(true == twoOrMore(true,false,true));
  cout << "\t\tcase passed...\n";

  cout << "\tcase 4: Aaron alive, Bob alive, Charlie dead\n";
  assert(true == twoOrMore(true,true,false));
  cout << "\t\tcase passed...\n";

  cout << "\tcase 5: Aaron dead, Bob dead, Charlie alive\n";
  assert(false == twoOrMore(false,false,true));
  cout << "\t\tcase passed...\n";

  cout << "\tcase 6: Aaron alive, Bob dead, Charlie dead\n";
  assert(false == twoOrMore(true,false,false));
  cout << "\t\tcase passed...\n";

  cout << "\tcase 7: Aaron dead, Bob alive, Charlie dead\n";
  assert(false == twoOrMore(false,true,false));
  cout << "\t\tcase passed...\n";

  cout << "\tcase 8: Aaron dead, Bob dead, Charlie dead\n";
  assert(false == twoOrMore(false,false,false));
  cout << "\t\tcase passed...\n";
}

// had to define local variables in order to test the outcomes because you cant pass in literals?
// its a test driver so its very similar to the previous one
void testAaronShoots1(void)
{
  bool b = true;
  bool c = true;
  cout << "Unit testing 2: Function - aaronShoots1(bAlive, cAlive)\n";

  cout << "\tcase 1: bob alive, charlie alive\n";
    assert(2 == aaronShoots1(b, c));
  cout << "\t\taaron shoots charlie\n";

  b = false;
  c = true;
  cout << "\tcase 2: bob dead, charlie alive\n";
    assert(2 == aaronShoots1(b, c));
  cout << "\t\taaron shoots charlie\n";

  b = true;
  c = false;
  cout << "\tcase 3: bob alive, charlie dead\n";
    assert(1 == aaronShoots1(b, c));
  cout << "\t\taaron shoots bob\n";
}

// copy of testAaronShoots1 but for the second strategy
void testAaronShoots2(void)
{
  bool b = true;
  bool c = true;
  cout << "Unit testing 3: Function - aaronShoots2(bAlive, cAlive)\n";

  cout << "\tcase 1: bob alive, charlie alive\n";
    assert(0 == aaronShoots2(b, c));
  cout << "\t\taaron missed intentionally\n";

  b = false;
  c = true;
  cout << "\tcase 2: bob dead, charlie alive\n";
    assert(2 == aaronShoots2(b, c));
  cout << "\t\taaron shoots charlie\n";

  b = true;
  c = false;
  cout << "\tcase 3: bob alive, charlie dead\n";
    assert(1 == aaronShoots2(b, c));
  cout << "\t\taaron shoots bob\n";
}

// copy of aaron test with adjusted numbers for bob's expected results
void testBobShoots(void)
{
  bool a = true;
  bool c = true;
  cout << "Unit testing 4: Function - bobShoots(aAlive, cAlive)\n";

  cout << "\tcase 1: aaron alive, charlie alive\n";
    assert(2 == bobShoots(a, c));
  cout << "\t\tbob shoots charlie\n";

  a = false;
  c = true;
  cout << "\tcase 2: aaron dead, charlie alive\n";
    assert(2 == bobShoots(a, c));
  cout << "\t\tbob shoots charlie\n";

  a = true;
  c = false;
  cout << "\tcase 3: aaron alive, charlie dead\n";
    assert(0 == bobShoots(a, c));
  cout << "\t\tbob shoots aaron\n";
}

// another copy of Aaron test with adjusted numbers for testing charlie
void testCharlieShoots(void)
{
  bool b = true;
  bool a = true;
  cout << "Unit testing 5: Function - charlieShoots(aAlive, bAlive)\n";

  cout << "\tcase 1: bob alive, aaron alive\n";
    assert(1 == charlieShoots(a, b));
  cout << "\t\tcharlie shoots bob\n";

  b = false;
  a = true;
  cout << "\tcase 2: bob dead, aaron alive\n";
    assert(0 == charlieShoots(a, b));
  cout << "\t\tcharlie shoots aaron\n";

  b = true;
  a = false;
  cout << "\tcase 3: bob alive, aaron dead\n";
    assert(1 == charlieShoots(a, b));
  cout << "\t\tcharlie shoots bob\n";
}
