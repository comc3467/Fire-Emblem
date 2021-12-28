#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <troop_creator.h>
#include <queue>
#include "board.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void UpdatePlayerSideBar(Rectangle * rectangle);
    void UpdateOpponentSideBar(Rectangle * rectangle);

private slots:
    void on_pushButton_clicked();
    void CastleClick(int player);
    void TroopClick(Rectangle * rectangle);
    void MoveClick(Rectangle * rectangle);
    void AttackBuildingClick(Rectangle * rectangle);
    void spawnTroop(Troop *troop);
    //void SpawnClick(Rectangle* space, Troop* troop);

    void Announce(std::string message);
    void AnnounceStats();

    void on_attackButton_clicked();

    void on_turnButton_clicked();

    void on_movingHold_pressed();

    void on_movingHold_released();

    void on_attackingHold_pressed();

    void on_attackingHold_released();

    void on_gameButton_clicked();

    void on_duelButton_clicked();

    void on_itemButton_clicked();

private:
    Ui::MainWindow *ui_;
    QGraphicsScene *scene_;

    Troop_Creator *troopWindow_;

    Board * game_;

    bool spawning_ = false;

    Rectangle* current_; //this is either mover, attacker, or item user

    Rectangle* defender_; //when there is an attack we want to be keeping track of this dude

    std::queue<QString> updates_;

    int turn_; //starts at 1

    int money_1_;
    int money_2_;

};
#endif // MAINWINDOW_H