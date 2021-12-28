#include <iostream>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QDebug>
#include <QTimer>
#include <vector>
#include <tuple>

#include "mainwindow.h"
#include "ui_mainwindow.h"

/**
  Constructor for MainWindow, the main UI element of this project
  @param: QWdiget *
  returns none
*/
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui_(new Ui::MainWindow)
{
    ui_->setupUi(this);
    troopWindow_ = new Troop_Creator();
    connect(troopWindow_, &Troop_Creator::spawnTroop, this , &MainWindow::spawnTroop );

    QGraphicsView * view = ui_->mainBoard;
    this->game_ = new NormalBoard();

    // scene is a QGraphicsScene pointer field of the PlotWindow class
    // this makes our lives easier by letting us easily access it
    // from other functions in this class.
    scene_ = new QGraphicsScene;
    view->setScene(scene_);
    // make the scene the same size as the view containing it
    view->setSceneRect(0,0,view->frameSize().width(),view->frameSize().height());
//    int rectangle_width = 7;
    for(int x = 0; x < 600; x += 25){ //+= 20 since we're going to iterate 20 each time for the cell width
        std::vector<Rectangle *> temp;
        for(int y = 0; y < 600; y += 25){
            Rectangle * r = new Rectangle(x, y);
            connect(r, &Rectangle::CastleClick, this, &MainWindow::CastleClick);
            connect(r, &Rectangle::TroopClick, this, &MainWindow::TroopClick);
            connect(r, &Rectangle::MoveClick, this, &MainWindow::MoveClick);
            connect(r, &Rectangle::AttackBuildingClick, this, &MainWindow::AttackBuildingClick);
            connect(r, &Rectangle::Announce, this, &MainWindow::Announce);
            connect(r, &Rectangle::AnnounceStats, this, &MainWindow::AnnounceStats);
            // add it to the scene
            temp.push_back(r);
//            game_->board_[y/20].push_back(r); //gives us a much more workable format... indices are from 0 to 19 so it's much easier
            scene_->addItem(r);
        }
        std::reverse(temp.begin(),temp.end());
        this->game_->board_.push_back(temp);
    } //these double for loops populate the playing field originally
//    std::reverse(this->game_->board_.begin(),this->game_->board_.end());
    this->game_->SetUpBoard();

    this->ui_->attackButton->setVisible(false);

    this->current_ = nullptr; //sets current troop to nothing..

    this->turn_ = 1;
    this->money_1_ = 250;
    this->money_2_ = 250;

//    this->ui_->gameStats->isReadOnly(true);

}
MainWindow::~MainWindow()
{
    delete ui_;
}

/**
  Test button
  @param: none
  returns none
*/
void MainWindow::on_pushButton_clicked()
{
    troopWindow_->show();
    qDebug() << "test";
}

/**
  Slot to respond to a troop spawn
  @param: Troop*
  returns none
*/
void MainWindow::spawnTroop(Troop *troop){
//    this->spawning_ = true;
    int cost = 0;
    int player = troop->get_player();
    if(player == 1){
        cost = this->game_->Spawn(troop, player, money_1_); //this returns 0 if no troop actually spawns
        this->money_1_ -= cost;
        qDebug() << this->money_1_;
        this->troopWindow_->setMoney(money_1_, money_2_); //update costs (does nothing if no troop was spawned, because cost was zero
    }
    else{
        qDebug() << money_2_;
        cost = this->game_->Spawn(troop, player, money_2_);
        qDebug() << cost;
        this->money_2_ -= cost;
        this->troopWindow_->setMoney(money_1_, money_2_);
    }
}

/**
  Slot to respond to a castle click
  @param: player
  returns none
*/
void MainWindow::CastleClick(int player){
    if(this->turn_ != player){
        return; //don't do anything, it's not our turn
    }
    troopWindow_->setTurnPlayer(player);
    troopWindow_->setMoney(money_1_, money_2_);
    troopWindow_->show();
//    this->game_->Spawn(tempTroop, player);
}

