//Main Program to test all Doubly Linked list methods
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <stdexcept>
#include "myHashTable_i127p615.hpp"
using namespace std;
int main(int argc, char* argv[])
{
if(argc != 3)
    {
        std::cout << "You have to provide one test instance file and output file name to run the test main!\n";
        return 0;
    }
//File Intiallization for input and output files
ifstream inFile;
ifstream inFile1;
inFile.open(argv[1]);
ofstream outfile (argv[2]);
//Open input and out file and sstart with hash table methods
if(inFile.is_open() and outfile.is_open())

  {
    int num;
  //Hahs table object with <int> as templete type
    myHashTable<int> hash;
    myDlList<int> dll;
    while(!inFile.eof())
    {
         inFile >> num;
/**
*  @Pre  A new instance has been read from input file
*  @Post Add the input instance from input file into Hah table using insert
*/
         hash.insert(num);
    }
/**
*  @Pre  The Hash table was built
*  @Post Display all the elements of hash table using DlList iterators
*/
    myDlList<int>::iterator i;
    for (int k=0; k< hash.hashsize() ;++k){
        outfile << k << ":  ";
        for (i= hash.getiteratorbegin(k); i != hash.getiteratorend(k); ++i)
          outfile <<"-->" << *i;
        outfile << "\n";
      }

//OPen a new file to get some elements from same instance file
    inFile1.open(argv[1]);
    int count=0;
    num=0;
  /**
  *  @Pre  Hash table as input
  *  @Check first 20 elements from input files are present in hash table
  */
    inFile1.open(argv[1]);
    count=0;
    num=0;
    while(!inFile1.eof() and (count !=20))
    {
         inFile1 >> num;
          if(hash.contains(num))
            outfile <<"1"<<"\n";
          else
            outfile<<"0"<<"\n";
         count=count+1;
    }
    inFile1.close();
  /**
  *  @Pre  Hash table as input
  *  @Remove  first 20 elements from input files from hash table
  */
    inFile1.open(argv[1]);
    count=0;
    num=0;
    while(!inFile1.eof() and (count !=20))
    {
         inFile1 >> num;
          if(hash.remove(num))
            outfile <<"1"<<"\n";
          else
            outfile<<"0"<<"\n";
         count=count+1;
    }
    inFile1.close();
  /**
  *  @Pre  Hash table as input
  *  @Check first 20 elements from input files are present in hash table
  */
    inFile1.open(argv[1]);
    count=0;
    num=0;
    while(!inFile1.eof() and (count !=20))
    {
         inFile1 >> num;
          if(hash.contains(num))
            outfile <<"1"<<"\n";
          else
            outfile<<"0"<<"\n";
         count=count+1;
    }
    inFile1.close();

  /**
  *  @Pre  Hash table as input
  *  @Post Make hash table empty
  */
    hash.makeEmpty();
  }
else
  {
      cout << "The instance.txt file cannot be opened";
  }
inFile.close();
outfile.close();
}
