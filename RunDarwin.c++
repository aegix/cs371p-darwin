// -----------------------------
// projects/darwin/RunDarwin.c++
// Copyright (C) 2014
// Glenn P. Downing
// -----------------------------

// --------
// includes
// --------

#include <utility>
#include <cassert>   // assert
#include <cstdlib>   // rand, srand
#include <iostream>  // cout, endl
#include <stdexcept> // invalid_argument, out_of_range
#include "Darwin.h"

// ----
// main
// ----

int main () {
    using namespace std;

    // ----
    // food
    // ----

    /*
     0: left
     1: go 0
    */

    Species f("food");
    pair <int,int> i(1,0);
    f.addInstruction(i);
    i = pair<int,int>(8,0);
    f.addInstruction(i);

    // ------
    // hopper
    // ------

    /*
     0: hop
     1: go 0
    */

    Species h("hopper");
    pair <int,int> j(0,0);
    h.addInstruction(j);
    j = pair<int,int>(8,0);
    h.addInstruction(j);

    // -----
    // rover
    // -----

    /*
     0: if_enemy 9
     1: if_empty 7
     2: if_random 5
     3: left
     4: go 0
     5: right
     6: go 0
     7: hop
     8: go 0
     9: infect
    10: go 0
    */

    Species r("rover");
    j = pair<int,int>(7,9);
    r.addInstruction(j);
    j = pair<int,int>(4,7);
    r.addInstruction(j);
    j = pair<int,int>(6,5);
    r.addInstruction(j);
    j = pair<int,int>(1,0);
    r.addInstruction(j);
    j = pair<int,int>(8,0);
    r.addInstruction(j);
    j = pair<int,int>(2,0);
    r.addInstruction(j);
    j = pair<int,int>(8,0);
    r.addInstruction(j);
    j = pair<int,int>(0,0);
    r.addInstruction(j);
    j = pair<int,int>(8,0);
    r.addInstruction(j);
    j = pair<int,int>(3,0);
    r.addInstruction(j);
    j = pair<int,int>(8,0);
    r.addInstruction(j);


    // ----
    // trap
    // ----

    /*
     0: if_enemy 3
     1: left
     2: go 0
     3: infect
     4: go 0
    */

     Species t("trap");
     j = pair<int,int>(7,3);
     t.addInstruction(j);
     j = pair<int,int>(1,0);
     t.addInstruction(j);
     j = pair<int,int>(8,0);
     t.addInstruction(j);
     j = pair<int,int>(3,0);
     t.addInstruction(j);
     j = pair<int,int>(8,0);
     t.addInstruction(j);

    // ----------
    // darwin 8x8
    // ----------
    {
    Darwin x(8,8);

    cout << "*** Darwin 8x8 ***" << endl;

    Creature f1(f);
    Creature f2(f);
    Creature h1(h);
    Creature h2(h);
    Creature h3(h);
    Creature h4(h);

    x.addCreature(f1, 0,0,EAST);
    x.addCreature(f2, 7,7,WEST);
    x.addCreature(h1, 3, 3, NORTH);
    x.addCreature(h2, 4, 3, EAST);
    x.addCreature(h3, 4, 4, SOUTH);
    x.addCreature(h4, 3, 4, WEST);
    x.print();
    x.nextTurn();
    x.print();
    x.nextTurn();
    x.print();
    x.nextTurn();
    x.print();
    x.nextTurn();
    x.print();
    x.nextTurn();
    x.print();
    }
    /*
    8x8 Darwin
    Food,   facing east,  at (0, 0)
    Hopper, facing north, at (3, 3)
    Hopper, facing east,  at (3, 4)
    Hopper, facing south, at (4, 4)
    Hopper, facing west,  at (4, 3)
    Food,   facing north, at (7, 7)
    Simulate 5 moves.
    Print every grid.
    */

    // ----------
    // darwin 7x9
    // ----------
    {
    Darwin x(9,7);
    cout << "*** Darwin 7x9 ***" << endl;
    srand(0);

    Creature t1(t);
    Creature h1(h);
    Creature r1(r);
    Creature t2(t);

    x.addCreature(t1, 0,0,SOUTH);
    x.addCreature(h1, 2,3,EAST);
    x.addCreature(r1, 4, 5, NORTH);
    x.addCreature(t2, 8, 6, WEST);
    x.print();
    x.nextTurn();
    x.print();
    x.nextTurn();
    x.print();
    x.nextTurn();
    x.print();
    x.nextTurn();
    x.print();
    x.nextTurn();
    x.print();
    }
    /*
    7x9 Darwin
    Trap,   facing south, at (0, 0)
    Hopper, facing east,  at (3, 2)
    Rover,  facing north, at (5, 4)
    Trap,   facing west,  at (6, 8)
    Simulate 5 moves.
    Print every grid.
    */
    
    // ------------
    // darwin 72x72
    // without best
    // ------------
    {
    Darwin x(72,72);
    cout << "*** Darwin 72x72 without Best ***" << endl;
    srand(0);

    

    /*
    Randomly place the following creatures facing randomly.
    Call rand(), mod it with 5184 (72x72), and use that for the position
    in a row-major order grid.
    Call rand() again, mod it with 4 and use that for it's direction with
    the ordering: west, north, east, south.
    Do that for each kind of creature.
    10 Food
    10 Hopper
    10 Rover
    10 Trap
    Simulate 1000 moves.
    Print the first 10 grids          (i.e. 0, 1, 2...9).
    Print every 100th grid after that (i.e. 100, 200, 300...1000).
    */

    // ------------
    // darwin 72x72
    // with best
    // ------------
    }
    cout << "*** Darwin 72x72 with Best ***" << endl;
    srand(0);
    /*
    Randomly place the following creatures facing randomly.
    Call rand(), mod it with 5184 (72x72), and use that for the position
    in a row-major order grid.
    Call rand() again, mod it with 4 and use that for it's direction with
    the ordering: 0:west, 1:north, 2:east, 3:south.
    Do that for each kind of creature.
    10 Food
    10 Hopper
    10 Rover
    10 Trap
    10 Best
    Simulate 1000 moves.
    Best MUST outnumber ALL other species for the bonus pts.
    Print the first 10 grids          (i.e. 0, 1, 2...9).
    Print every 100th grid after that (i.e. 100, 200, 300...1000).
    */

    return 0;}
