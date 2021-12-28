#ifndef TROOP_CREATOR_H
#define TROOP_CREATOR_H

#include "troop.h"
#include "troopfactory.h"
#include <QDialog>

namespace Ui {
class Troop_Creator;
}

class Troop_Creator : public QDialog
{
    Q_OBJECT

public:
    explicit Troop_Creator(QWidget *parent = nullptr);
    ~Troop_Creator();
    void setTurnPlayer(int player){turnPlayer_ = player;};
    void setMoney(int money_1, int money_2);

signals:
    void spawnTroop(Troop *troop);

private slots:

    void on_InfantryButton_clicked();

    void on_KnightButton_clicked();

    void on_WizardButton_clicked();

    void on_ArcherButton_clicked();

    void on_InfantryRadio_clicked();

    void on_KnightRadio_clicked();

    void on_WizardRadio_clicked();

    void on_ArcherRadio_clicked();

    void on_AssasinRadio_clicked();

    void on_AssasinButton_clicked();

    void on_closeButton_clicked();

private:
    Ui::Troop_Creator *ui_;
    int turnPlayer_;
    int money_;

    TroopFactory* troopFactory_;


};

#endif // TROOP_CREATOR_H
