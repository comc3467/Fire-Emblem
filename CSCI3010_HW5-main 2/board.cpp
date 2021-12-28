#include <cmath>
#include "board.h"
#include <tuple>

/**
  Constructors for Board
  @param none
  returns nothing
*/
Board::Board(){
    this->turn_ = 1;
    this->p1_hp_ = 50;
    this->p2_hp_ = 50;

    this->chest_flyweight_ = new Building("chest");
}
DuelBoard::DuelBoard(){
    this->turn_ = 1;
    this->p1_hp_ = 50;
    this->p2_hp_ = 50;

    this->chest_flyweight_ = new Building("chest");
}
NormalBoard::NormalBoard(){
    this->turn_ = 1;
    this->p1_hp_ = 50;
    this->p2_hp_ = 50;

    this->chest_flyweight_ = new Building("chest");
}

/**
  DYNAMIC DISPATCH for NormalBoard setup
  @param none
  returns nothing
*/
void NormalBoard::SetUpBoard(){ //should only be called after the board's 2d vector has been set up

    srand(0);

    this->board_[2][2]->ChangeState("castle1");
    this->board_[2][3]->ChangeState("castle1");
    this->board_[3][2]->ChangeState("castle1");
    this->board_[3][3]->ChangeState("castle1");


    this->board_[20][20]->ChangeState("castle2");
    this->board_[20][21]->ChangeState("castle2");
    this->board_[21][20]->ChangeState("castle2");
    this->board_[21][21]->ChangeState("castle2");


    int count = 0;
    while(count < 7){
        int rand1 = 3 + (rand() % 16);
        int rand2 = 5 + (rand() % 13); //puts them more in the middle of the arena
        if(this->board_[rand1][rand2]->building_ == nullptr){ //if there's no castle there...
            this->board_[rand1][rand2]->ChangeState(this->chest_flyweight_); //utilizes just one object to populate a variable amount of rectangles for the chests
            count++;
        }
    }
}

/**
  DYNAMIC DISPATCH for DuelBoard setup
  @param none
  returns nothing
*/
void DuelBoard::SetUpBoard(){ //should only be called after the board's 2d vector has been set up

    srand(0);

    for(int i = 0; i < 24; i++){
        for(int j = 0; j < 24; j++){
            if(i > 17 || i < 7 || j < 5 || j > 19){ //gives us a surroudning wall
                this->board_[i][j]->ChangeState("wall");
            }
        }
    }
    //so really we want sort of a checkerboard pattern starting from [7,5]...
    this->board_[7][19]->ChangeState(new Infantry(2));
    this->board_[8][18]->ChangeState(new Infantry(2));
    this->board_[9][17]->ChangeState(new Knight(2));

    this->board_[10][18]->ChangeState(new Knight(2));
    this->board_[11][17]->ChangeState(new Knight(2));
    this->board_[12][18]->ChangeState(new Knight(2));

    this->board_[9][19]->ChangeState(new Wizard(2));
    this->board_[10][19]->ChangeState(new Archer(2));
    this->board_[11][19]->ChangeState(new Wizard(2));

    this->board_[13][17]->ChangeState(new Knight(2));
    this->board_[14][18]->ChangeState(new Knight(2));
    this->board_[15][17]->ChangeState(new Knight(2));

    this->board_[13][19]->ChangeState(new Wizard(2));
    this->board_[14][19]->ChangeState(new Archer(2));
    this->board_[15][19]->ChangeState(new Wizard(2));

    this->board_[16][18]->ChangeState(new Infantry(2));
    this->board_[17][19]->ChangeState(new Infantry(2));

    this->board_[12][19]->ChangeState(new Assassin(2));

    this->board_[7][5]->ChangeState(new Infantry(1));
    this->board_[8][6]->ChangeState(new Infantry(1));
    this->board_[9][7]->ChangeState(new Knight(1));

    this->board_[9][5]->ChangeState(new Wizard(1));
    this->board_[10][5]->ChangeState(new Archer(1));
    this->board_[11][5]->ChangeState(new Wizard(1));

    this->board_[10][6]->ChangeState(new Knight(1));
    this->board_[11][7]->ChangeState(new Knight(1));
    this->board_[12][6]->ChangeState(new Knight(1));
    this->board_[13][7]->ChangeState(new Knight(1));

    this->board_[13][5]->ChangeState(new Wizard(1));
    this->board_[14][5]->ChangeState(new Archer(1));
    this->board_[15][5]->ChangeState(new Wizard(1));

    this->board_[14][6]->ChangeState(new Knight(1));
    this->board_[15][7]->ChangeState(new Knight(1));
    this->board_[16][6]->ChangeState(new Infantry(1));
    this->board_[17][5]->ChangeState(new Infantry(1));

    this->board_[12][5]->ChangeState(new Assassin(1));
//    this->board_[6][18]->ChangeState("knight",1);
//    this->board_[7][19]->ChangeState("knight",1);

}

