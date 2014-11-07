#include <string>
#include <vector>
#include <iostream>

enum dir {NORTH = 1, EAST = 2, SOUTH = 3, WEST = 0};

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
  void infect(std::vector<std::vector<Creature*>>&);
  bool if_empty(std::vector<std::vector<Creature*>>&, int);
  bool if_wall(std::vector<std::vector<Creature*>>&, int);
  bool if_random(int);
  bool if_enemy(std::vector<std::vector<Creature*>>&, int);
  bool go(int);
  bool is_enemy(Creature&);

public:
	Creature( Species sp);
  void init(int, int, dir);
	void action(std::vector<std::vector<Creature*>>&, int);
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
	void nextTurn();
	void print();
	void addCreature(Creature &c, int x, int y, dir d);
};
