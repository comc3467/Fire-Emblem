#ifndef TROOP_H
#define TROOP_H

#include <QColor>
#include <iostream>


class Troop
{
public:
    Troop();

//    virtual void attack(Troop *) = 0;
    virtual QColor get_color() = 0;
    virtual std::string get_name() = 0;
    virtual int get_num_tiles() = 0;
    virtual void set_player(int player){player_=player;};
    virtual int get_player() = 0;
    virtual void set_currentHealth(int health){currentHealth_=health;};
    virtual int get_currentHealth() = 0;
    virtual int get_maxHealth() = 0;
    virtual int get_attack() = 0;
    virtual int get_defense() = 0;
    virtual int get_speed() = 0;
    virtual int get_range() = 0;
    virtual bool get_moved() = 0;
    virtual bool get_attacked() = 0;

    virtual void moved() = 0;
    virtual void attacked() = 0;

    virtual void loseHealth(int hp) = 0;

    virtual void refresh() = 0;

    virtual int get_cost() = 0;

    virtual std::string get_item() = 0;

    virtual void set_item(std::string item) = 0;

protected:
    std::string name_;
    int maxHealth_;
    int currentHealth_;
    int speed_;
    int attack_;
    int defense_;
    int tiles_;
    int player_;
    int range_;
    QColor color_;
    bool moved_;
    bool attacked_;

    std::string item_;
};

// Derived classes

class Infantry: public Troop {
   public:
      Infantry(int player);
//      void attack(Troop *);
      QColor get_color(){ return color_; }
      std::string get_name(){ return name_; }
      int get_num_tiles(){ return tiles_; }
      int get_player(){return player_ ;}
      int get_currentHealth(){return currentHealth_;}
      int get_maxHealth(){return maxHealth_;}
      int get_attack(){return attack_;}
      int get_defense(){return defense_;}
      int get_speed(){return speed_;}
      int get_range(){return range_;}

      bool get_moved(){ return moved_;}
      bool get_attacked(){ return attacked_;}

      void moved(){ moved_ = true;}
      void attacked(){ attacked_ = true;}

      void loseHealth(int hp){
          this->currentHealth_ -= hp;
      }

      void refresh(){
          this->moved_ = false;
          this->attacked_ = false;
      }

      int get_cost(){ return 20;}

      std::string get_item(){ return item_; }

      void set_item(std::string item){ this->item_ = item; }
};

class Knight: public Troop {
   public:
      Knight(int player);
//      void attack(Troop *);
      QColor get_color(){ return color_; }
      std::string get_name(){ return name_; }
      int get_num_tiles(){ return tiles_; }
      int get_player(){return player_ ;}
      int get_currentHealth(){return currentHealth_;}
      int get_maxHealth(){return maxHealth_;}
      int get_attack(){return attack_;}
      int get_defense(){return defense_;}
      int get_speed(){return speed_;}
      int get_range(){return range_;}

      bool get_moved(){ return moved_;}
      bool get_attacked(){ return attacked_;}

      void moved(){ moved_ = true;}
      void attacked(){ attacked_ = true;}

      void loseHealth(int hp){
          this->currentHealth_ -= hp;
      }

      void refresh(){
          this->moved_ = false;
          this->attacked_ = false;
      }

      int get_cost(){ return 40;}

      std::string get_item(){ return item_; }

      void set_item(std::string item){ this->item_ = item; }
};

class Archer: public Troop {
   public:
      Archer(int player);
//      void attack(Troop *);
      QColor get_color(){ return color_; }
      std::string get_name(){ return name_; }
      int get_num_tiles(){ return tiles_; }
      int get_player(){return player_ ;}
      int get_currentHealth(){return currentHealth_;}
      int get_maxHealth(){return maxHealth_;}
      int get_attack(){return attack_;}
      int get_defense(){return defense_;}
      int get_speed(){return speed_;}
      int get_range(){return range_;}

      bool get_moved(){ return moved_;}
      bool get_attacked(){ return attacked_;}

      void moved(){ moved_ = true;}
      void attacked(){ attacked_ = true;}

      void loseHealth(int hp){
          this->currentHealth_ -= hp;
      }

      void refresh(){
          this->moved_ = false;
          this->attacked_ = false;
      }

      int get_cost(){ return 20;}
      std::string get_item(){ return item_; }

      void set_item(std::string item){ this->item_ = item; }
};

class Wizard: public Troop {
   public:
      Wizard(int player);
//      void attack(Troop *);
      QColor get_color(){ return color_; }
      std::string get_name(){ return name_; }
      int get_num_tiles(){ return tiles_; }
      int get_player(){return player_ ;}
      int get_currentHealth(){return currentHealth_;}
      int get_maxHealth(){return maxHealth_;}
      int get_attack(){return attack_;}
      int get_defense(){return defense_;}
      int get_speed(){return speed_;}
      int get_range(){return range_;}

      bool get_moved(){ return moved_;}
      bool get_attacked(){ return attacked_;}

      void moved(){ moved_ = true;}
      void attacked(){ attacked_ = true;}

      void loseHealth(int hp){
          this->currentHealth_ -= hp;
      }

      void refresh(){
          this->moved_ = false;
          this->attacked_ = false;
      }
      int get_cost(){ return 40;}

      std::string get_item(){ return item_; }

      void set_item(std::string item){ this->item_ = item; }
};

class Assassin: public Troop {
   public:
      Assassin(int player);
//      void attack(Troop *);
      QColor get_color(){ return color_; }
      std::string get_name(){ return name_; }
      int get_num_tiles(){ return tiles_; }
      int get_player(){return player_ ;}
      int get_currentHealth(){return currentHealth_;}
      int get_maxHealth(){return maxHealth_;}
      int get_attack(){return attack_;}
      int get_defense(){return defense_;}
      int get_speed(){return speed_;}
      int get_range(){return range_;}

      bool get_moved(){ return moved_;}
      bool get_attacked(){ return attacked_;}

      void moved(){ moved_ = true;}
      void attacked(){ attacked_ = true;}

      void loseHealth(int hp){
          this->currentHealth_ -= hp;
      }

      void refresh(){
          this->moved_ = false;
          this->attacked_ = false;
      }

      int get_cost(){ return 50;}

      std::string get_item(){ return item_; }

      void set_item(std::string item){ this->item_ = item; }
};

#endif // TROOP_H