/**
  Spawns a given troop, based on how much money that player has
  @param Troop*, int plauyer, int money
  returns int cost = 0 if you cannot afford it or it returns cost of the troop
*/
int Board::Spawn(Troop *troop, int player, int money){
    troop->set_player(player);
    if(troop->get_cost() > money){ // if we don't have enough to purhcase it, return immediately with 0
        qDebug() << "Not enough for:";
        qDebug() << troop->get_cost();
        return 0;
    }
    if(player == 1){
        if(board_[1][2]->CheckEmpty()){
           board_[1][2]->ChangeState(troop, 1);
        }
        else if(board_[1][3]->CheckEmpty()){
            board_[1][3]->ChangeState(troop, 1);
        }
        else if(board_[4][2]->CheckEmpty()){
            board_[4][2]->ChangeState(troop, 1);
        }
        else if(board_[4][3]->CheckEmpty()){
            board_[4][3]->ChangeState(troop, 1);
        }
        else if(board_[2][1]->CheckEmpty()){
            board_[2][1]->ChangeState(troop, 1);
        }
        else if(board_[3][1]->CheckEmpty()){
            board_[3][1]->ChangeState(troop, 1);
        }
        else if(board_[2][4]->CheckEmpty()){
            board_[2][4]->ChangeState(troop, 1);
        }
        else if(board_[3][4]->CheckEmpty()){
            board_[3][4]->ChangeState(troop, 1);
        }
        else{
            qDebug() << "Spawn slots full!!";
            return 0;
        }
        return troop->get_cost(); //we return the cost to reflect on the money you have

    }
    else{
        if(board_[19][20]->CheckEmpty()){
           board_[19][20]->ChangeState(troop, 1);
        }
        else if(board_[19][21]->CheckEmpty()){
            board_[19][21]->ChangeState(troop, 1);
        }
        else if(board_[22][20]->CheckEmpty()){
           board_[22][20]->ChangeState(troop, 1);
        }
        else if(board_[22][21]->CheckEmpty()){
            board_[22][21]->ChangeState(troop, 1);
        }
        else if(board_[20][19]->CheckEmpty()){
            board_[20][19]->ChangeState(troop, 1);
        }
        else if(board_[21][19]->CheckEmpty()){
            board_[21][19]->ChangeState(troop, 1);
        }
        else if(board_[20][22]->CheckEmpty()){
            board_[20][22]->ChangeState(troop, 1);
        }
        else if(board_[21][22]->CheckEmpty()){
            board_[21][22]->ChangeState(troop, 1);
        }
        else{
            qDebug() << "Spawn slots full!!";
            return 0;
        }
    }
    return troop->get_cost(); //we return the cost to reflect on the money you have
}

/**
  Helper function to return a tuple of the coordinates of the rectanngle argument
  @param Rectangle*
  returns std::tuple<int,int> of coordinates
*/
std::tuple<int,int> Board::GetCoordinates(Rectangle* rectangle){
    for(int i = 0; i < 24; i++){
        for(int j = 0; j < 24; j++){
            if(this->board_[i][j] == rectangle){
                return std::make_tuple(i,j);
            }
        }
    }
}

