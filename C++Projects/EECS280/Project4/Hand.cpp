#include "Hand.h"
#include <cstdlib>

Hand::Hand() : value(0), soft(false) {}

void Hand::discard_all()
{
    value = 0;
    soft = false;
}

void Hand::add_card(Card c)
{
    if(c.get_rank()<9) value+=c.get_rank()+2;
    else if (c.get_rank()<12) value +=10;
    else if (value < 11)
    {
        value += 11;
        soft  = true;
    }
    else value +=1;
    if(soft && value > 21)
    {
        value -= 10;
        soft = false;
    }
}

int Hand::hand_value() const
{
    return value;
}

bool Hand::hand_is_soft() const
{
    return soft;
}
