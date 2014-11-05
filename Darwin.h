#include <string>
#include <vector>
#include <iostream>


class Species{
private:
  std::string _name;
  char first;
  std::vector<std::pair<int,int>> instructions;
public:
	Species(std::string name);
	std::vector<std::pair<int,int>> get_instructions() const;
	void addInstruction(std::pair<int,int> in);
	char getName() const;

};
class Creature{
private:
  int _x;
  int _y;
  int _d;   //direction
  int _pc;
  int _max;
  std::vector<std::pair<int,int>> instructions;
  char name;
  Creature();
public:
	Creature(const Species &sp, int d);
	Creature(const Species &sp, int x, int y, int d);
	std::pair<int,int> action();
	char getName() const;
};
class Darwin{
private:
  Darwin();
  int turn;
  int _x;
  int _y;
  std::vector<std::vector<Creature*>> grid;
public:
	Darwin(int x, int y);
	void nextTurn();
	void print();
	void addCreature(Creature c, int x, int y);
};
