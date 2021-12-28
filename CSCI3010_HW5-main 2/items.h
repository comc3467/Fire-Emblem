#ifndef ITEMS_H
#define ITEMS_H

#include <QDialog>

namespace Ui {
class Items;
}

class Items : public QDialog
{
    Q_OBJECT

public:
    explicit Items(QWidget *parent = nullptr);
    ~Items();
    void setTurnPlayer(int player){turnPlayer_ = player;};
    void setMoney(int money_1, int money_2);

signals:
    void item(int item,int player);
    void gainItem(int cost,int player);

private slots:

    void on_rollButton_clicked();

    void on_HealButton_clicked();

    void on_BallistaButton_clicked();

    void on_JackpotBag_clicked();

    void on_closeButton_clicked();

private:
    Ui::Items *ui_;
    int turnPlayer_;
    int money_;

    std::vector<int> items_1_;
    std::vector<int> items_2_;
};

#endif // Items_H
