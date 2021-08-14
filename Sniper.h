#ifndef SNIPER_H
#define SNIPER_H
#include "Character.h"
#include "Auxiliaries.h"
#include "Exceptions.h"
#include "Game.h"

namespace mtm {
    const units_t kSniperMoveRange=4, kSniperAddAmmo=2;
    const char kSniperCppTeam='N', kSniperPythonTeam='n';
    class Sniper : public Character {
        int attacks_counter=0;
        const int kSpecialAttackNum=3,kSpecialAttackMultiply=2,kSniperMinRange=2;
        public: 
        Sniper(const Team team, const units_t health ,const units_t ammo, const units_t range, const units_t power);
        virtual Character* clone() const override;
        void attack(GridPoint attacker_point, GridPoint victim_point,Matrix<std::shared_ptr<Character>>& board)  override;
    };
}

#endif