/**
  Helper function to find true distance between squares, assuming diagnol is then 2, left is 1...
  @param int x1,x2,y1,y2
  returns int distance between the rectangles
*/
int TrueDistance(int x1, int y1, int x2, int y2){
    int total = 0;
    total += abs(x1 - x2);
    total += abs(y1 - y2);
    return total;
}

/**
  gets the moves for a given rectangle (always a troop)
  @param Rectangle*
  returns vector of tuples of places you can move
*/
std::vector<std::tuple<int,int> > Board::GetMoves(Rectangle * rectangle){
    Troop * troop = rectangle->troop_;

    int x = rectangle->get_x();
    int y = rectangle->get_y();
    int num_tiles = troop->get_num_tiles();

    std::vector<std::tuple<int,int> > temp_vect;

    for(int i = 0; i < 24; i++){
        for(int j = 0; j < 24; j++){
            if(this->board_[i][j]->CheckEmpty()){
                if(TrueDistance(x,y,i,j) <= num_tiles){
                    std::tuple<int, int> temp_tuple;
                    // Assigning values to tuple using make_tuple()
                    temp_tuple = std::make_tuple(i,j);
                    temp_vect.push_back(temp_tuple);
                    qDebug() << i;
                    qDebug() << j;
                }
            }
        }
    }
    return temp_vect;
}

/**
  gets the attack possibilites for a given rectangle (always a troop)
  @param Rectangle*
  returns vector of tuples of places in range of attack, or empty vect if no attacks worthwhile
*/
std::vector<std::tuple<int,int> > Board::GetAttackMoves(Rectangle *rectangle){
    Troop * troop = rectangle->troop_;

    int x = rectangle->get_x();
    int y = rectangle->get_y();
    int num_tiles = troop->get_range(); //range of attack, 2 for archers and wizards

    std::vector<std::tuple<int,int> > temp_vect;
    std::vector<std::tuple<int,int> > empty_vect; //returns if there are no troops to attack

    if(rectangle->troop_ != nullptr && rectangle->troop_->get_attacked() == true){
        return empty_vect;
    }//break condition for the function, we don't need to check because this guy cannot attack anyways

    int attackable = 0;

    for(int i = 0; i < 24; i++){
        for(int j = 0; j < 24; j++){
            if(this->board_[i][j]->building_ == nullptr){
                if(TrueDistance(x,y,i,j) <= num_tiles){
                    if(this->board_[i][j]->troop_ != nullptr && this->board_[i][j]->troop_->get_player() != troop->get_player()){
                        attackable += 1; //tells us this is a worthwhile result because there are troops to attack
                    }
                    else if(this->board_[i][j]->troop_ != nullptr){
                        continue; // we don't want to add this to the collection, because it is OUR TROOP
                    }
                    std::tuple<int, int> temp_tuple;
                    // Assigning values to tuple using make_tuple()
                    temp_tuple = std::make_tuple(i,j);
                    temp_vect.push_back(temp_tuple);
                    qDebug() << i;
                    qDebug() << j;
                }
            }
            else if(this->board_[i][j]->building_ != nullptr
                    && this->board_[i][j]->building_->player_ != 0
                    && this->board_[i][j]->building_->player_ != rectangle->troop_->get_player()){ //if player != 0 and not our own player, castle/chest to destroy
                if(TrueDistance(x,y,i,j) <= num_tiles){
                    std::tuple<int, int> temp_tuple = std::make_tuple(i,j);
                    temp_vect.push_back(temp_tuple);
                    attackable += 1; //worthwhile report within vector
                }
            }
        }
    }
    if(attackable > 0){
        return temp_vect;
    }
    else{
        return empty_vect;
    }
}

/**
  Repaints the empty rectangles – those that dont have a building or a troop on them
  @param none
  returns none
*/
void Board::RepaintEmpty(){
    for(int i = 0; i < 24; i++){
        for(int j = 0; j < 24; j++){ //will always be 24 by 24 given our sizes currently
            if(this->board_[i][j]->CheckEmpty()){
                this->board_[i][j]->ChangeState("empty");
            }
        }
    }
}

