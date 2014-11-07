#include "gtest/gtest.h"
#include "Darwin.h"
#include <sstream>
#include <utility>
#include <cassert>   // assert
#include <cstdlib>   // rand, srand
#include <iostream>  // cout, endl
#include <stdexcept> // invalid_argument, out_of_range

using namespace std;

TEST(Species, Construct1){

  Species t("food");
  ASSERT_EQ('f', t.getName());
}

TEST(Species, Construct2){

  Species t("test");
  ASSERT_EQ('t', t.getName());
}

TEST(Species, Construct3){

  Species t(" ");
  ASSERT_EQ(' ', t.getName());
}

TEST(Species, AddInstruction1){
  Species s("test");
  s.addInstruction(pair<int,int>(0,0));
}

TEST(Species, AddInstruction2){
  Species s("test");
  s.addInstruction(pair<int,int>(8,0));
  s.addInstruction(pair<int,int>(8,0));
  s.addInstruction(pair<int,int>(8,0));
}

TEST(Species, AddInstruction3){
  Species s("test");
  s.addInstruction(pair<int,int>(8,0));
  s.addInstruction(pair<int,int>(8,0));
  s.addInstruction(pair<int,int>(8,0));
  s.addInstruction(pair<int,int>(7,3));
  s.addInstruction(pair<int,int>(8,0));
  s.addInstruction(pair<int,int>(8,0));
  s.addInstruction(pair<int,int>(8,0));
}

TEST(Species, GetInstruction1){
  Species s("test");
  s.addInstruction(pair<int,int>(0,0));
  pair<int,int> p(0,0);
  ASSERT_EQ(s.get_instructions()[0],p);
}

TEST(Species, GetInstruction2){
  Species s("test");
  s.addInstruction(pair<int,int>(8,0));
  s.addInstruction(pair<int,int>(8,0));
  s.addInstruction(pair<int,int>(8,0));
  pair<int,int> p(8,0);
  ASSERT_EQ(s.get_instructions()[0],p);
}

TEST(Creature, Construct1){

  Species s("test");
  s.addInstruction(pair<int,int>(8,0));
  s.addInstruction(pair<int,int>(8,0));
  s.addInstruction(pair<int,int>(8,0));
  s.addInstruction(pair<int,int>(7,3));
  s.addInstruction(pair<int,int>(8,0));
  s.addInstruction(pair<int,int>(8,0));
  s.addInstruction(pair<int,int>(8,0));
  Creature x(s);
  ASSERT_EQ('t', x.getName());

}

TEST(Creature, Construct2){

  Species s("fest");
  s.addInstruction(pair<int,int>(0,0));
  s.addInstruction(pair<int,int>(8,0));
  Creature x(s);
  ASSERT_EQ('f', x.getName());

}

TEST(Creature, Construct3){

  Species t(" ");
  pair<int,int> j(7,3);
  t.addInstruction(j);
  j = pair<int,int>(1,0);
  t.addInstruction(j);
  j = pair<int,int>(8,0);
  t.addInstruction(j);
  j = pair<int,int>(3,0);
  t.addInstruction(j);
  j = pair<int,int>(8,0);
  t.addInstruction(j);
  Creature x(t);
  ASSERT_EQ(' ', x.getName());

}

TEST(Creature, Init1){

  Species t("trap");
  pair<int,int> j(7,3);
  t.addInstruction(j);
  j = pair<int,int>(1,0);
  t.addInstruction(j);
  j = pair<int,int>(8,0);
  t.addInstruction(j);
  j = pair<int,int>(3,0);
  t.addInstruction(j);
  j = pair<int,int>(8,0);
  t.addInstruction(j);
  Creature x(t);
  x.init(0,0,(dir)0);

}

TEST(Creature, Init2){

  Species s("test");
  s.addInstruction(pair<int,int>(8,0));
  s.addInstruction(pair<int,int>(8,0));
  s.addInstruction(pair<int,int>(8,0));
  s.addInstruction(pair<int,int>(7,3));
  s.addInstruction(pair<int,int>(8,0));
  s.addInstruction(pair<int,int>(8,0));
  s.addInstruction(pair<int,int>(8,0));
  Creature x(s);
  x.init(4,5,(dir)2);
}

TEST(Creature, Init3){

  Species s("test");
  s.addInstruction(pair<int,int>(0,0));
  s.addInstruction(pair<int,int>(8,0));
  Creature x(s);
  x.init(1,2,(dir)3);

}

