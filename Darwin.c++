#include <string>
#include <vector>
#include <iostream>
#include <cstdlib>
#include "Darwin.h"

////////////Species///////////////
using namespace std;
Species::Species(std::string name){
  _name = name;
  first = name[0];
}
std::vector<std::pair<int,int>>& Species::get_instructions() {
  return instructions;
}
void Species::addInstruction(std::pair<int,int> in){
  using namespace std;
  //cout << first << endl;
  //cout << in.first << " " << in.second << endl;
  instructions.push_back(in);
}
char Species::getName() const{
  return first;
}