/**
  Updates the player sidebar stats
  @param: Rectangle*
  returns none
*/
void MainWindow::UpdatePlayerSideBar(Rectangle * rectangle){

    if(rectangle->troop_ == nullptr){
        std::string name = "Name: died in battle" ;
        QString ns(name.c_str());
        ui_->NameLabel->setText(ns);
        return; //we want to return because there's nothing to update from a nullptr
    }
    std::string name = "Name: " + rectangle->troop_->get_name() + "" ;
    QString ns(name.c_str());
    ui_->NameLabel->setText(ns);
    std::string health = "Health: " + std::to_string(rectangle->troop_->get_currentHealth()) + "/" + std::to_string(rectangle->troop_->get_maxHealth()) + "" ;
    QString hs(health.c_str());
    ui_->HealthLabel->setText(hs);
    std::string attack = "Attack: " + std::to_string(rectangle->troop_->get_attack()) + "" ;
    QString as(attack.c_str());
    ui_->AttackLabel->setText(as);
    std::string defense = "Defense: " + std::to_string(rectangle->troop_->get_defense()) + "" ;
    QString ds(defense.c_str());
    ui_->DefenseLabel->setText(ds);
    std::string speed = "Speed: " + std::to_string(rectangle->troop_->get_speed()) + "";
    QString ss(speed.c_str());
    ui_->SpeedLabel->setText(ss);
    std::string player = "Player: " + std::to_string(rectangle->troop_->get_player()) + "" ;
    QString ps(player.c_str());
    ui_->PlayerLabel->setText(ps);

    if(rectangle->troop_->get_item() != ""){
        std::string item = "Item: " + rectangle->troop_->get_item() + "" ;
        QString i(item.c_str());
        ui_->itemLabel->setText(i);
        ui_->itemButton->setVisible(true);
    }
    else{
        std::string item = "Item: No item" ;
        QString i(item.c_str());
        ui_->itemLabel->setText(i);
        ui_->itemButton->setVisible(false);
    }


//    ui_->attackButton->setVisible(true);

    update();
}

/**
  Updates the opponent sidebar stats
  @param: Rectangle*
  returns none
*/
void MainWindow::UpdateOpponentSideBar(Rectangle * rectangle){

    this->defender_ = rectangle;

    if(rectangle->troop_ == nullptr){
        std::string name = "Name: died in battle" ;
        QString ns(name.c_str());
        ui_->NameLabel_2->setText(ns);
        return; //we want to return because there's nothing to update from a nullptr
    }
    std::string name = "Name: " + rectangle->troop_->get_name() + "" ;
    QString ns(name.c_str());
    ui_->NameLabel_2->setText(ns);
    std::string health = "Health: " + std::to_string(rectangle->troop_->get_currentHealth()) + "/" + std::to_string(rectangle->troop_->get_maxHealth()) + "" ;
    QString hs(health.c_str());
    ui_->HealthLabel_2->setText(hs);
    std::string attack = "Attack: " + std::to_string(rectangle->troop_->get_attack()) + "" ;
    QString as(attack.c_str());
    ui_->AttackLabel_2->setText(as);
    std::string defense = "Defense: " + std::to_string(rectangle->troop_->get_defense()) + "" ;
    QString ds(defense.c_str());
    ui_->DefenseLabel_2->setText(ds);
    std::string speed = "Speed: " + std::to_string(rectangle->troop_->get_speed()) + "";
    QString ss(speed.c_str());
    ui_->SpeedLabel_2->setText(ss);
    std::string player = "Player: " + std::to_string(rectangle->troop_->get_player()) + "" ;
    QString ps(player.c_str());
    ui_->PlayerLabel_2->setText(ps);

    update();
}

/**
  Slot that handles what happens when a troop is clicked on, if it needs to be moved, attacked, etc.
  @param: Rectangle*
  returns none
*/
void MainWindow::TroopClick(Rectangle * rectangle){
    ui_->attackButton->setVisible(false); //sets it to false every time we click a new character... this way we know when we click the button there's an attack
    defender_ = nullptr;
    this->game_->RepaintEmpty(rectangle); //refreshes the board, AND repaints the rectangles that are attackable troops but are not being attacked
    if(rectangle->attackable_){
        this->UpdateOpponentSideBar(rectangle);
        ui_->attackButton->setVisible(true);
        return; //this is a special troop click, when we intend to attack the troop we've clicked... not trying to repaint anything
    }

    if(rectangle->troop_->get_player() != turn_){
        return; //don't do anything, it's not our turn yet
    }

    this->UpdatePlayerSideBar(rectangle);

    update();
    if(rectangle->troop_->get_moved() == false){
        std::vector<std::tuple<int, int> > moves = this->game_->GetMoves(rectangle);
        this->game_->PaintMoves(moves);
    }
    if(rectangle->troop_->get_moved() == false){
        std::vector<std::tuple<int, int> > moves = this->game_->GetAttackMoves(rectangle);
        if(moves.size() != 0){ //meaning there's someone we could attack
            this->game_->PaintAttackMoves(moves);
        }
    } //this way, we can paint over the blue stuff in case you want to run away or attack when an enemy is near

    this->current_ = rectangle; //remembers for later (necessary)
}