TEST(Darwin, Construct1){

  Darwin x(2,2);

}

TEST(Darwin, Construct2){

  Darwin x(9,9);

}

TEST(Darwin, Construct3){

  Darwin x(100,200);

}

TEST(Darwin, AddCreature1){

  Species s("test");
  s.addInstruction(pair<int,int>(0,0));
  s.addInstruction(pair<int,int>(8,0));
  Creature x(s);
  Darwin d(9,9);
  d.addCreature(x, 2, 2, NORTH);

}

TEST(Darwin, AddCreature2){

  Species s("test");
  s.addInstruction(pair<int,int>(0,0));
  s.addInstruction(pair<int,int>(8,0));
  Creature x(s);
  Creature y(s);
  Darwin d(9,9);
  d.addCreature(x, 2, 2, NORTH);
  d.addCreature(y, 2, 4, SOUTH);

}

TEST(Darwin, AddCreature3){

  Species t("trap");
  pair<int,int> j(7,3);
  t.addInstruction(j);
  j = pair<int,int>(1,0);
  t.addInstruction(j);
  j = pair<int,int>(8,0);
  t.addInstruction(j);
  j = pair<int,int>(3,0);
  t.addInstruction(j);
  j = pair<int,int>(8,0);
  t.addInstruction(j);
  Creature x(t);
  Creature y(t);
  Species s2("test");
  s2.addInstruction(pair<int,int>(0,0));
  s2.addInstruction(pair<int,int>(8,0));
  Creature z(s2);
  Darwin d(9,9);
  d.addCreature(x, 2, 2, NORTH);
  d.addCreature(y, 2, 4, SOUTH);
  d.addCreature(z, 4, 2, WEST);

}

TEST(Darwin, advanceTurn1){

  Species s("test");
  s.addInstruction(pair<int,int>(0,0));
  s.addInstruction(pair<int,int>(8,0));
  Creature x(s);
  Darwin d(9,9);
  d.addCreature(x, 2, 2, NORTH);
  d.nextTurn();

}

TEST(Darwin, advanceTurn2){

  Species s("test");
  s.addInstruction(pair<int,int>(0,0));
  s.addInstruction(pair<int,int>(8,0));
  Creature x(s);
  Creature y(s);
  Darwin d(9,9);
  d.addCreature(x, 2, 2, NORTH);
  d.addCreature(y, 2, 4, SOUTH);
  d.nextTurn();

}

TEST(Darwin, advanceTurn3){

  Species t("trap");
  pair<int,int> j(7,3);
  t.addInstruction(j);
  j = pair<int,int>(1,0);
  t.addInstruction(j);
  j = pair<int,int>(8,0);
  t.addInstruction(j);
  j = pair<int,int>(3,0);
  t.addInstruction(j);
  j = pair<int,int>(8,0);
  t.addInstruction(j);
  Creature x(t);
  Creature y(t);
  Species s2("test");
  s2.addInstruction(pair<int,int>(0,0));
  s2.addInstruction(pair<int,int>(8,0));
  Creature z(s2);
  Darwin d(9,9);
  d.addCreature(x, 2, 2, NORTH);
  d.addCreature(y, 2, 4, SOUTH);
  d.addCreature(z, 4, 2, WEST);
  d.nextTurn();

}

TEST(Darwin, actions){

  Species s2("test");
  s2.addInstruction(pair<int,int>(0,0));
  s2.addInstruction(pair<int,int>(1,0));
  s2.addInstruction(pair<int,int>(2,0));
  s2.addInstruction(pair<int,int>(3,0));
  s2.addInstruction(pair<int,int>(4,5));
  s2.addInstruction(pair<int,int>(5,6));
  s2.addInstruction(pair<int,int>(6,7));
  s2.addInstruction(pair<int,int>(7,8));
  s2.addInstruction(pair<int,int>(8,0));
  Creature x(s2);
  Creature y(s2);
  Creature z(s2);
  Creature w(s2);
  Darwin d(9,9);
  d.addCreature(z, 0, 0, SOUTH);
  d.addCreature(x, 4, 2, WEST);
  d.addCreature(y, 2, 2, EAST);
  d.addCreature(w, 7, 7, NORTH);
  d.nextTurn();
  d.nextTurn();
  d.nextTurn();
  d.nextTurn();
  d.nextTurn();
  d.nextTurn();
  d.nextTurn();
  d.nextTurn();
  d.nextTurn();
  d.nextTurn();
  d.nextTurn();
  d.nextTurn();

}


