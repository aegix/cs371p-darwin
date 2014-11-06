#include <string>
#include <vector>
#include <iostream>

enum dir {NORTH = 0, EAST = 1, SOUTH = 2, WEST = 3};

class Species{
private:
  std::string _name;
  char first;
  std::vector<std::pair<int,int>> instructions;
public:
	Species(std::string name);
	std::vector<std::pair<int,int>>& get_instructions() ;
	void addInstruction(std::pair<int,int> in);
	char getName() const;
};

class Creature{
private:
  bool set;
  int _turn;
  int _x;
  int _y;
  dir _d;   //direction
  int _pc;
  std::vector<std::pair<int,int>> instructions;
  char name;
  Creature();
  void hop(std::vector<std::vector<Creature*>>&);
  void left();
  void right();

public:
  void  print();
	Creature( Species sp);
  void init(int, int, dir);
	char getName() const;

};

class Darwin{
private:
  Darwin();
  int _turn;
  int _x;
  int _y;
  std::vector<std::vector<Creature*>> grid;
public:
	Darwin(int x, int y);
	void addCreature(Creature &c, int x, int y, dir d);
};
