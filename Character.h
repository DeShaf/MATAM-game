#ifndef CHARACTER_H
#define CHARACTER_H
#include "Auxiliaries.h"
#include "Exceptions.h"
#include "Matrix.h"
#include <memory>


namespace mtm {
    /* class Character: Abstract class for all character type (Soldier,Medic,Sniper)
    */
    class Character {
        protected:
            Team team;
            units_t health, ammo;
            const units_t range,power,move_range, add_ammo;
            const char cpp_team,python_team;

            /* Character C'tor:   Creates a character 
                Parmaters:  team: the character team
                            health: the character starting health
                            ammo: the character starting ammo
                            range: the character range of attack
                            power: the character power of attack 
                            move_range: the character range of moving
                            add_ammo: how much ammo is given to the character after a reload
                            cpp_team: the character char if it belongs to CPP team
                            cpp_team: the character char if it belongs to PYTHON team*/
            Character(const Team team,const units_t health,const units_t ammo,const units_t range,const units_t power,
                        const units_t move_range,const units_t add_ammo,const char cpp_team,const char python_team);
            
            public:
            /* Character D'tor:   detroys a character
            is only implemented for derived classes */
            virtual ~Character();

            /* clone:   copies a character and returns a pointer to it 
            is only implemented for derived classes */
            virtual Character* clone() const = 0;

            /* attack:      recieves coordinates for attacker and victim, and a pointer to the victim 
                            and performs attack action
            is only implemented for derived classes */
            virtual void attack(GridPoint attacker_point, GridPoint victim_point,Matrix<std::shared_ptr<Character>>& board) = 0;
            
            /* toChar:      returns the sign associated with each character,
                            determined by the character's type and team */
            char toChar() const;
            
            /* getRange:      returns the character's range */
            units_t getRange() const;

            /* isDead:      returns if the character health is lower or equal to zero */
            bool isDead() const;

            /* verifyLegalMove:  checks if a distance between two given coordinates is within 
                                    the moving range of the character */
            void verifyLegalMove(const GridPoint & point_src,const GridPoint & point_dst) const;

            /* isSameTeam:      returns if 2 characters are on the same team */
            friend bool isSameTeam(const Character& character, const Character& other);
            
            void loadAmmo();
             /* changeHealth:   subtracts delta from the character health 
                                (delta is negative if it should be added to health)*/
            void changeHealth(const units_t delta);  
    };
}

#endif