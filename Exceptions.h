#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <iostream>
#include <string>


namespace mtm{
    class Exception : public std::exception {};

    class GameException : public Exception{
        std::string error_string;
        public:
        GameException(const std::string& error_type);
        const char* what() const noexcept;
        virtual ~GameException();
    };
    
    class IllegalArgument : public GameException {
        public:
        IllegalArgument();
    };
    class IllegalCell : public GameException {
        public:
        IllegalCell();
    };
    class CellEmpty : public GameException {
        public:
        CellEmpty();
    };
    class MoveTooFar : public GameException {
        public:
        MoveTooFar();
    };
    class CellOccupied : public GameException {
        public:
        CellOccupied();
    };
    class OutOfRange : public GameException {
        public:
        OutOfRange();
    };
    class OutOfAmmo : public GameException {
        public:
        OutOfAmmo();
    };
    class IllegalTarget : public GameException {
        public:
        IllegalTarget();
    };
}

#endif