/**
  Repaints the empty rectangles – also repaints over the rectangle we just attacked
  @param rectange*
  returns none
*/
void Board::RepaintEmpty(Rectangle *rectangle){
    for(int i = 0; i < 24; i++){
        for(int j = 0; j < 24; j++){ //will always be 24 by 24 given our sizes currently
            qDebug() << i;
            qDebug() << j;
            if(this->board_[i][j]->CheckEmpty()){ //check empty says if it's a building or truly empty, it's empty
                this->board_[i][j]->ChangeState("empty");
            } //getting passed here means that the rectangle MUST contain a troop
            else if(this->board_[i][j]->troop_ != nullptr && this->board_[i][j]->attackable_ && this->board_[i][j] != rectangle){ //cannot be the rectangle we send,, that is the rectangle we WANT to attack
                this->board_[i][j]->ChangeState(board_[i][j]->troop_); //refreshes the red circle in the middle of the rectangle...
            }
        }
    }
}

/**
  Paints the moves from GetMoves()
  @param vector of tuples
  returns none
*/
void Board::PaintMoves(std::vector<std::tuple<int,int> > moves){
    for(std::tuple<int,int> move : moves){
        this->board_[std::get<0>(move)][std::get<1>(move)]->ChangeState("open");
    }
}

/**
  Paints the moves from GetAttackMoves()
  @param vector of tuples
  returns none
*/
void Board::PaintAttackMoves(std::vector<std::tuple<int,int> > attack_moves){
    qDebug() << "Within PaintAttackMoves";
    for(std::tuple<int,int> move : attack_moves){
        this->board_[std::get<0>(move)][std::get<1>(move)]->ChangeState("attackable");
    }
}

/**
  Moves the troop from one rectangle to the other
  @param Rectangle* previous, *next
  returns none
*/
void Board::Move(Rectangle* previous, Rectangle* next){ //basically an integer swap
    Troop * temp = previous->troop_;
    temp->moved();
    previous->troop_ = nullptr;
    next->ChangeState(temp);
    previous->ChangeState("empty");
    next->AnnounceStats();
}

