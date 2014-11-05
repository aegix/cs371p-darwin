#include <string>
#include <vector>
#include <iostream>
#include "Darwin.h"

  Species::Species(std::string name){
    _name = name;
    first = name[0];
  }
  std::vector<std::pair<int,int>> Species::get_instructions() const{
    return instructions;
  }
  void Species::addInstruction(std::pair<int,int> in){
    instructions.push_back(in);
  }
  char Species::getName() const{
    return first;
  }



  Creature::Creature(const Species &sp, int d) : _d(d){
    instructions = sp.get_instructions();
    _max = instructions.size();
    name = sp.getName();
  }

  Creature::Creature(const Species &sp, int x, int y, int d) : _x(x), _y(y), _d(d), _pc(0)
  {

    instructions = sp.get_instructions();
    _max = instructions.size();
    name = sp.getName();

  }

  std::pair<int,int> Creature::action(){
    std::pair<int
    ,int> out = instructions[_pc];
    if(_pc==_max)
      _pc = 0;
    else 
      ++_pc;
    return out;

  }

  char Creature::getName() const{
    return name;
  }


Darwin::Darwin(int x, int y) : turn(0), _x(x), _y(y){
  for(int i = 0; i<y; i++){
    std::vector<Creature*> temp(x,(Creature*)0);
    grid.push_back(temp);
  }
}

void Darwin::nextTurn(){
  ++turn;
}

void Darwin::print(){
  using namespace std;
  cout << "Turn = " << turn << '.' << endl;
  cout << " ";
  for(int i = 0; i < _x; i++){
    cout << i;
  }
  cout << endl;
  for(int i = 0; i < _y; i++){
    cout << i << ' ';
    for(int j = 0; j < _x; j++){
      Creature* temp = grid[i][j];
      if(temp==0)
        cout << '.';
      else
        cout << temp->getName();
    }
    cout << endl;
  }
}

  void Darwin::addCreature(Creature c, int x, int y){
    grid[y][x] = &c;
  }


