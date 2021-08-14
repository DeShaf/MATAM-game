#ifndef SOLDIER_H
#define SOLDIER_H
#include "Character.h"
#include "Auxiliaries.h"
#include "Game.h"

namespace mtm {
    const units_t kSoldierMoveRange=3, kSoldierAddAmmo=3;
    const char kSoldierCppTeam='S', kSoldierPythonTeam='s';
    class Soldier : public Character {
        const units_t kSoldierDangerZone=3,kSoldierRicochetDamage=2;
        public: 
        Soldier(const Team team, const units_t health ,const units_t ammo, const units_t range, const units_t power);
        virtual Character* clone() const override;
        void attack(GridPoint attacker_point, GridPoint victim_point,Matrix<std::shared_ptr<Character>>& board)  override;
    };
}


#endif