/**
  Attack algorithm for troop->troop and troop->building
  @param Rectangle* attacker, *defender
  returns none
*/
void Board::Attack(Rectangle* attacker, Rectangle * defender){
    if(defender->building_ != nullptr){
        if(defender->building_->type_ == "chest"){ //chest mechanic
            attacker->troop_->set_item("potion");
            defender->ChangeState("empty"); //makes the square empty, no longer a chest
            return; //get outta here!!
        }
        attacker->troop_->moved(); //also just makes sure that it moves
        attacker->troop_->attacked();
        if(defender->building_->player_ == 1){
            this->p1_hp_ -= attacker->troop_->get_attack();
            if(this->p1_hp_ < 0){
                this->p1_hp_ = 0;
            }
            defender->ChangeState("refresh castle"); //refreshes it, takes away the red circle, etc.
        }
        else{
            this->p2_hp_ -= attacker->troop_->get_attack();
            if(this->p2_hp_ < 0){
                this->p2_hp_ = 0;
            }
            defender->ChangeState("refresh castle");
        }
        attacker->AnnounceStats();
        return; //break out of function
    }
    attacker->troop_->moved(); //also just makes sure that it moves
    attacker->troop_->attacked();
    int hit = attacker->troop_->get_attack() - defender->troop_->get_defense();
    if(hit <= 0){
        defender->troop_->loseHealth(1); //such that an attack always hits
        defender->Announce(std::to_string(defender->troop_->get_player()) + "'s defending " + defender->troop_->get_name() +
                           " took 1 damage from " +
                           std::to_string(attacker->troop_->get_player()) + "'s attacking " + attacker->troop_->get_name());
    }
    else{
        int chance = rand() % attacker->troop_->get_attack();
        if(chance < (attacker->troop_->get_attack() - 5)){ //so you need at least 5 for a critical hit, and bigger attacks have bigger chances of criticals
            defender->troop_->loseHealth(attacker->troop_->get_attack()); //lays full extent of attack
            qDebug() << "Critical hit";
            defender->Announce("Critical Hit! " + std::to_string(defender->troop_->get_player()) + "'s defending " + defender->troop_->get_name() +
                               " took " + std::to_string(attacker->troop_->get_attack()) + " damage from " +
                               std::to_string(attacker->troop_->get_player()) + "'s attacking " + attacker->troop_->get_name());
        }
        else{
            defender->troop_->loseHealth(hit); //if not a critical, just difference between attack and defense
            defender->Announce(std::to_string(defender->troop_->get_player()) + "'s defending " + defender->troop_->get_name() +
                               " took " + std::to_string(hit) + " damage from " +
                               std::to_string(attacker->troop_->get_player()) + "'s attacking " + attacker->troop_->get_name());
        }
    }

    std::tuple<int,int> temp_tuple_1 = this->GetCoordinates(attacker);
    std::tuple<int,int> temp_tuple_2 = this->GetCoordinates(defender);
    int distance = TrueDistance(std::get<0>(temp_tuple_1),std::get<1>(temp_tuple_1),std::get<0>(temp_tuple_2),std::get<1>(temp_tuple_2));

    defender->ChangeState(defender->troop_); //refreshes it, takes away the red circle, etc.
    if(defender->troop_->get_currentHealth() > 0 && distance <= defender->troop_->get_range()){
        int chance = rand() % 10;
        if(chance < attacker->troop_->get_speed()){
            qDebug() << "attacker evaded fight back";
            attacker->Announce(std::to_string(attacker->troop_->get_player()) + "'s attacking " + attacker->troop_->get_name() +
                               " evaded the return attack");
        }
        else{
            double attacker_defense = 1-(attacker->troop_->get_defense()/11); //gives us a decimal, smaller for better defenses
            double hp_lost = (defender->troop_->get_attack() - 1)*attacker_defense;
            int hp = int (hp_lost);
            attacker->troop_->loseHealth(hp+1);
            attacker->Announce(std::to_string(attacker->troop_->get_player()) + "'s attacking " + attacker->troop_->get_name() +
                               " took " + std::to_string(hp+1) + "damage from " +
                               std::to_string(defender->troop_->get_player()) + "'s defending " + defender->troop_->get_name());
        }
        if(attacker->troop_->get_currentHealth() <= 0){
            qDebug() << "Attacker has died";
            attacker->ChangeState("dead");
        }
    }
    else if (distance > defender->troop_->get_range() && defender->troop_->get_currentHealth() > 0){
        qDebug() << "Attacker is too far away for defender to attack back";
        attacker->Announce(std::to_string(attacker->troop_->get_player()) + "'s attacking " + attacker->troop_->get_name() +
                           " is too far to receive return attack from " +
                           std::to_string(defender->troop_->get_player()) + "'s defending " + defender->troop_->get_name());
    }
    else{
        qDebug() << "Defender has died";
        defender->ChangeState("dead");
    }
    attacker->AnnounceStats();
}

/**
  Gets the troops that can still move
  @param none
  returns int num troops
*/
int Board::GetTroopsToMove(){
    int count = 0;
    for(int i = 0; i < 24; i++){
        for(int j = 0; j < 24; j++){
            if(board_[i][j]->troop_ != nullptr){
                if(board_[i][j]->troop_->get_player() == this->turn_ && board_[i][j]->troop_->get_moved() == false){
                    count++; //this player has yet to move and is on the team of the current player
                }
            }
        }
    }
    return count;
}

/**
  Gets the troops that can still attack
  @param none
  returns int num troops
*/
int Board::GetTroopsToAttack(){
    int count = 0;
    for(int i = 0; i < 24; i++){
        for(int j = 0; j < 24; j++){
            if(board_[i][j]->troop_ != nullptr){
                if(board_[i][j]->troop_->get_player() == this->turn_ && board_[i][j]->troop_->get_attacked() == false){
                    if(this->GetAttackMoves(board_[i][j]).size() != 0){
                        count++; //this player has yet to attack and is in position to attack
                    }
                }
            }
        }
    }
    return count;
}

