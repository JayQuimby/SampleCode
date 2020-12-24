//
//  project4_quimby_jrq0004.cpp
//  I did not use outside sources except for Linked list help from: https://www.codesdope.com/blog/article/c-linked-lists-in-c-singly-linked-list/
//  I used this source to get an idea of implementation for a class structure linked list
//  Just compile and run, for testing un-comment the TESTING symbol.
//  The program is a trivia game that users may input questions and answers then play the
//  game with their questions, plus the default questions.
//  I have tested my code on AU servers.
//
//  Created by Jack Quimby on 10/16/20.
//  Copyright © 2020 Jack Quimby. All rights reserved.
//
#include <iostream> // for cin and cout
#include <assert.h> // for testing methods

//#define TESTING 1   // <---- Testing symbol

using std::cout; using std::cin; using std::endl;  using std::string;

void runCase1(); // test case 1 method for testing stage
void runCase2(); // test cases 2.1 and 2.2 for tesing stage
void runCase3(); // test case 3 method for testing stage
void runCase4(); // test case 4 method for testing stage
void addDefault(); // adds the default question, answer, and point value in the linked List
bool addQuestion(); // method that prompts users question, answer and point Value
int play(int rounds); // method that gives the player the number of questions given by
                      // the rounds integer and checks corectness while keeping score.

/*------------------------------------------------------------------------
  TriviaNode is used to create a linked structure.
  no constructor, used value assignment with -> symbol.
  stores index in the list, question, andswer, points, and next TriviaNode.
  has toString method for testing purposes.
  ------------------------------------------------------------------------*/

struct TriviaNode
{
  int index;
  string question;
  string answer;
  int points;
  TriviaNode* next;

  string toString()
  {
    return question + "  ,  " + answer;
  }
} ;

/*------------------------------------------------------------------------
  TriviaList is a pointer-linked structure that is used to store all the
  nodes in inserted order. It uses two pointers, one at the head the other
  at the tail, and has the number of elements as an integer.
  constructor innitilizes pointers to null and size to 0.
  contains methods add, print, get, and size. add inserts an element to
  the end, print outputs the data in the node designated. get returns the
  pointer associated with an input index. size returns the number of trivia
  ------------------------------------------------------------------------*/

class TriviaList
{
private:
  TriviaNode *head, *tail;
  int numQs, points;
public:

  TriviaList()
  {
    head = NULL;
    tail = NULL;
    numQs = 0;
  }

  void add(string q, string a, int p)
  {
    numQs++;

    // create new node and assign all values
    TriviaNode* newNode = new TriviaNode;
    newNode->question = q;
    newNode->answer = a;
    newNode->points = p;
    newNode->index = numQs;
    newNode->next = NULL;

    // insert as head if head DNE
    if(head == NULL)
    {
      head = newNode;
      tail = newNode;
    }
    else // indert as node after tail then assign new node as tail
    {
      tail->next = newNode;
      tail = tail->next;
    }
  }
  // find node with index i then cout the data in it
  void print(int i)
  {
    TriviaNode* cur = head;
    while(cur->next != NULL && cur->index != i)
      cur = cur->next;
    cout << cur->question << " , " << cur->answer << " , " << cur->points << endl;
  }

 // find node with index i then return the pointer pointing at it
  TriviaNode* get(int i)
  {
    if(i > this->numQs) return NULL;
    TriviaNode* cur = head;
    for(int x = 1; x < i; x++)
      cur = cur->next;
    return cur;
  }

  // returns numQs.
  int size()
  {
    return numQs;
  }

  void addPts(int p)
  {
    points += p;
  }

  int getPts()
  {
    return points;
  }
};

TriviaList game = TriviaList(); // global linked list that stores all q's and a's


/*------------------------------------------------------------------------
  main is used to create the two different coding enviornments, testing and
  production. testing version is defined when TESTING is defined and production
  is used otherwise. testing produces the test case output as specefied by
  the project description. production mode produces the actual game sequence.
  ------------------------------------------------------------------------*/
int main()
{

  #ifdef TESTING  // testing methods

  cout << "*** Debug Version ***" << endl;
  runCase1();
  addDefault();
  runCase2();
  runCase3();
  runCase4();
  cout << "*** testing concluded ***" << endl;

  #else // production methods

  bool moreQs = true;

  cout << "*** Welcome to Jack's trivia quiz game ***\n";

  addDefault();

  while(moreQs) moreQs = addQuestion();

  cout << "-_-_-_-_-_-_-_-_-_-_-_-_-  quiz time  -_-_-_-_-_-_-_-_-_-_-_-_-\n"
       << "Press Enter to continue... ";

  play(game.size());

  cout << "*** Thanks for playing the trivia game. Goodbye! ***\n";

  #endif
}

