// Shezan Alam

// References: Data Structures and Algorithm Analysis in C++ by Mark A. Weiss 
// References: Sven Dietrich CSCI 335 Slides


//Program parses through given file that has enzyme nodes and recognition sequences
//Creates SequenceMap objects and builds an AVL tree 
//User inputs recognition tree, program prints values associated with recognition sequence 

#include "avl_tree.h"
// You will have to add #include "sequence_map.h"
#include "sequence_map.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;


namespace {

// @dbx_filename: an input filename.
// @a_tree: an input tree of the type TreeType. It is assumed to be
//  empty.
template <typename TreeType>
void QueryTree(const string &dbx_filename, TreeType &a_tree) {
  // Code for running Part 2.1
  // You can use public functions of TreeType. For example:
  //a_tree.insert(10);
  //a_tree.printTree();
  std::ifstream inputfile{dbx_filename};
  
  string db_line_;
  string input;
  
  // for loop is for reading through header of file/junk
  for(int i = 0; i < 10; ++i) {
    getline(inputfile, db_line_);
  }
  
  // reading file 
  while(getline(inputfile, db_line_)){
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

  //user inputs here the recognition sequence 
  while(getline(cin, input)) {
    SequenceMap userMap(input, {});
    if (a_tree.contains(userMap)) {
      cout << a_tree.find(userMap) << "\n";
    } else {
      cout << "Not Found\n";
    }
  }


   inputfile.close();
}


}  // namespace

int
main(int argc, char **argv) {
  if (argc != 2) {
    cout << "Usage: " << argv[0] << " <databasefilename>" << endl;
    return 0;
  }
  const string dbx_filename(argv[1]);
  cout << "Input filename is " << dbx_filename << endl;
  // Note that you will replace the type AvlTree<int> with AvlTree<SequenceMap>
  AvlTree<SequenceMap> a_tree;
  QueryTree(dbx_filename, a_tree);
  return 0;
}
