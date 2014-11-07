#include <string>
#include <vector>
#include <iostream>
#include <cstdlib>
#include <cassert>
#include "Darwin.h"

////////////Species///////////////
using namespace std;
Species::Species(std::string name){
  assert (name.size()>0);
  _name = name;
  first = name[0];
}

//return this species' instruction set
std::vector<std::pair<int,int>>& Species::get_instructions() {
  return instructions;
}

//Adds instruction to set
void Species::addInstruction(std::pair<int,int> in){
  using namespace std;
  instructions.push_back(in);
}

//return first letter of species name
char Species::getName() const{
  return first;
}

////////////Creature///////////////

Creature::Creature(Species sp) : _turn(0), _pc(0), instructions(sp.get_instructions()){
  using namespace std;
  name = sp.getName();
}

//Initializes Creature with position and direction
void Creature::init(int x, int y, dir d){
  assert(x>=0);
  assert(y>=0);
  assert(d>=0&&d<=3);
  _x = x;
  _y = y;
  _d = d;

}

//Action Harness for each turn
void Creature::action(std::vector<std::vector<Creature*>> &grid, int turn){
  using namespace std;
  if(turn!=_turn)
    return;
  bool repeat = true;

  while(repeat){
    std::pair<int,int> cur = instructions[_pc];
    switch(cur.first){
      case 0:
        hop(grid);
        repeat = false;
        break;
      case 1:
        left();
        repeat = false;
        break;
      case 2:
        right();
        repeat = false;
        break;
      case 3:
        infect(grid);
        repeat = false;
        break;
      case 4:
        repeat = if_empty(grid,cur.second);
        break;
      case 5:
        repeat = if_wall(grid,cur.second);
        break;
      case 6:
        repeat = if_random(cur.second);
        break;
      case 7:
        repeat = if_enemy(grid, cur.second);
        break;
      case 8:
        repeat = go(cur.second);
        break;
    }
  }
  ++_pc;
  ++_turn;
  
}

//Returns one letter name of Creature
char Creature::getName() const{
  return name;
}

//Returns whether the creature is of a different species
bool Creature::is_enemy(Creature& c){
  if(getName()!=c.getName()){
    return true;
  }
  else 
    return false;
}

//moves forward if possible
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

//Turns left
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

//turns right
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

//If there is a different species creature in front
//it is changed to the caller's species and pc is reset
void Creature::infect(std::vector<std::vector<Creature*>> &grid){
    switch (_d){
    case NORTH:
      if(_y!=0&&grid[_y-1][_x]!=0){
        if(is_enemy(*grid[_y-1][_x])){
          grid[_y-1][_x]->instructions = instructions;
          grid[_y-1][_x]->_pc = 0;
          grid[_y-1][_x]->name = getName();
        }
      }
      break;
    case EAST:
      if(_x!=grid[0].size()-1&&grid[_y][_x+1]!=0){
        if(is_enemy(*grid[_y][_x+1])){
          grid[_y][_x+1]->instructions = instructions;
          grid[_y][_x+1]->_pc = 0;
          grid[_y][_x+1]->name = getName();
        }
      }
      break;
    case SOUTH:
      if(_y!=grid.size()-1&&grid[_y+1][_x]!=0){
        if(is_enemy(*grid[_y+1][_x])){
          grid[_y+1][_x]->instructions = instructions;
          grid[_y+1][_x]->_pc = 0;
          grid[_y+1][_x]->name = getName();
        }
      }
      break;
    case WEST:
      if(_x!=0&&grid[_y][_x-1]!=0){
        if(is_enemy(*grid[_y][_x-1])){
          grid[_y][_x-1]->instructions = instructions;
          grid[_y][_x-1]->_pc = 0;
          grid[_y][_x-1]->name = getName();
        }
      }
      break;
  }
}

