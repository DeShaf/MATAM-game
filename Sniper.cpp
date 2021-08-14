#include "Sniper.h"
#include <iostream>
#include <cmath>


namespace mtm {
    Sniper::Sniper(const Team team, const units_t health, const units_t ammo, const units_t range,
                   const units_t power): Character::Character(team,health,ammo,range,power,kSniperMoveRange,
                   kSniperAddAmmo,kSniperCppTeam,kSniperPythonTeam)
    {
    }
   
    Character* Sniper::clone() const 
    {
        return new Sniper(*this);
    }


    void Sniper::attack(GridPoint attacker_point, GridPoint victim_point,Matrix<std::shared_ptr<Character>>& board)  
    {
        //check range
        if((GridPoint::distance(attacker_point,victim_point)<ceil((double)range/kSniperMinRange)) 
                                    || (GridPoint::distance(attacker_point,victim_point)>range))
        {
            throw mtm::OutOfRange();
        }
        //check ammo
        if(ammo == 0) {
            throw mtm::OutOfAmmo();
        }
        std::shared_ptr<Character> victim=board(victim_point.row,victim_point.col);
        if((victim==nullptr) || (isSameTeam(*this,*victim)))
        {
            throw mtm::IllegalTarget();
        }
        ammo--;
        attacks_counter++;
        if (attacks_counter==kSpecialAttackNum){
            attacks_counter=0;
            victim->changeHealth(kSpecialAttackMultiply*power);
        }
        else{
            victim->changeHealth(power);
        }
        if(victim->isDead()){
            board(victim_point.row,victim_point.col)=nullptr;
        }
    }
}