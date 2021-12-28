#ifndef BOARD_H
#define BOARD_H

#include <QObject>
#include <iostream>
#include<tuple>
#include <vector>
#include "rectangle.h"
#include "troop.h"

class Board : public QObject
{
    Q_OBJECT
public:



    Board();

    std::vector< std::vector<Rectangle *> > board_;

    virtual void SetUpBoard() = 0;

    virtual int CheckWin() = 0;

    int Spawn(Troop * troop, int player, int money); //returns the cost of the troop that's spawning

    std::tuple<int,int> GetCoordinates(Rectangle* rectangle);

    std::vector<std::tuple<int,int>> GetMoves(Rectangle * rectangle);

    std::vector<std::tuple<int,int>> GetAttackMoves(Rectangle * rectangle);

    void RepaintEmpty();

    void RepaintEmpty(Rectangle *rectangle); //overloaded to repaint also those rectangles not BEING ATTACKED, but are attackable as well as repaint empty

    void PaintMoves(std::vector<std::tuple<int,int> > moves);

    void PaintAttackMoves(std::vector<std::tuple<int,int> > attack_moves);

    void Move(Rectangle* previous, Rectangle* next);

    void Attack(Rectangle* attacker, Rectangle* defender);

    void ShowMoveable();

    void UnShowMoveable();

    void ShowAttackable();

    void UnShowAttackable();


    int GetTroopsToMove();

    int GetTroopsToAttack();

    int AdvanceTurn();

    int getP1Health(){ return p1_hp_; }
    int getP2Health(){ return p2_hp_; }

protected:
    int turn_; //either going to be a 1 or a 2, 1 to start off since it's player 1's turn

    int p1_hp_;
    int p2_hp_;

    Building *chest_flyweight_;
};

class NormalBoard: public Board{
public:
    NormalBoard();
    void SetUpBoard();
    int CheckWin();

};

class DuelBoard: public Board{
public:
    DuelBoard();
    void SetUpBoard();
    int CheckWin();
};

/*
std::vector<std::tuple<int,int>> MoveAlgorithm(Rectangle * rectangle,int move, std::vector<std::tuple<int,int>> & moves);
*/

#endif // BOARD_H
