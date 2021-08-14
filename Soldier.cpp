#include "Soldier.h"
#include <iostream>


namespace mtm {
    Soldier::Soldier(const Team team, const units_t health, const units_t ammo, const units_t range,
                     const units_t power): Character::Character(team,health,ammo,range,power,kSoldierMoveRange,
                     kSoldierAddAmmo, kSoldierCppTeam, kSoldierPythonTeam)
    {
    }
   
    Character* Soldier::clone() const 
    {
        return new Soldier(*this);
    }


    void Soldier::attack(GridPoint attacker_point, GridPoint victim_point,Matrix<std::shared_ptr<Character>>& board)  
    {
        //check range
        if(GridPoint::distance(attacker_point,victim_point)>range)
        {
            throw mtm::OutOfRange();
        }
        //check ammo
        if(ammo == 0) {
            throw mtm::OutOfAmmo();
        }
        std::shared_ptr<Character> victim=board(victim_point.row,victim_point.col);
        if ((attacker_point.row!=victim_point.row) && (attacker_point.col!=victim_point.col)){
            throw mtm::IllegalTarget();
        }
        ammo--;
        if(victim)
        {
            if(!isSameTeam(*this,*victim))
            {
                victim->changeHealth(power);
                if(victim->isDead())
                {
                    board(victim_point.row,victim_point.col)=nullptr;
                }
            }
        }
        for(int i=0; i<board.height(); i++){
            for(int j=0;j<board.width();j++){
                GridPoint current_point(i,j);
                if((board(i,j)!=nullptr)
                    && GridPoint::distance(current_point, victim_point) <= 
                    ceil((double)getRange()/kSoldierDangerZone)
                    && GridPoint::distance(current_point, victim_point) > 0 
                    && !(isSameTeam(*this, *(board(i,j))))){
                        board(i,j)->changeHealth(ceil((double)power/kSoldierRicochetDamage));
                        if(board(i,j)->isDead()){
                            board(i,j) = nullptr;
                        }
                }
            }
        }
    }
}