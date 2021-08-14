#ifndef MEDIC_H
#define MEDIC_H
#include "Character.h"
#include "Auxiliaries.h"
#include "Exceptions.h"
#include "Game.h"

namespace mtm {
    const units_t kMedicMoveRange=5, kMedicAddAmmo=5;
    const char kMedicCppTeam='M', kMedicPythonTeam='m';
    class Medic : public Character {
        public: 
        Medic(const Team team, const units_t health ,const units_t ammo, const units_t range, const units_t power);
        virtual Character* clone() const override;
        void attack(GridPoint attacker_point, GridPoint victim_point,Matrix<std::shared_ptr<Character>>& board)  override;
    };
}

#endif