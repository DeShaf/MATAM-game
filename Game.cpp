#include "Game.h"

namespace mtm
{

    Game::Game(int height, int width) : board(mtm::Dimensions(1, 1), nullptr), height(height), width(width)
    {
        try
        {
            board = Matrix<std::shared_ptr<Character>>(Dimensions(height, width), nullptr);
        }
        catch (Matrix<std::shared_ptr<Character>>::IllegalInitialization &e)
        {
            throw mtm::IllegalArgument();
        }
    }

    Game::Game(const Game &other) : board(mtm::Dimensions(other.board.height(), other.board.width()), nullptr),
                                    height(other.height), width(other.width)
    {
        other.copyBoardContentTo((*this).board);
    }

    Game &Game::operator=(const Game &other)
    {
        if (this == &other)
        {
            return *this;
        }
        Matrix<std::shared_ptr<Character>> new_matrix(mtm::Dimensions(other.board.height(), other.board.width()), nullptr);
        other.copyBoardContentTo(new_matrix);
        board = new_matrix;
        height = other.height;
        width = other.width;
        return *this;
    }

    void Game::addCharacter(const GridPoint &coordinates, std::shared_ptr<Character> character)
    {
        verifyLegalEmptyCell(coordinates);
        board(coordinates.row, coordinates.col) = character;
    }

    std::shared_ptr<Character> Game::makeCharacter(CharacterType type, Team team, units_t health, units_t ammo,
                                                   units_t range, units_t power)
    {
        if (health <= 0 || ammo < 0 || range < 0 || power < 0)
        {
            throw mtm::IllegalArgument();
        }
        switch (type)
        {
        case SOLDIER:
            return std::shared_ptr<Character>(new Soldier(team, health, ammo, range, power));
        case MEDIC:
            return std::shared_ptr<Character>(new Medic(team, health, ammo, range, power));
        default:
        {
            assert(type == SNIPER);
            return std::shared_ptr<Character>(new Sniper(team, health, ammo, range, power));
        }
        }
    }

    void Game::move(const GridPoint &src_coordinates, const GridPoint &dst_coordinates)
    {
        verifyLegalCell(dst_coordinates);
        verifyLegalOccupiedCell(src_coordinates);
        if (src_coordinates == dst_coordinates)
        {
            return;
        }
        board(src_coordinates.row, src_coordinates.col)->Character::verifyLegalMove(src_coordinates, dst_coordinates);
        verifyLegalEmptyCell(dst_coordinates);
        board(dst_coordinates.row, dst_coordinates.col) = board(src_coordinates.row, src_coordinates.col);
        board(src_coordinates.row, src_coordinates.col) = nullptr;
    }

    void Game::attack(const GridPoint &src_coordinates, const GridPoint &dst_coordinates)
    {
        verifyLegalCell(dst_coordinates);
        verifyLegalOccupiedCell(src_coordinates);
        std::shared_ptr<Character> attacker = board(src_coordinates.row, src_coordinates.col);
        attacker->attack(src_coordinates, dst_coordinates, board);
    }

    void Game::reload(const GridPoint &coordinates)
    {
        verifyLegalOccupiedCell(coordinates);
        board(coordinates.row, coordinates.col)->Character::loadAmmo();
    }

    std::ostream &operator<<(std::ostream &os, const Game &game)
    {
        char *char_board = game.boardToCharArray();
        printGameBoard(os, char_board, char_board + game.board.size(), game.width);
        delete[] char_board;
        return os;
    }

    bool Game::isOver(Team *winningTeam) const
    {
        bool cpp_team = false, python_team = false;
        char *char_board = boardToCharArray();
        for (int i = 0; i < board.size(); i++)
        {
            if (cpp_team && python_team)
            {
                delete[] char_board;
                return false;
            }
            if (char_board[i] != ' ')
            {
                if (checkWhichTeam(char_board[i]) == CPP)
                {
                    cpp_team = true;
                }
                else if (checkWhichTeam(char_board[i]) == PYTHON)
                {
                    python_team = true;
                }
            }
        }
        delete[] char_board;
        if ((!cpp_team && !python_team) || (cpp_team && python_team))
        {
            return false;
        }
        if (winningTeam != NULL)
        {
            if (cpp_team && !python_team)
            { //cpp wins
                *winningTeam = CPP;
            }
            else
            { //python wins
                assert(!cpp_team && python_team);
                *winningTeam = PYTHON;
            }
        }
        return true;
    }

    char *Game::boardToCharArray() const
    {
        char *char_board = new char[board.size()];
        int k = 0;
        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                if (board(i, j))
                {
                    char_board[k++] = board(i, j)->toChar();
                }
                else
                {
                    char_board[k++] = ' ';
                }
            }
        }
        return char_board;
    }

    Team Game::checkWhichTeam(char letter)
    {
        if (letter >= 'a' && letter <= 'z')
        {
            return PYTHON;
        }
        else
        {
            return CPP;
        }
    }

    void Game::verifyLegalCell(const GridPoint &point) const
    {
        if ((point.row >= board.height() || point.col >= board.width()) || ((point.row < 0) || (point.col < 0)))
        {
            throw mtm::IllegalCell();
        }
    }

    void Game::verifyLegalEmptyCell(const GridPoint &point) const
    {
        verifyLegalCell(point);
        if (board(point.row, point.col) != nullptr)
        {
            throw mtm::CellOccupied();
        }
    }

    void Game::verifyLegalOccupiedCell(const GridPoint &point) const
    {
        verifyLegalCell(point);
        if (board(point.row, point.col) == nullptr)
        {
            throw mtm::CellEmpty();
        }
    }

    void Game::copyBoardContentTo(Matrix<std::shared_ptr<Character>> &other_board) const
    {
        Matrix<std::shared_ptr<Character>>::const_iterator it = board.begin();
        Matrix<std::shared_ptr<Character>>::iterator other_it = other_board.begin();
        for (; it != board.end(); it++)
        {
            if (*it)
            {
                *other_it = std::shared_ptr<Character>((*it)->clone());
            }
            other_it++;
        }
    }

    Game::~Game()
    {
    }
} // namespace mtm