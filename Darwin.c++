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

////////////Darwin///////////////

Darwin::Darwin(int x, int y) : _turn(0), _x(x), _y(y){
  for(int i = 0; i<y; i++){
    std::vector<Creature*> temp(x,(Creature*)0);
    grid.push_back(temp);
  }
}

void Darwin::addCreature(Creature &c, int x, int y, dir d){
    c.init(x, y, d);
    grid[y][x] = &c;
    //cout << endl;
    //c.print();
    //cout << endl;
}


