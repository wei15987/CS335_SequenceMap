/*******************************************************************************
  Title          : SequenceMap.h
  Author         : Wei Lian
  Created on     : March 7, 2018
  Description    : Implementation to the SequenceMap class with interface
  Purpose        : 
  Usage          : 
  Build with     : 
  Modifications  : 

*******************************************************************************/
#ifndef _SEQUENCE_MAP_H
#define _SEQUENCE_MAP_H

#include <iostream>
#include <vector>

using namespace std;

class SequenceMap
{
public:
	//constructor with two strings as parameters
	SequenceMap(const string &a_rec_seq, const string &an_enz_acro)
	{
		recognition_sequence_=a_rec_seq;
		enzyme_acronyms_.push_back(an_enz_acro);
	}
	//overload < operator
	bool operator<(const SequenceMap &rhs) const
	{
		if(recognition_sequence_ < rhs.recognition_sequence_)
		{
			return true;
		}
		return false;
	}
	//overload output stream
	friend ostream &operator <<(ostream &out,const SequenceMap &a_Sequencemap)
	{
		//out<<a_Sequencemap.recognition_sequence_<<endl;
		for(size_t i=0;i<a_Sequencemap.enzyme_acronyms_.size();i++)
		{
			out<<a_Sequencemap.enzyme_acronyms_[i]<<" ";
		}
		return out;
	}
	//merge function that merge two sequencemap
	void Merge(const SequenceMap &other_sequence)
	{
		enzyme_acronyms_.insert(enzyme_acronyms_.end(),other_sequence.enzyme_acronyms_.begin(),other_sequence.enzyme_acronyms_.end());
	}





private:
	string recognition_sequence_;
	vector<string> enzyme_acronyms_;


};
#endif //_SEQUENCE_MAP_H