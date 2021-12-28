#ifndef BUILDING_H
#define BUILDING_H

#include <iostream>
#include <QColor>

class Building
{
public:
    Building(std::string type);
    std::string type_;
    QColor color_;
    int player_;
    int currentHealth_;

    QColor get_color(){ return color_; }

};

#endif // BUILDING_H
