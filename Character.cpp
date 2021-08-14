#include "Character.h"

namespace mtm
{
    Character::Character(const Team team, const units_t health, const units_t ammo, const units_t range, const units_t power,
                         const units_t move_range, const units_t add_ammo, const char cpp_team, const char python_team) : team(team), health(health), ammo(ammo), range(range), power(power),
                                                                                                                          move_range(move_range), add_ammo(add_ammo), cpp_team(cpp_team), python_team(python_team)
    {
    }

    void Character::loadAmmo()
    {
        ammo += add_ammo;
    }

    void Character::verifyLegalMove(const GridPoint &point_src, const GridPoint &point_dst) const
    {
        if (GridPoint::distance(point_src, point_dst) > move_range)
        {
            throw mtm::MoveTooFar();
        }
    }

    bool Character::isDead() const
    {
        return (health <= 0);
    }

    bool isSameTeam(const Character &character, const Character &other)
    {
        return (character.team == other.team);
    }

    units_t Character::getRange() const
    {
        return range;
    }

    void Character::changeHealth(const units_t damage)
    {
        health -= damage;
    }

    char Character::toChar() const
    {
        if (team == CPP)
            return cpp_team;
        else
            return python_team;
    }

    Character::~Character() {}
} // namespace mtm