/**
  Slot that responds to a MoveClick, mvoes the troops...
  @param: Rectangle*
  returns none
*/
void MainWindow::MoveClick(Rectangle * next){
    if(this->current_ != nullptr){
//        this->current_->troop_->moved();
        this->game_->Move(current_,next);
        this->game_->RepaintEmpty();
        this->current_ = next;
    }
    else{
        return; //for some reason current was not set
    }
    if(this->current_->troop_->get_attacked() == false){
        std::vector<std::tuple<int, int> > moves = this->game_->GetAttackMoves(this->current_);
        if(moves.size() != 0){ //meaning there's someone we could attack
            this->game_->PaintAttackMoves(moves);
        }
    } //this way, we can paint over the blue stuff in case you want to run away or attack when an enemy is near

}

/**
  Slot that responds to a AttackBuildingClick, when the building could be attacked like a chest or enemy castle
  @param: Rectangle* defender
  returns none
*/
void MainWindow::AttackBuildingClick(Rectangle * defender){
//    if(this->current_ != nullptr){
//        this->current_->troop_->attacked();
//        this->game_->Attack(current_,defender);
//        this->game_->RepaintEmpty();
//    }
    this->game_->RepaintEmpty();
    this->defender_ = defender;
    ui_->attackButton->setVisible(true);
}

/**
  Slot that responds to a attackbutton clicked, this starts the attack process
  @param: none
  returns none
*/
void MainWindow::on_attackButton_clicked()
{
    ui_->attackButton->setVisible(false);
    this->game_->Attack(this->current_, this->defender_);
//    std::string temp = this->defender_->troop_->get_name();
//    qDebug() << temp[0];
    this->UpdatePlayerSideBar(this->current_);
    this->UpdateOpponentSideBar(this->defender_); //refreshes sidebar

    //we only check the win condition after an attack, so after the function of the attack is totally done we can call within this function

    int temp_win = this->game_->CheckWin();
    if(temp_win != 0){
        this->game_->board_[0][0]->Announce("GAME OVER! PLAYER " + std::to_string(temp_win) + "HAS WON THE GAME");
        this->ui_->turnButton->setDisabled(true);
    }
}

/**
  Slot that appends a message to the game updates panel
  @param: std::string message
  returns none
*/
void MainWindow::Announce(std::string message){
    this->ui_->gameUpdates->clear();
    if(this->updates_.size() >= 7){
        this->updates_.pop(); //takes off the first element of the queue if it's too long
    }
    QString m(message.c_str());
    this->updates_.push(m);
    std::queue<QString> temp_queue = this->updates_;
    while (!temp_queue.empty())
    {
        QString update = temp_queue.front();
        this->ui_->gameUpdates->append(update);
        temp_queue.pop();
    }
}
/**
  Slot that updates the gameStats panel
  @param: none
  returns none
*/
void MainWindow::AnnounceStats(){
    this->ui_->gameStats->clear();

    std::string turn = "Turn: Player " + std::to_string(this->turn_);
    QString t(turn.c_str());
    this->ui_->gameStats->append(t);

    std::string moves = "Troops to move: " + std::to_string(this->game_->GetTroopsToMove());
    QString m(moves.c_str());
    this->ui_->gameStats->append(m);

    std::string attacks = "Troops in position to attack: " + std::to_string(this->game_->GetTroopsToAttack());
    QString a(attacks.c_str());
    this->ui_->gameStats->append(a);

    std::string p1_hp = "Player 1 Castle Health: " + std::to_string(this->game_->getP1Health());
    QString p1(p1_hp.c_str());
    this->ui_->gameStats->append(p1);

    std::string p2_hp = "Player 2 Castle Health: " + std::to_string(this->game_->getP2Health());
    QString p2(p2_hp.c_str());
    this->ui_->gameStats->append(p2);
}

/**
  Slot that responds to the button to advance the turn
  @param: none
  returns none
*/
void MainWindow::on_turnButton_clicked()
{
    this->turn_ = this->game_->AdvanceTurn();
    this->troopWindow_->setTurnPlayer(turn_);
    this->AnnounceStats();
}

/**
  Slot that responds to pressing the show moveable button – shows who can move
  @param: none
  returns none
*/
void MainWindow::on_movingHold_pressed()
{
    this->game_->ShowMoveable();
}

/**
  Slot that responds to releasing the show moveable button – unshows who can move
  @param: none
  returns none
*/
void MainWindow::on_movingHold_released()
{
    this->game_->UnShowMoveable();
}

/**
  Slot that responds to pressing the show attackable button – shows who can attack
  @param: none
  returns none
*/
void MainWindow::on_attackingHold_pressed()
{
    this->game_->ShowAttackable();
}

/**
  Slot that responds to releasing the show attackable button – unshows who can attack
  @param: none
  returns none
*/
void MainWindow::on_attackingHold_released()
{
    this->game_->UnShowAttackable();
}

