/*******************************************************************************
  Title          : query_tree.cc
  Author         : Wei Lian
  Created on     : March 7, 2018
  Description    : main file for part2 a
  Purpose        : 
  Usage          : 
  Build with     : 
  Modifications  : 

*******************************************************************************/
// <Wei Lian>
// Main file for Part2(a) of Homework 2.

#include "AvlTree.h"
#include "BinarySearchTree.h"
#include "SequenceMap.h"

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
using namespace std;

namespace {
//the function get the enzyme acronym with the string 
string GetEnzymeAcronym(string & line)
{
  size_t pos=0;
  pos=line.find('/');
  if(pos>0&&pos<100)
  {
    string EnzymeAcronym=line.substr(0,pos);
    ++pos;
    line=line.substr(pos,line.length());
    return EnzymeAcronym;
  }
  else
    return line;
}
//the function keeps getting the regocnition sequence
bool GetNextRegocnitionSequence(string &db_line, string &a_rego_seq) 
{
  if(db_line=="/"&& db_line.length()<2)
  {
    //cout<<db_line<<endl;
    return true;
  }
  else
  {
    size_t pos=0;
    pos=db_line.find('/');
    if(pos>0&&pos<100)
    {
      a_rego_seq=db_line.substr(0,pos);
      ++pos;
      db_line=db_line.substr(pos,db_line.length());
      return false;
    }
    else
      return true;
  }


}
// @db_filename: an input filename.
// @a_tree: an input tree of the type TreeType. It is assumed to be
//  empty.
template <typename TreeType>
void QueryTree(const string &db_filename, TreeType &a_tree) {
  // Code for running Part2(a)
  string db_line;
  ifstream file(db_filename);
  //int num_=0;
  if(!file.is_open())
  {
    cerr<<db_filename<<" "<<"can not be open "<<endl;
  }
  else
  {
    while(!file.eof())
    {
      //read the file line by line
      getline(file,db_line);
      if(!db_line.empty()&&db_line!=" ")
      {
        //get the first part
        string an_enz_acro=GetEnzymeAcronym(db_line);
        string a_reco_seq;
        //keep getting the second part
        while(GetNextRegocnitionSequence(db_line,a_reco_seq)!=true)
        {
          SequenceMap new_sequence_map(a_reco_seq, an_enz_acro);
          a_tree.insert(new_sequence_map);
          //num_++;
        }
      }
    }
    //cout<<num_<<endl;
    file.close();
  }


  // You can use public functions of TreeType. For example:
  //a_tree.insert(10);
  //a_tree.printTree();

  //ask users to provide three strings as inputs
  string str,str1,str2;
  cout<<"please enter three strings: "<<endl;
  cin>>str>>str1>>str2;
  //create three new sequence map with provided input as data
  SequenceMap temp(str,"null");
  SequenceMap temp1(str1,"null");
  SequenceMap temp2(str2,"null");
  //to check if these datas as existed in the tree
  a_tree.contains(temp);
  a_tree.contains(temp1);
  a_tree.contains(temp2);

}

} // namespace



int
main(int argc, char **argv) {
  if (argc != 3) {
    cout << "Usage: " << argv[0] << " <databasefilename> <tree-type>" << endl;
    return 0;
  }
  const string db_filename(argv[1]);
  const string param_tree(argv[2]);
  cout << "Input filename is " << db_filename << endl;
  cout << "Type of tree is " << param_tree << endl;
  if (param_tree == "BST") {
    // Note that you will replace BinarySearchTree<int> with BinarySearchTree<SequenceMap>
    BinarySearchTree<SequenceMap> a_tree;
    QueryTree(db_filename, a_tree);
  } else if (param_tree == "AVL") {
    // Note that you will replace AvlTree<int> with AvlTree<SequenceMap>
    AvlTree<SequenceMap> a_tree;
    QueryTree(db_filename, a_tree);
  } else {
    cout << "Uknown tree type " << param_tree << " (User should provide BST, or AVL)" << endl;
  }
  return 0;
}