/**
  Goes to the next turn, updates things accordingly
  @param none
  returns turn
*/
int Board::AdvanceTurn(){
    if(this->turn_ == 1){
        this->turn_ = 2;
    }
    else{
        this->turn_ = 1;
    }
    for(int i = 0; i < 24; i++){
        for(int j = 0; j < 24; j++){
            if(board_[i][j]->troop_ != nullptr){
                board_[i][j]->troop_->refresh(); //this makes the bools for moved and attacked back to false
            }
        }
    }
    board_[0][0]->Announce("NEXT TURN. It is now Player " + std::to_string(turn_) + "'s turn");

    return this->turn_;
}

/**
  Changes state of moveable troops
  @param none
  returns none
*/
void Board::ShowMoveable(){
    for(int i = 0; i < 24; i++){
        for(int j = 0; j < 24; j++){
            if(board_[i][j]->troop_ != nullptr && board_[i][j]->troop_->get_player() == this->turn_){
                if(board_[i][j]->troop_->get_moved() == false){ //if we still haven't moved yet
                    board_[i][j]->ChangeState("moveable_visual_");
                }
            }
        }
    }
}
/**
  Changes state of moveable troops back to regular
  @param none
  returns none
*/
void Board::UnShowMoveable(){
    for(int i = 0; i < 24; i++){
        for(int j = 0; j < 24; j++){
            if(board_[i][j]->troop_ != nullptr && board_[i][j]->troop_->get_player() == this->turn_){
                if(board_[i][j]->troop_->get_moved() == false){ //if we still haven't moved yet
                    board_[i][j]->ChangeState("not moveable_visual_");
                }
            }
        }
    }
}
/**
  Changes state of attackable troops
  @param none
  returns none
*/
void Board::ShowAttackable(){
    for(int i = 0; i < 24; i++){
        for(int j = 0; j < 24; j++){
            if(board_[i][j]->troop_ != nullptr && board_[i][j]->troop_->get_player() == this->turn_){
                if(board_[i][j]->troop_->get_attacked() == false){ //if we still haven't moved yet
                    board_[i][j]->ChangeState("attackable_visual_");
                }
            }
        }
    }
}

/**
  Changes state of attackable troops back to regular
  @param none
  returns none
*/
void Board::UnShowAttackable(){
    for(int i = 0; i < 24; i++){
        for(int j = 0; j < 24; j++){
            if(board_[i][j]->troop_ != nullptr && board_[i][j]->troop_->get_player() == this->turn_){
                if(board_[i][j]->troop_->get_attacked() == false){ //if we still haven't moved yet
                    board_[i][j]->ChangeState("not attackable_visual_");
                }
            }
        }
    }
}

/**
  DYNAMIC DISPATCH for NormalBoard CheckWin
  @param none
  returns none int winner (0 if no winner)
*/
int NormalBoard::CheckWin(){
    if(this->p1_hp_ <= 0){
        return 2; //player 2 wins...
    }
    else if(this->p2_hp_ <= 0){
        return 1;
    }
    else return 0;
}

/**
  DYNAMIC DISPATCH for NormalBoard CheckWin
  @param none
  returns int winner (0 if no winner)
*/
int DuelBoard::CheckWin(){
    int count_1 = 0;
    int count_2 = 0;
    for(int i = 0; i < 24; i++){
        for(int j = 0; j < 24; j++){
            if(this->board_[i][j]->troop_ != nullptr){
                if(this->board_[i][j]->troop_->get_player() == 1){
                    count_1++;
                }
                else{
                    count_2++;
                }
            }
        }
    }
    if(count_1 == 0){
        return 2; //player 2 wins
    }
    else if(count_2 == 0){
        return 1;
    }
    else{
        return 0; //still going... troops left on both sides..
    }
}
