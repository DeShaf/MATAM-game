#ifndef GAME_H
#define GAME_H
#include "Character.h"
#include "Soldier.h"
#include "Medic.h"
#include "Sniper.h"
#include "Auxiliaries.h"
#include "Matrix.h"
#include "Exceptions.h"
#include <cmath>
#include <memory>

namespace mtm {
    /* class Game: Manages the game actions
    */
    class Game
    {
        Matrix<std::shared_ptr<Character>> board;
        int height, width;
        
        /* verifyLegalCell:  checks if a given set of coordinates is positive and within the game board  */
        void verifyLegalCell(const GridPoint& point) const;

        /* verifyLegalEmptyCell:  checks if the given coordinates is legal and empty  */
        void verifyLegalEmptyCell(const GridPoint& point) const;

        /* verifyLegalOccupiedCell:  checks if the given coordinates is legal and occupied  */
        void verifyLegalOccupiedCell(const GridPoint& point) const;
        
        /* checkWhichTeam:  returns the team of the character 
                            based on the given letter that represents it in the board */        
        static Team checkWhichTeam(char letter);

        /* boardToCharArray:  Creates a array of chars according to each character type and team  */
        char* boardToCharArray() const;
        
        /* isSoldier:  checks if a a character is of type soldier  */
        static bool isSoldier(std::shared_ptr<Character> attacker);

        /* soldierAttackRest:  attack rest of the board after soldier attack according to soldiers rules of attack  */
        void soldierAttackRest(std::shared_ptr<Character> attacker,const GridPoint &dst_coordinates,const int attack_strength);

        /* copyBoardContentTo:  Copy all the contect of a game to another board (all the characters are cloned to the board)*/
        void copyBoardContentTo(Matrix<std::shared_ptr<Character>>& other_board) const;




        public:
        /* C'tor:  Creates a new game in the size of height and width  */
        Game(int height,  int width);

        /* D'tor:  Destroys a game and frees all its resources */
        ~Game();

        /* Copy C'tor:  Creates a new game which is a copy of other */
        Game(const Game& other);

        /* =opeartor :  changes the game to be equivalent to other  */
        Game& operator=(const Game& other);
        
        /* addCharacter:  Adds a new character to the game to the given coordinates */
        void addCharacter(const GridPoint& coordinates, std::shared_ptr<Character> character);
        
        /* makeCharacter:  makes a new character
            parameters: type: the type of the character
                        team: the team of the character
                        health: the starting health of the character
                        ammo: the starting ammo of the character
                        range: the attack range of the character
                        power: the power of the attack of the character */
        static std::shared_ptr<Character> makeCharacter(CharacterType type, Team team, units_t health, units_t ammo,
                                                         units_t range, units_t power);

        /* move:  moves a character from one coordinate to another coordinate*/
        void move(const GridPoint & src_coordinates, const GridPoint & dst_coordinates);

        /* attack:  recieves coordinates for the attacker and the victim,
                    and performs the attack action */
        void attack(const GridPoint & src_coordinates, const GridPoint & dst_coordinates);

        /* reload:  reloads ammo for the character in the given coordinates */
        void reload(const GridPoint & coordinates);

        /* << operator: returns reference to ostream in order to print the game * */
        friend std::ostream& operator<<(std::ostream& os, const Game& game);

        /* isOver:  returns if the game is over: when there are characters of only one team on the board.
                    When a pointer to the winning team is received as a parameter, if the game is over the
                    pointer is overwritten to point to the winning team  */
        bool isOver(Team* winningTeam=NULL) const;
    };
}

#endif