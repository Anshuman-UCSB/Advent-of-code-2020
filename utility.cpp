#include <iostream>
#include <vector>
#include <fstream>
#include <map>
#include <queue>
#include <cmath>
#include <stack>
#include <string>
#include <regex>
#include <numeric>
#include <sstream>
#include <chrono>
#include <set>
#include <utility>
#include <algorithm>
using namespace std;

struct Timer{
    std::chrono::high_resolution_clock::time_point begin, end; 

	Timer():begin(chrono::high_resolution_clock::now()){}
	void start(){
		begin = chrono::high_resolution_clock::now();
	}
	void stop(){
		end  = chrono::high_resolution_clock::now();
		chrono::duration<double> elapsed = end-begin;
		cout << "Elapsed time: " << elapsed.count() << " s\n";
	}
};

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
	os << "]"; 
	return os; 
} 

template <class T>
vector<T> reverseVect(const vector<T>& v){
    return vector<T>(v.rbegin(), v.rend());
}

template <typename T>
bool removeValue(vector<T>& v, T val){
	for(int i = 0;i<v.size();i++){
		if(v[i] == val){
			v.erase(v.begin()+i);
			return true;
		}
	}
	return false;
}

template <typename T>
bool inVect(vector<T>& v, T val){
	for(auto c: v){
		if(c == val){
			return true;
		}
	}
	return false;
}

template <typename T>
int findInd(const vector<T>& v, T val){
	for(int i = 0;i<v.size();i++){
		if(v[i] == val){
			return i;
		}
	}
	return -1;
}

template <typename T>
vector<T> subVector(const vector<T>& v, int l, int h){// vector from [l, h)
	return vector<T>(v.begin()+l, v.begin()+h);
}



vector<string> readFile(string inp){
	fstream file(inp);
	string line;
	vector<string> out;
	while(getline(file, line)){
		if (line.back() == '\r'){
			line.pop_back();
		}
		out.push_back(line);
	}
	return out;
}


  // C++ template to print map container elements 
template <typename T, typename S> 
ostream& operator<<(ostream& os, const map<T, S>& v) 
{ 
	for (auto it : v)  
		os << it.first << " : " 
		   << it.second << endl; 
	  
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