/**
  Slot that creates a new Normal Game
  @param: none
  returns none
*/
void MainWindow::on_gameButton_clicked()
{
    this->ui_->turnButton->setDisabled(false);
    scene_ = new QGraphicsScene;
    this->game_ = new NormalBoard();
    // scene is a QGraphicsScene pointer field of the PlotWindow class
    // this makes our lives easier by letting us easily access it
    // from other functions in this class.
    QGraphicsView * view = ui_->mainBoard;
    view->setScene(scene_);
    // make the scene the same size as the view containing it
    view->setSceneRect(0,0,view->frameSize().width(),view->frameSize().height());
//    int rectangle_width = 7;
    for(int x = 0; x < 600; x += 25){ //+= 20 since we're going to iterate 20 each time for the cell width
        std::vector<Rectangle *> temp;
        for(int y = 0; y < 600; y += 25){
            Rectangle * r = new Rectangle(x, y);
            connect(r, &Rectangle::CastleClick, this, &MainWindow::CastleClick);
            connect(r, &Rectangle::TroopClick, this, &MainWindow::TroopClick);
            connect(r, &Rectangle::MoveClick, this, &MainWindow::MoveClick);
            connect(r, &Rectangle::AttackBuildingClick, this, &MainWindow::AttackBuildingClick);
            connect(r, &Rectangle::Announce, this, &MainWindow::Announce);
            connect(r, &Rectangle::AnnounceStats, this, &MainWindow::AnnounceStats);
            // add it to the scene
            temp.push_back(r);
//            game_->board_[y/20].push_back(r); //gives us a much more workable format... indices are from 0 to 19 so it's much easier
            scene_->addItem(r);
        }
        std::reverse(temp.begin(),temp.end());
        this->game_->board_.push_back(temp);
    } //these double for loops populate the playing field originally
//    std::reverse(this->game_->board_.begin(),this->game_->board_.end());
    this->game_->SetUpBoard();

    this->ui_->attackButton->setVisible(false);

    this->current_ = nullptr; //sets current troop to nothing..

    this->turn_ = 1;
    this->money_1_ = 250;
    this->money_2_ = 250;

//    this->ui_->gameStats->isReadOnly(true);
}

/**
  Slot that creates a new Duel Game
  @param: none
  returns none
*/
void MainWindow::on_duelButton_clicked()
{
    this->ui_->turnButton->setDisabled(false);
    scene_ = new QGraphicsScene;
    this->game_ = new DuelBoard();
    // scene is a QGraphicsScene pointer field of the PlotWindow class
    // this makes our lives easier by letting us easily access it
    // from other functions in this class.
    QGraphicsView * view = ui_->mainBoard;
    view->setScene(scene_);
    // make the scene the same size as the view containing it
    view->setSceneRect(0,0,view->frameSize().width(),view->frameSize().height());
//    int rectangle_width = 7;
    for(int x = 0; x < 600; x += 25){ //+= 20 since we're going to iterate 20 each time for the cell width
        std::vector<Rectangle *> temp;
        for(int y = 0; y < 600; y += 25){
            Rectangle * r = new Rectangle(x, y);
            connect(r, &Rectangle::CastleClick, this, &MainWindow::CastleClick);
            connect(r, &Rectangle::TroopClick, this, &MainWindow::TroopClick);
            connect(r, &Rectangle::MoveClick, this, &MainWindow::MoveClick);
            connect(r, &Rectangle::AttackBuildingClick, this, &MainWindow::AttackBuildingClick);
            connect(r, &Rectangle::Announce, this, &MainWindow::Announce);
            connect(r, &Rectangle::AnnounceStats, this, &MainWindow::AnnounceStats);
            // add it to the scene
            temp.push_back(r);
//            game_->board_[y/20].push_back(r); //gives us a much more workable format... indices are from 0 to 19 so it's much easier
            scene_->addItem(r);
        }
        std::reverse(temp.begin(),temp.end());
        this->game_->board_.push_back(temp);
    } //these double for loops populate the playing field originally
//    std::reverse(this->game_->board_.begin(),this->game_->board_.end());
    this->game_->SetUpBoard();

    this->ui_->attackButton->setVisible(false);

    this->current_ = nullptr; //sets current troop to nothing..

    this->turn_ = 1;
    this->money_1_ = 250;
    this->money_2_ = 250;

//    this->ui_->gameStats->isReadOnly(true);
}

/**
  Slot that uses the item for a given player
  @param: none
  returns none
*/
void MainWindow::on_itemButton_clicked()
{

    this->current_->troop_->set_currentHealth(10); //refills the health
    this->current_->troop_->set_item(""); //no item
    this->UpdatePlayerSideBar(this->current_);
}
