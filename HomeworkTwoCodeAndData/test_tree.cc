/*******************************************************************************
  Title          : test_tree.cc
  Author         : Wei Lian
  Created on     : March 7, 2018
  Description    : main file for part2
  Purpose        : 
  Usage          : 
  Build with     : 
  Modifications  : 

*******************************************************************************/
// <Wei Lian>
// Main file for Part2(b) of Homework 2.

#include "AvlTree.h"
#include "BinarySearchTree.h"
#include "SequenceMap.h"

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <cmath>
using namespace std;

namespace {
  //get the first part which is enzymeacronym, line is the data
  //parse the data into different parts, it finds the / to separate two parts
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
//the parser, db_line is the data, and save it to a_rego_seq
//also same as getenzyacronym function, it finds the / and break it into two parts
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
//a calculation function that calculate x/y return float
float GetAverage_depth(float x,float y)
{
  return (x/y);
}

// @db_filename: an input database filename.
// @seq_filename: an input sequences filename.
// @a_tree: an input tree of the type TreeType. It is assumed to be
//  empty.
template <typename TreeType>
void TestTree(const string &db_filename, const string &seq_filename, TreeType &a_tree) {
  // Code for running Part2(b)  
  string db_line,seq_line;
  ifstream file(db_filename);
  //read the file, make sure it is open
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
      //make sure the line is valid
      if(!db_line.empty()&&db_line!=" ")
      {
        //get the first part
        string an_enz_acro=GetEnzymeAcronym(db_line);
        string a_reco_seq;
        //cout<<db_line<<endl;
        //keep getting the second half break it into sequence
        while(GetNextRegocnitionSequence(db_line,a_reco_seq)!=true)
        {
          //create new sequence object save it to the tree
          SequenceMap new_sequence_map(a_reco_seq, an_enz_acro);
          a_tree.insert(new_sequence_map);
        }
      }
    }
    file.close();
  }
  int num;
  //call the get numbers of nodes function assign it to num
  num=a_tree.get_num_nodes();
  cout<<"2: "<<num<<endl;
  //call the caculation function to find the average depth
  float Average_depth=GetAverage_depth(a_tree.get_internal_length(),num);
  cout<<"3a: "<<Average_depth<<endl;
  cout<<"3b: "<<Average_depth/log2(num)<<endl;
  //read the sequence file
  ifstream file1(seq_filename);
  if(!file1.is_open())
  {
    cerr<<seq_filename<<" "<<"can not be open"<<endl;
  }
  else
  {
    while(!file1.eof())
    {
      //read it line by line
      while(getline(file1,seq_line))
      {
        //create new class object with sequence
        SequenceMap new_sequence_map(seq_line, "null");
        //call the find function to see if it exist in the tree or not
        a_tree.find(new_sequence_map);
      }
    }
    file1.close();
  }
  //the function retrun the number of success call of find
  int found=a_tree.find_success();
  //the function return the total number of recursion call
  int total_call=a_tree.find_total();
  //the function return the total number of call
  int find_call=a_tree.find_calla();
  cout<<"4a: "<<found<<endl;
  cout<<"4b: "<<GetAverage_depth(total_call,find_call)<<endl;
  ifstream file2(seq_filename);
  int cter=1;
  if(!file2.is_open())
  {
    cerr<<seq_filename<<" "<<"can not be open"<<endl;
  }
  else
  {
    while(!file2.eof())
    {
      //read file line by line
      while(getline(file2,seq_line))
      {
        //increase the counter by1
        cter++;
        //if the counter can be divided by 2 which is even number, so it reads the line,and skip next,and next
        if(cter%2==0)
        {
          //remove every other sequence
          SequenceMap new_sequence_map(seq_line, "null");
          a_tree.remove(new_sequence_map);
        }
      }
    }
    file2.close();
  }
  //return the successful remove 
  int removed=a_tree.remove_success();
  //return the total of resursive remove call
  int total_remove=a_tree.remove_total();
  //return the total of remove call
  int remove_call=a_tree.remove_calla();
  cout<<"5a: "<<removed<<endl;
  cout<<"5b: "<<GetAverage_depth(total_remove,remove_call)<<endl;
  //get the numbers of nodes
  cout<<"6a: "<<a_tree.get_num_nodes()<<endl;
  //get the average depth of tree
  cout<<"6b: "<<GetAverage_depth(a_tree.get_internal_length(),a_tree.get_num_nodes())<<endl;
  //get the ratio of the tree
  cout<<"6c: "<<GetAverage_depth(a_tree.get_internal_length(),a_tree.get_num_nodes())/log2(a_tree.get_num_nodes())<<endl;
}

}  // namespace

int
main(int argc, char **argv) {
  if (argc != 4) {
    cout << "Usage: " << argv[0] << " <databasefilename> <queryfilename> <tree-type>" << endl;
    return 0;
  }
  const string db_filename(argv[1]);
  const string seq_filename(argv[2]);
  const string param_tree(argv[3]);
  cout << "Input file is " << db_filename << ", and sequences file is " << seq_filename << endl;
  cout << "Type of tree is " << param_tree << endl;
  if (param_tree == "BST") {
    // Note that you will replace BinarySearchTree<int> with BinarySearchTree<SequenceMap>
    BinarySearchTree<SequenceMap> a_tree;
    TestTree(db_filename, seq_filename, a_tree);
  } else if (param_tree == "AVL") {
    // Note that you will replace AvlTree<int> with AvlTree<SequenceMap>
    AvlTree<SequenceMap> a_tree;
    TestTree(db_filename, seq_filename, a_tree);
  } else {
    cout << "Uknown tree type " << param_tree << " (User should provide BST, or AVL)" << endl;
  }
  return 0;
}
