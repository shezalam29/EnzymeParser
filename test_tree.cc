// Shezan Alam

// References: Data Structures and Algorithm Analysis in C++ by Mark A. Weiss 
// References: Sven Dietrich CSCI 335 Slides


#include "avl_tree.h"
// You will have to add #include "sequence_map.h"
#include "sequence_map.h"

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <math.h>
using namespace std;

namespace {

// @dbx_filename: an input database filename.
// @seq_filename: an input sequences filename.
// @a_tree: an input tree of the type TreeType. It is assumed to be
//  empty.
template <typename TreeType>
void TestTree(const string &dbx_filename, const string &seq_filename, TreeType &a_tree) {
// Code for running Part 2.2
std::ifstream inputfile{dbx_filename};
  
string db_line_;
  
  // for loop is for reading through header of file/junk
for(int i = 0; i < 10; ++i) {
  getline(inputfile, db_line_);
}


// reading file 
while(getline(inputfile, db_line_))
{
   string an_enz_acro;
   string a_reco_seq;
     

  db_line_ = db_line_.substr(0, db_line_.length()-2);
  stringstream strstream(db_line_);
  // reads first part of line with delimiter '/' 
  // which is an enzyme acronym
  getline(strstream,an_enz_acro, '/');  //puts enzyme acronym in variable
    
  while(getline(strstream, a_reco_seq,'/')){  //second while for rest of line
    SequenceMap map_(a_reco_seq, an_enz_acro);
      a_tree.insert(map_);
  } //End first while 
} //End second while 
  
// Variables to store all calculations 
float numberNodes = a_tree.getNodes();
float avgDepth = (float) a_tree.getLength() / numberNodes;
float ratio = (float) avgDepth / log2(numberNodes);


ifstream inputfile2{seq_filename}; //read from file with sequences 
string line_;
float successQueries = 0;
float totalRecCalls = 0;

while (getline(inputfile2, line_))
{
  SequenceMap map_2(line_, {});
  if (a_tree.contains(map_2))
  {
    successQueries++; 
    totalRecCalls += a_tree.getNumberRecursiveCalls();
  }

}

inputfile2.close();

float avgRecursiveCalls = (float) totalRecCalls / successQueries;

//Print statements 
cout << "2: " << numberNodes << endl;
cout << "3a: " << avgDepth << endl;
cout << "3b: " << ratio << endl; 
cout << "4a: " << successQueries << endl; 
cout << "4b: " << avgRecursiveCalls << endl; 

ifstream inputfile3{seq_filename};
string line_2;

float successRemoves = 0;
float recursiveRemove = 0;
   
while (getline(inputfile3, line_2))
{
  SequenceMap map_3 (line_2, {});
  successRemoves += 1; 
  a_tree.remove(map_3);
  recursiveRemove += a_tree.getNumberRecursiveCalls();

  getline(inputfile3, line_2);
}


inputfile3.close();

//calulations stored in variables 

float avgRecRemove = (float) recursiveRemove/successRemoves;
float fiveA = numberNodes - a_tree.getNodes();

cout << "5a: " << fiveA << endl;
cout << "5b: " << avgRecRemove << endl; 

//calulations stored in variables 
numberNodes = a_tree.getNodes();
avgDepth = (float) a_tree.getLength() / numberNodes;
ratio = (float) avgDepth / log2(numberNodes);

cout << "6a: " << numberNodes << endl;
cout << "6b: " << avgDepth << endl;
cout << "6c: " << ratio << endl;


}

}  // namespace

int
main(int argc, char **argv) {
  if (argc != 3) {
    cout << "Usage: " << argv[0] << " <databasefilename> <queryfilename>" << endl;
    return 0;
  }
  const string dbx_filename(argv[1]);
  const string seq_filename(argv[2]);
  cout << "Input file is " << dbx_filename << ", and sequences file is " << seq_filename << endl;
  // Note that you will replace the type AvlTree<int> with AvlTree<SequenceMap>
  AvlTree<SequenceMap> a_tree;
  TestTree(dbx_filename, seq_filename, a_tree);

  return 0;
}