//checks if the space in front is empty and changes pc if true
bool Creature::if_empty(std::vector<std::vector<Creature*>> &grid, int n){
  assert(n<instructions.size());
  switch (_d){
    case NORTH:
      if(_y!=0&&grid[_y-1][_x]==0){
        _pc = n;
        return true;      }
      break;
    case EAST:
      if(_x!=grid[0].size()-1&&grid[_y][_x+1]==0){
        _pc = n;
        return true;
      }
      break;
    case SOUTH:
      if(_y!=grid.size()-1&&grid[_y+1][_x]==0){
        _pc = n;
        return true;
      }
      break;
    case WEST:
      if(_x!=0&&grid[_y][_x-1]==0){
        _pc = n;
        return true;
      }
      break;
  }
  ++_pc;
  return true;
}

//checks if the space in front is a wall and changes pc if true
bool Creature::if_wall(std::vector<std::vector<Creature*>> &grid, int n){
  assert(n<instructions.size());

  switch (_d){
    case NORTH:
      if(_y==0){
        _pc = n;
        return true;
      }
      break;
    case EAST:
      if(_x==grid[0].size()-1){
        _pc = n;
        return true;
      }
      break;
    case SOUTH:
      if(_y==grid.size()-1){
        _pc = n;
        return true;
      }
      break;
    case WEST:
      if(_x!=0){
        _pc = n;
        return true;
      }
      break;
  }
  ++_pc;
  return true;
}

//50/50 chance to change pc to n
bool Creature::if_random(int n){
  assert(n<instructions.size());
  int r = rand();
  if(r%2 != 0){
    _pc = n;
    return true;
  }
  else{
    ++_pc;
    return true;
  }

}

//checks if space in front is occupied by an enemy and changes pc if true
bool Creature::if_enemy(std::vector<std::vector<Creature*>> &grid, int n){
  assert(n<instructions.size());
  switch (_d){
    case NORTH:
      if(_y!=0&&grid[_y-1][_x]!=0){
        if(is_enemy(*grid[_y-1][_x])){
          _pc = n;
          return true;
        }
      }
      break;
    case EAST:
      if(_x!=grid[0].size()-1&&grid[_y][_x+1]!=0){
        if(is_enemy(*grid[_y][_x+1])){
          _pc = n;
          return true;
        }
      }
      break;
    case SOUTH:
      if(_y!=grid.size()-1&&grid[_y+1][_x]!=0){
        if(is_enemy(*grid[_y+1][_x])){
          _pc = n;
          return true;
        }
      }
      break;
    case WEST:
      if(_x!=0&&grid[_y][_x-1]!=0){
        if(is_enemy(*grid[_y][_x-1])){
          _pc = n;
          return true;
        }
      }
      break;
  }
    ++_pc;
    return true;
}

bool Creature::go(int n){
  using namespace std;
  _pc = n;
  return true;
}


////////////Darwin///////////////

Darwin::Darwin(int x, int y) : _turn(0), _x(x), _y(y){
  assert(x>=0);
  assert(y>=0);
  for(int i = 0; i<y; i++){
    std::vector<Creature*> temp(x,(Creature*)0);
    grid.push_back(temp);
  }
}

//Advances the world
void Darwin::nextTurn(){
  for(int i = 0; i<_y; i++){
    for(int j = 0; j <_x; j++){
      if(grid[i][j]!=0){
        
        grid[i][j]->action(grid, _turn);
      }
    }
  }
  ++_turn;
}

//Prints the status of the world
void Darwin::print(){
  using namespace std;
  cout << "Turn = " << _turn << '.' << endl;
  cout << "  ";
  for(int i = 0; i < _x; i++){
    cout << i%10;
  }
  cout << endl;
  for(int i = 0; i < _y; i++){
    cout << i%10 << ' ';
    for(int j = 0; j < _x; j++){
      Creature* temp = grid[i][j];
      if(temp==0)
        cout << '.';
      else{
        cout << temp->getName();
      }
    }
    cout << endl;
  }
  cout << endl;
}

//Add Creature to the world
void Darwin::addCreature(Creature &c, int x, int y, dir d){
    c.init(x, y, d);
    grid[y][x] = &c;
}


