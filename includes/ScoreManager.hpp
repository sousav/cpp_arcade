/*
** ScoreManager.hpp for Shared in /Users/gmblucas/Desktop/Shared/cpp_arcade/includes
**
** Made by Lucas Gambini
** Login   <gmblucas@epitech.net>
**
** Started on  Tue Mar 14 04:37:42 2017 Lucas Gambini
** Last update	Thu Apr 06 01:26:33 2017 Full Name
*/

#ifndef SCOREMANAGER_HPP_
#define SCOREMANAGER_HPP_

#include <string>
#include <fstream>
#include <vector>
#include <iostream>
#include <sstream>

struct Score {
        std::string name;
        int score;
};

class ScoreManager {

public:
    explicit ScoreManager (std::string const & gameName, std::string name);
    ~ScoreManager ();

    void pushNewScore(int score);
    int getBestScore() const;
    std::string getBestName() const;
    std::string const &getName() const;
    void setName(std::string const &name);
    std::vector<Score> const &getScoreBoard() const;

private:
    ScoreManager(const ScoreManager &obj);
    ScoreManager    &operator=(const ScoreManager &obj);
    void loadScores();
    bool getLineInfo(std::string line, Score &score);

    std::vector<Score> _scoreBoard;
    std::string _name;
    std::fstream _file;
};

#endif /* !SCOREMANAGER_HPP_ */
