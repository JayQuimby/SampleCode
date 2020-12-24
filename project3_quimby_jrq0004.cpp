//
//  project3_quimby_jrq0004.cpp
//  I did not use any outside sources except the lecture slides
//  This program needs to be compiled and run and I have tested it on AU servers
//  The program takes two sorted input files and merges them in sorted order, outputing to a file
//  chosen by the user.
//
//  Created by Jack Quimby on 9/23/20.
//  Copyright © 2020 Jack Quimby. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <cstdlib>

using std::cout; using std::endl; using std::cin; using std::ifstream; using std::ofstream; using std::string;

// declaration of all functions used for the program
int sort(int inArray1[], int inArray1Size, int inArray2[], int inArray2Size, int outArray[]);
void writeFile(int outArray[], int outArraySize, string fileName);
int readFile(int inArray[], ifstream& inStream);
int printInData(int array[], int arraySize);
int printOutData(int array[], int arraySize);
int compare(int a, int b);

int MAX_SIZE = 100; // maximum number of elements in an array



int main()
{

  int inArray1[MAX_SIZE];
  int inArray1Size;
  int inArray2[MAX_SIZE];
  int inArray2Size;
  int outArray[MAX_SIZE*2];
  int outArraySize;

  string file1;
  string file2;

  ifstream inStream1;
  ifstream inStream2;

// this starts the inital output of the program prompting the input of the user
  cout << "*** Welcome to Jack's sorted array merger ***\n";
  cout << "Name of file 1:";
  cin >> file1;
  // this opens the stream for the first input file then checks to see that the file exists
  // once the file is open it gets the size and puts the data into an array the  closes the stream
  inStream1.open((char*)file1.c_str());
  if(inStream1.fail())
  {
    cout << "the file failed to open" << endl;
    exit(1);
  }
  inArray1Size = readFile(inArray1, inStream1);
  inStream1.close();
  cout << "the list of " << inArray1Size << " numbers in " << file1 << " is:\n";
  printInData(inArray1, inArray1Size); // prints all the data from file 1
//  prompt input from file 2
  cout << "Name of file 2:";
  cin >> file2;
  //  repeat of input process for file 2
  inStream2.open((char*)file2.c_str());
  if(inStream2.fail())
  {
    cout << "the file failed to open" << endl;
    exit(1);
  }
  inArray2Size = readFile(inArray2, inStream2);
  inStream2.close();
  cout << "the list of " << inArray2Size << " numbers in " << file2 << " is:\n";
  printInData(inArray2, inArray2Size);

// sort and merge the two input arrays and assign the length to outArraySize
  outArraySize = sort(inArray1, inArray1Size, inArray2, inArray2Size, outArray);
  cout << "the sorted list of " << outArraySize << " numbers is: ";
  printOutData(outArray, outArraySize);// output the data in the merged output array

  string outFile;

// prompt file to put the merged data into
  cout << "Enter file to output to:";
  cin >> outFile;
  writeFile(outArray, outArraySize, outFile); // write merged data to output file
  cout << "***Please check output file - "<< outFile << "***\n";
  cout << "***program terminaing***\n";
}

// this function is used to merge the data togeter in sorted order and then returns the size of
// the output array
int sort(int inArray1[], int inArray1Size, int inArray2[], int inArray2Size, int outArray[])
{
  int index1 = 0;
  int index2 = 0;
  int outIndex = 0;

// loop used to add data to the output array until all data from both arrays is merged
  while (index1 < inArray1Size || index2 < inArray2Size)
  {
    // this if-else if-else block is to determine which array to take the next value from
    if(index1 == inArray1Size)
    {

      outArray[outIndex] = inArray2[index2];
      index2++;
    }
    else if(index2 == inArray2Size)
    {

      outArray[outIndex] = inArray1[index1];
      index1++;
    }
    else
    {
      // determine which number is greater and adds from that array to the merged array
      int delta = compare(inArray1[index1], inArray2[index2]);

      if(delta == 1)
      {

        outArray[outIndex] = inArray2[index2];
        index2++;
      }
      else if(delta == -1)
      {

        outArray[outIndex] = inArray1[index1];
        index1++;
      }
      else
      {
        // in the case that both arrays have the same value it add both values
        outArray[outIndex] = inArray2[index2];
        index2++;
        outIndex++;
        outArray[outIndex] = inArray1[index1];
        index1++;
      }
    }


    outIndex++;
  }

// returns the combined size of both the input arrays
  return inArray1Size + inArray2Size;
}

// this function is used to write the data from an array to a file given by a string
void writeFile(int outArray[], int outArraySize, string fileName)
{
  ofstream outStream;
  outStream.open((char*)fileName.c_str());
  // adds values one by one to the output file sepparated by a new line
  for(int x = 0; x < outArraySize; x++)
  {
    outStream << outArray[x] << "\n";
  }
  outStream.close();
}

// reads all unput from a file of integer values using an input stream reference
int readFile(int inArray[], ifstream& inStream)
{
  int index = 0;

  inStream >> inArray[index];

  while(!inStream.eof())
  {
    index++;
    inStream >> inArray[index];
  }

  return index;
}

// prints the values of a given array to the console sepparated by a new line
int printInData(int array[], int arraySize)
{
  for (int x = 0; x < arraySize; x++){
    cout << array[x] << endl;
  }
  return 0;
}

// prints the values of an array sepparated by a space
int printOutData(int array[], int arraySize)
{
  for (int x = 0; x < arraySize; x++){
    cout << array[x] << " ";
  }
  cout << endl;
  return 0;
}
// outputs 1 if a > b, 0 if a = b, and -1 if a < b
// used to determine which array to take the next value from
int compare(int a, int b){
  if(a > b) return 1;
  else if(a < b) return -1;
  else return 0;
}
