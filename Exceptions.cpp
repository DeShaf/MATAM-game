#include "Exceptions.h"

namespace mtm{
        GameException::GameException(const std::string& error_type) : 
                                    error_string("A game related error has occurred: " + error_type) 
        {}
        const char* GameException::what() const noexcept{
            return error_string.c_str();
        }
        GameException::~GameException() {}

        IllegalArgument::IllegalArgument() : GameException("IllegalArgument") {}
        IllegalCell::IllegalCell() : GameException("IllegalCell") {}
        CellEmpty::CellEmpty() : GameException("CellEmpty") {}
        MoveTooFar::MoveTooFar(): GameException("MoveTooFar") {}
        CellOccupied::CellOccupied() : GameException("CellOccupied") {}
        OutOfRange::OutOfRange() : GameException("OutOfRange") {}
        OutOfAmmo::OutOfAmmo() : GameException("OutOfAmmo") {}
        IllegalTarget::IllegalTarget() :  GameException("IllegalTarget") {}        
}