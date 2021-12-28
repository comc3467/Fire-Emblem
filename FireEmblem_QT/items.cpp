#include "items.h"
#include "ui_items.h"

#include <iostream>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QDebug>
#include <QTimer>

Items::Items(QWidget *parent) :
    QDialog(parent),
    ui_(new Ui::Items)
{
    ui_->setupUi(this);
}

Items::~Items()
{
    delete ui_;
}

void Items::setMoney(int money_1, int money_2){
    if(turnPlayer_ == 1){
        this->money_ = money_1;
    }
    else{
        this->money_ = money_2;
    }
    std::string money = std::to_string(this->money_);
    QString m(money.c_str());
    this->ui_->MoneyLabel->setText(m);
} //always called after player has been set

void Items::on_rollButton_clicked()
{
    int item = 0;
    int rng = rand() % 100 + 1;

    int count = 0;
    if (rng == 1){
        item = 3;
        qDebug() << "money";
        if (turnPlayer_ == 1){
            items_1_.insert(items_1_.end(), 1);

            std::vector<int>::iterator it;
            int ser = 3;

            it = std::find (items_1_.begin(), items_1_.end(), ser);
            if (it != items_1_.end())
            {
                count ++;
            }
        }
        else{
            items_2_.insert(items_2_.end(), 1);
            std::vector<int>::iterator it;
            int ser = 3;

            it = std::find (items_2_.begin(), items_2_.end(), ser);
            if (it != items_2_.end())
            {
                count ++;
            }
        }
        std::string quantity = std::to_string(count)  ;
        QString q(quantity.c_str());
        ui_->JackpotLabel->setText(q);
    }
    else if (rng < 30){
        item = 2;
        qDebug() << "ballista";
        if (turnPlayer_ == 1){
            items_1_.insert(items_1_.end(), 1);

            std::vector<int>::iterator it;
            int ser = 2;

            it = std::find (items_1_.begin(), items_1_.end(), ser);
            if (it != items_1_.end())
            {
                count ++;
            }
        }
        else{
            items_2_.insert(items_2_.end(), 1);
            std::vector<int>::iterator it;
            int ser = 2;

            it = std::find (items_2_.begin(), items_2_.end(), ser);
            if (it != items_2_.end())
            {
                count ++;
            }
        }
        std::string quantity = std::to_string(count)  ;
        QString q(quantity.c_str());
        ui_->BallistaLabel->setText(q);
    }
    else{
        item = 1;
        qDebug() << "heal";
        if (turnPlayer_ == 1){
            items_1_.insert(items_1_.end(), 1);

            std::vector<int>::iterator it;
            int ser = 1;

            it = std::find (items_1_.begin(), items_1_.end(), ser);
            if (it != items_1_.end())
            {
                count ++;
            }
        }
        else{
            items_2_.insert(items_2_.end(), 1);
            std::vector<int>::iterator it;
            int ser = 1;

            it = std::find (items_2_.begin(), items_2_.end(), ser);
            if (it != items_2_.end())
            {
                count ++;
            }
        }
        std::string quantity = std::to_string(count)  ;
        QString q(quantity.c_str());
        ui_->HealLabel->setText(q);
    }
}


void Items::on_HealButton_clicked()
{
    if (turnPlayer_ == 1){
        std::vector<int>::iterator it;
        int ser = 1;

        it = std::find (items_1_.begin(), items_1_.end(), ser);
        if (it != items_1_.end())
        {
            emit(item(1,turnPlayer_));
            items_1_.erase(it);
        }
    }
    else{
        std::vector<int>::iterator it;
        int ser = 1;

        it = std::find (items_2_.begin(), items_2_.end(), ser);
        if (it != items_2_.end())
        {
            emit(item(1,turnPlayer_));
            items_2_.erase(it);
        }
    }
}


void Items::on_BallistaButton_clicked()
{
    if (turnPlayer_ == 1){
        std::vector<int>::iterator it;
        int ser = 2;

        it = std::find (items_1_.begin(), items_1_.end(), ser);
        if (it != items_1_.end())
        {
            emit(item(2,turnPlayer_));
            items_1_.erase(it);
        }
    }
    else{
        std::vector<int>::iterator it;
        int ser = 2;

        it = std::find (items_2_.begin(), items_2_.end(), ser);
        if (it != items_2_.end())
        {
            emit(item(2,turnPlayer_));
            items_2_.erase(it);
        }
    }
}


void Items::on_JackpotBag_clicked()
{
    if (turnPlayer_ == 1){
        std::vector<int>::iterator it;
        int ser = 3;

        it = std::find (items_1_.begin(), items_1_.end(), ser);
        if (it != items_1_.end())
        {
            emit(item(3,turnPlayer_));
            items_1_.erase(it);
        }
    }
    else{
        std::vector<int>::iterator it;
        int ser = 3;

        it = std::find (items_2_.begin(), items_2_.end(), ser);
        if (it != items_2_.end())
        {
            emit(item(3,turnPlayer_));
            items_2_.erase(it);
        }
    }
}

void Items::on_closeButton_clicked()
{
    this->hide();
}

