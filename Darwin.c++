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

////////////Creature///////////////

Creature::Creature(Species sp) : _turn(0), _pc(0), instructions(sp.get_instructions()){
  using namespace std;
  name = sp.getName();
  //print();
}

void Creature::init(int x, int y, dir d){

  _x = x;
  _y = y;
  _d = d;

}

char Creature::getName() const{
  return name;
}

void Creature::hop(std::vector<std::vector<Creature*>> &grid){
  switch (_d){
    case NORTH:
      if(_y!=0&&grid[_y-1][_x]==0){
        grid[_y-1][_x]=grid[_y][_x];
        grid[_y][_x] = 0;
        --_y;
      }
      break;
    case EAST:
      if(_x!=grid[0].size()-1&&grid[_y][_x+1]==0){
        grid[_y][_x+1]=grid[_y][_x];
        grid[_y][_x] = 0;
        ++_x;
      }
      break;
    case SOUTH:
      if(_y!=grid.size()-1&&grid[_y+1][_x]==0){
        grid[_y+1][_x]=grid[_y][_x];
        grid[_y][_x] = 0;
        ++_y;
      }
      break;
    case WEST:
      if(_x!=0&&grid[_y][_x-1]==0){
        grid[_y][_x-1]=grid[_y][_x];
        grid[_y][_x] = 0;
        --_x;
      }
      break;
  }
}

void Creature::left(){
  switch(_d){
    case NORTH:
      _d = WEST;
      break;
    case EAST:
      _d = NORTH;
      break;
    case SOUTH:
      _d = EAST;
      break;
    case WEST:
      _d = SOUTH;
      break;
  }
}

void Creature::right(){
  switch(_d){
    case NORTH:
      _d = EAST;
      break;
    case EAST:
      _d = SOUTH;
      break;
    case SOUTH:
      _d = WEST;
      break;
    case WEST:
      _d = NORTH;
      break;
  }
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


