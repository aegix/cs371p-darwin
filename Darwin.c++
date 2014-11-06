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

void Creature::action(std::vector<std::vector<Creature*>> &grid, int turn){
  //cout << "action" << endl;
  using namespace std;
  //print();
  //cout << turn << _turn << endl;
  if(turn!=_turn)
    return;
  //std::pair<int,int> cur = instructions[_pc];
  //cout << "pc "<<_pc<< endl;
  //cout << cur.first <<" "<<cur.second<< endl;
  bool repeat = true;

  while(repeat){
    std::pair<int,int> cur = instructions[_pc];
    //cout << getName() << " " << cur.first << " " << cur.second << endl;
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
    }
  }
  ++_pc;
  ++_turn;
  
}

void Creature::print(){
  for(int i = 0; i < instructions.size(); i ++){
    cout << instructions[i].first << " "<< instructions[i].second<<endl;
  }
  cout << endl;
}

char Creature::getName() const{
  return name;
}

bool Creature::is_enemy(Creature& c){
  //cout << getName() << " vs " << c.getName()<<endl;
  if(getName()!=c.getName()){
    //cout << "isenemy!" << endl;
    return true;
  }
  else 
    return false;
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

void Darwin::nextTurn(){
  for(int i = 0; i<_y; i++){
    for(int j = 0; j <_x; j++){
      //cout << i << " " << j << endl;
      //cout << grid[i][j] << endl;
      if(grid[i][j]!=0){
        
        grid[i][j]->action(grid, _turn);
      }
    }
  }
  ++_turn;
}

void Darwin::print(){
  using namespace std;
  cout << "Turn = " << _turn << '.' << endl;
  cout << "  ";
  for(int i = 0; i < _x; i++){
    cout << i;
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

void Darwin::addCreature(Creature &c, int x, int y, dir d){
    c.init(x, y, d);
    grid[y][x] = &c;
    //cout << endl;
    //c.print();
    //cout << endl;
}