/*------------------------------------------------------------------------
  play is the method used to make the game run after all the questions have
  created and inserted into the linked list. the method checks that there
  is at least one question and will not allow you to play more than the
  number of trivia in the list. outputs 0 if failed and 1 if not.
  ------------------------------------------------------------------------*/
int play(int rounds)
{
  // warning for list the has no questions
  if(game.size() == 0 || rounds == 0)
  {
    cout << "Warning - the number of trivia to be asked must be greater than or equal to 1\n";
    return 0;
  }

  if(rounds == -1) // code to play all questions in the list
    rounds = game.size();

  if(rounds > game.size()) // check for overflow error then output warning
  {
    cout << "Warning - there are only "<< game.size() << " trivia in the list.\n";
    return 0;
  }
  // initilize variables to be used
  string ans;
  TriviaNode* cur;
  cin.ignore().get();  // pause
  //for(int x = 0; x < 80; x++) cout << "\n"; // clear the screen so answers can't be seen

  // loop : get question -> display question -> get answer -> determine if correct -> add points |
  for(int x = 1; x <= rounds; x++)
  {
    cur = game.get(x);
    cout << "Question: " << cur->question << endl;
    cout << "Answer: ";
    getline(cin, ans);
    if(ans == cur->answer)
    {
      cout << "Your answer was correct. you recieve " << cur->points << " points.\n";
      game.addPts(cur->points);
    }
    else
    {
      cout << "Your answer is wrong. The correct answer was: " << cur->answer << endl;
    }
    cout << "Your total points: " << game.getPts() << "\n\n";
  }

  return 1; // shows method was completed.
}

/*------------------------------------------------------------------------
  addQuestion uses cin and cout in order to get user data and creates a new
  TriviaNode with the data then usse the Linked List's add method to put
  the new node in the list so it can be used in the game. returns false
  if the user is done adding questions and true if they want to add more.
  ------------------------------------------------------------------------*/

bool addQuestion()
{
  // initilize variables to be used
  string q;
  string a;
  string con;
  int p;

  if(game.size() > 3) cin.get(); // pause for cin stream

  cout << "Enter a question: " ;
  getline(cin,q);

  cout << "Enter an answer: " ;
  getline(cin,a);

  cout << "Enter award points: " ;
  cin >> p;

  game.add(q,a,p); // add new trivia based on input


  cout << "Continue? (Yes/No): ";
  cin >> con;
  cout << endl;

  return (con == "Yes" || con == "yes") ? true : false ; // used for loop to add multiple questions
}

/*------------------------------------------------------------------------
  addDefault adds the three default questions given by the project description
  it also uses the linked list's add method to add them to the list.
  ------------------------------------------------------------------------*/

void addDefault()
{
  // uses add method with literals for all three.
  game.add("How long was the shortest war on record? (Hint: how many minuites)",
    "38", 100);
  game.add("What was the Bank of America's original name? (Hint: Bank of Italy or Bank of Germany)",
    "Bank of Italy", 50);
  game.add("What it the best-selling video game of all time? (Hint: call of Duty or Wii Sports?)",
    "Wii Sports", 20);
}

/*------------------------------------------------------------------------
  runs test 1 : no questions in the linked list. tests to see if play()
  exits with code 0 using assert. warning message is displayed
  ------------------------------------------------------------------------*/

void runCase1()
{
  cout << "Unit Test Case 1: Ask no question. Program should give a warning.\n";
  int comp = play(0);
  assert(comp == 0);
  cout << "Case 1 passed. \n\n";
}

/*------------------------------------------------------------------------
  runs test 2.1 and 2.2 : check for a wrong answer, check for correct answer.
  both cases exit with code 1 and are checked by assert.
  ------------------------------------------------------------------------*/

void runCase2()
{
  cout << "Unit Test Case 2.1: Ask 1 question in the trivia. The tester enters incorrect answer.\n";
  int comp = play(1);
  assert(comp == 1);
  cout << "Case 2.1 passed. \n\n";
  cout << "Unit Test Case 2.2: Ask 1 question in the trivia. The tester enters correctly.\n";
  comp = play(1);
  assert(comp == 1);
  cout << "Case 2 passed. \n\n";
}

/*------------------------------------------------------------------------
  runs test 3 : play through all questions in the list. checks that the play
  method exits with code 1 using assert.
  ------------------------------------------------------------------------*/

void runCase3()
{
  cout << "Unit Test Case 3: Ask all question in the trivia\n";
  int comp = play(-1);
  assert(comp == 1);
  cout << "Case 3 passed. \n\n";
}

/*------------------------------------------------------------------------
  runs test 4 : attempts to get a question that does not exist. checks for
  code 0 exit, with warning, using assert.
  ------------------------------------------------------------------------*/

void runCase4()
{
  cout << "Unit Test Case 4: Ask more questions than in the list\n";
  int comp = play (5);
  assert(comp == 0);
  cout << "Case 4 passed. \n\n";
}
