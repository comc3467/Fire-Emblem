#include <iostream>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QDebug>
#include <QTimer>

#include "troop.h"
#include "troop_creator.h"
#include "ui_troop_creator.h"

Troop_Creator::Troop_Creator(QWidget *parent) :
    QDialog(parent),
    ui_(new Ui::Troop_Creator)
{
    ui_->setupUi(this);
    this->troopFactory_ = new TroopFactory();
}

Troop_Creator::~Troop_Creator()
{
    delete ui_;
}

/**
  Updates the money for player1 and player2, this is so it can display correctly
  @param int money_1, int money_2
  returns none
*/
void Troop_Creator::setMoney(int money_1, int money_2){
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

/**
  Button to spawn infantry – calls TroopFactory
  @param none
  returns none
*/
void Troop_Creator::on_InfantryButton_clicked()
{
    emit(spawnTroop(troopFactory_->createTroop("infantry",turnPlayer_)));
}

/**
  Button to spawn knight – calls TroopFactory
  @param none
  returns none
*/
void Troop_Creator::on_KnightButton_clicked()
{
    emit(spawnTroop(troopFactory_->createTroop("knight",turnPlayer_))); //this is how the player of the troop is set, passed via varibale, dependent on which castle it's coming from
}

/**
  Button to spawn wizard – calls TroopFactory
  @param none
  returns none
*/
void Troop_Creator::on_WizardButton_clicked()
{
    emit(spawnTroop(troopFactory_->createTroop("wizard",turnPlayer_)));
}

/**
  Button to spawn archer – calls TroopFactory
  @param none
  returns none
*/
void Troop_Creator::on_ArcherButton_clicked()
{
    emit(spawnTroop(troopFactory_->createTroop("archer",turnPlayer_)));
}

/**
  Button to spawn assassin – calls TroopFactory
  @param none
  returns none
*/
void Troop_Creator::on_AssasinButton_clicked()
{
    emit(spawnTroop(troopFactory_->createTroop("assassin",turnPlayer_)));
}

/**
  Button to display infantry stats – calls TroopFactory
  @param none
  returns none
*/
void Troop_Creator::on_InfantryRadio_clicked()
{
    Troop * tempTroop = troopFactory_->createTroop("infantry",turnPlayer_);
    std::string name = "Name: " + tempTroop->get_name() + "" ;
    QString ns(name.c_str());
    ui_->NameLabel->setText(ns);
    std::string health = "Health: " + std::to_string(tempTroop->get_currentHealth()) + "/" + std::to_string(tempTroop->get_maxHealth()) + "" ;
    QString hs(health.c_str());
    ui_->HealthLabel->setText(hs);
    std::string attack = "Attack: " + std::to_string(tempTroop->get_attack()) + "" ;
    QString as(attack.c_str());
    ui_->AttackLabel->setText(as);
    std::string defense = "Defense: " + std::to_string(tempTroop->get_defense()) + "" ;
    QString ds(defense.c_str());
    ui_->DefenseLabel->setText(ds);
    std::string speed = "Speed: " + std::to_string(tempTroop->get_speed()) + "";
    QString ss(speed.c_str());
    ui_->SpeedLabel->setText(ss);
    std::string range = "Range for Attack: " + std::to_string(tempTroop->get_range()) + "";
    QString rs(range.c_str());
    ui_->RangeLabel->setText(rs);
    std::string tiles = "Tiles: " + std::to_string(tempTroop->get_num_tiles()) + "";
    QString ts(tiles.c_str());
    ui_->TileLabel->setText(ts);
}

/**
  Button to display knight stats – calls TroopFactory
  @param none
  returns none
*/
void Troop_Creator::on_KnightRadio_clicked()
{
    Troop * tempTroop = troopFactory_->createTroop("knight",turnPlayer_);
    std::string name = "Name: " + tempTroop->get_name() + "" ;
    QString ns(name.c_str());
    ui_->NameLabel->setText(ns);
    std::string health = "Health: " + std::to_string(tempTroop->get_currentHealth()) + "/" + std::to_string(tempTroop->get_maxHealth()) + "" ;
    QString hs(health.c_str());
    ui_->HealthLabel->setText(hs);
    std::string attack = "Attack: " + std::to_string(tempTroop->get_attack()) + "" ;
    QString as(attack.c_str());
    ui_->AttackLabel->setText(as);
    std::string defense = "Defense: " + std::to_string(tempTroop->get_defense()) + "" ;
    QString ds(defense.c_str());
    ui_->DefenseLabel->setText(ds);
    std::string speed = "Speed: " + std::to_string(tempTroop->get_speed()) + "";
    QString ss(speed.c_str());
    ui_->SpeedLabel->setText(ss);
    std::string range = "Range for Attack: " + std::to_string(tempTroop->get_range()) + "";
    QString rs(range.c_str());
    ui_->RangeLabel->setText(rs);
    std::string tiles = "Tiles: " + std::to_string(tempTroop->get_num_tiles()) + "";
    QString ts(tiles.c_str());
    ui_->TileLabel->setText(ts);
}

/**
  Button to display wizard stats – calls TroopFactory
  @param none
  returns none
*/
void Troop_Creator::on_WizardRadio_clicked()
{
    Troop * tempTroop = troopFactory_->createTroop("wizard",turnPlayer_);
    std::string name = "Name: " + tempTroop->get_name() + "" ;
    QString ns(name.c_str());
    ui_->NameLabel->setText(ns);
    std::string health = "Health: " + std::to_string(tempTroop->get_currentHealth()) + "/" + std::to_string(tempTroop->get_maxHealth()) + "" ;
    QString hs(health.c_str());
    ui_->HealthLabel->setText(hs);
    std::string attack = "Attack: " + std::to_string(tempTroop->get_attack()) + "" ;
    QString as(attack.c_str());
    ui_->AttackLabel->setText(as);
    std::string defense = "Defense: " + std::to_string(tempTroop->get_defense()) + "" ;
    QString ds(defense.c_str());
    ui_->DefenseLabel->setText(ds);
    std::string speed = "Speed: " + std::to_string(tempTroop->get_speed()) + "";
    QString ss(speed.c_str());
    ui_->SpeedLabel->setText(ss);
    std::string range = "Range for Attack: " + std::to_string(tempTroop->get_range()) + "";
    QString rs(range.c_str());
    ui_->RangeLabel->setText(rs);
    std::string tiles = "Tiles: " + std::to_string(tempTroop->get_num_tiles()) + "";
    QString ts(tiles.c_str());
    ui_->TileLabel->setText(ts);
}

/**
  Button to display archer stats – calls TroopFactory
  @param none
  returns none
*/
void Troop_Creator::on_ArcherRadio_clicked()
{
    Troop * tempTroop = troopFactory_->createTroop("archer",turnPlayer_);
    std::string name = "Name: " + tempTroop->get_name() + "" ;
    QString ns(name.c_str());
    ui_->NameLabel->setText(ns);
    std::string health = "Health: " + std::to_string(tempTroop->get_currentHealth()) + "/" + std::to_string(tempTroop->get_maxHealth()) + "" ;
    QString hs(health.c_str());
    ui_->HealthLabel->setText(hs);
    std::string attack = "Attack: " + std::to_string(tempTroop->get_attack()) + "" ;
    QString as(attack.c_str());
    ui_->AttackLabel->setText(as);
    std::string defense = "Defense: " + std::to_string(tempTroop->get_defense()) + "" ;
    QString ds(defense.c_str());
    ui_->DefenseLabel->setText(ds);
    std::string speed = "Speed: " + std::to_string(tempTroop->get_speed()) + "";
    QString ss(speed.c_str());
    ui_->SpeedLabel->setText(ss);
    std::string range = "Range for Attack: " + std::to_string(tempTroop->get_range()) + "";
    QString rs(range.c_str());
    ui_->RangeLabel->setText(rs);
    std::string tiles = "Tiles: " + std::to_string(tempTroop->get_num_tiles()) + "";
    QString ts(tiles.c_str());
    ui_->TileLabel->setText(ts);
}

/**
  Button to display assassin stats – calls TroopFactory
  @param none
  returns none
*/
void Troop_Creator::on_AssasinRadio_clicked()
{
    Troop * tempTroop = troopFactory_->createTroop("assassin",turnPlayer_);
    std::string name = "Name: " + tempTroop->get_name() + "" ;
    QString ns(name.c_str());
    ui_->NameLabel->setText(ns);
    std::string health = "Health: " + std::to_string(tempTroop->get_currentHealth()) + "/" + std::to_string(tempTroop->get_maxHealth()) + "" ;
    QString hs(health.c_str());
    ui_->HealthLabel->setText(hs);
    std::string attack = "Attack: " + std::to_string(tempTroop->get_attack()) + "" ;
    QString as(attack.c_str());
    ui_->AttackLabel->setText(as);
    std::string defense = "Defense: " + std::to_string(tempTroop->get_defense()) + "" ;
    QString ds(defense.c_str());
    ui_->DefenseLabel->setText(ds);
    std::string speed = "Speed: " + std::to_string(tempTroop->get_speed()) + "";
    QString ss(speed.c_str());
    ui_->SpeedLabel->setText(ss);
    std::string range = "Range for Attack: " + std::to_string(tempTroop->get_range()) + "";
    QString rs(range.c_str());
    ui_->RangeLabel->setText(rs);
    std::string tiles = "Tiles: " + std::to_string(tempTroop->get_num_tiles()) + "";
    QString ts(tiles.c_str());
    ui_->TileLabel->setText(ts);
}

/**
  Button to close the troop creator window
  @param none
  returns none
*/
void Troop_Creator::on_closeButton_clicked()
{
    this->hide();
}

