#include <iostream>
#include <vector>
#include <fstream>
#include <map>
#include <string>
#include <sstream>
#include <utility>
#include <algorithm>
using namespace std;

  // C++ template to print vector container elements 
template <typename T> 
ostream& operator<<(ostream& os, const vector<T>& v) 
{ 
	os << "["; 
	for (int i = 0; i < v.size(); ++i) { 
		os << v[i]; 
		if (i != v.size() - 1) 
			os << ", "; 
	} 
	os << "]\n"; 
	return os; 
} 
  

  // C++ template to print map container elements 
template <typename T, typename S> 
ostream& operator<<(ostream& os, const map<T, S>& v) 
{ 
	for (auto it : v)  
		os << it.first << " : " 
		   << it.second << "\n"; 
	  
	return os; 
} 

string upTo(string in, char findVal){
	return in.substr(0, in.find(findVal));
}
string upTo(string in, string findVal){
	return in.substr(0, in.find(findVal));
}

string after(string in, char findVal){
	return in.substr(in.find(findVal)+1);
}
string after(string in, string findVal){
	return in.substr(in.find(findVal)+findVal.size()+1);
}