#include "Medic.h"
#include <iostream>


namespace mtm {
    Medic::Medic(const Team team, const units_t health, const units_t ammo, const units_t range, const units_t power):
    Character::Character(team,health,ammo,range,power,kMedicMoveRange,kMedicAddAmmo,kMedicCppTeam,kMedicPythonTeam)
    {
    }
   
    Character* Medic::clone() const 
    {
        return new Medic(*this);
    }


    void Medic::attack(GridPoint attacker_point, GridPoint victim_point,Matrix<std::shared_ptr<Character>>& board)  
    {
        //check range
        if(GridPoint::distance(attacker_point,victim_point)>range)
        {
            throw mtm::OutOfRange();
        }
        //check ammo
        std::shared_ptr<Character> victim=board(victim_point.row,victim_point.col);
        if(victim && !isSameTeam(*this,*victim) && (ammo == 0)) {
            throw mtm::OutOfAmmo();
        }
        if ((attacker_point == victim_point)||(victim == nullptr))
        {
            throw mtm::IllegalTarget();
        }
        units_t delta=-power;
        if(!isSameTeam(*this,*victim))
        {
            ammo--;
            delta=-delta;
        }
        victim->changeHealth(delta);
        if(victim->isDead())
        {
            board(victim_point.row,victim_point.col)=nullptr;
        }
    }
}